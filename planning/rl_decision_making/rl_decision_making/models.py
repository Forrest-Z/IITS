#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
import numpy as np 
import torch 
import torch.nn as nn 
from torch.nn import functional as F

class BaseModule(torch.nn.Module):
    """
        Base torch.nn.Module implementing basic features:
            - initialization factory
            - normalization parameters
    """
    def __init__(self, activation_type="RELU", reset_type="XAVIER", normalize=None):
        super().__init__()
        self.activation = activation_factory(activation_type)
        self.reset_type = reset_type
        self.normalize = normalize
        self.mean = None
        self.std = None

    def _init_weights(self, m):
        if hasattr(m, 'weight'):
            if self.reset_type == "XAVIER":
                torch.nn.init.xavier_uniform_(m.weight.data)
            elif self.reset_type == "ZEROS":
                torch.nn.init.constant_(m.weight.data, 0.)
            else:
                raise ValueError("Unknown reset type")
        if hasattr(m, 'bias') and m.bias is not None:
            torch.nn.init.constant_(m.bias.data, 0.)

    def set_normalization_params(self, mean, std):
        if self.normalize:
            std[std == 0.] = 1.
        self.std = std
        self.mean = mean

    def reset(self):
        self.apply(self._init_weights)

    def forward(self, *input):
        if self.normalize:
            input = (input.float() - self.mean.float()) / self.std.float()
        return NotImplementedError

class MultiLayerPerceptron(BaseModule):
    def __init__(self,config):
        super().__init__()
        self.config = config
        sizes = [self.config["in"]] + self.config["layers"]
        self.activation = activation_factory(self.config["activation"])
        layers_list = [
            nn.Linear(sizes[i],sizes[i + 1]) for i in range(len(sizes) - 1)
        ]
        self.layers = nn.ModuleList(layers_list)
        if self.config.get("out",None):
            self.predict = nn.Linear(sizes[-1],self.config["out"])

    @classmethod
    def default_config(cls,input_size = None,layers = [64,64], activation = "RELU", reshape = True, output_size = None):
        config = {"in": input_size,
                "layers": layers,
                "activation": activation,
                "reshape": reshape,
                "out": output_size}
        model = cls(config)
        return model

    def forward(self, x):
        if self.config["reshape"]:
            x = x.reshape(x.shape[0], -1)  # We expect a batch of vectors
        for layer in self.layers:
            x = self.activation(layer(x))
        if self.config.get("out", None):
            x = self.predict(x)
        return x
        

def activation_factory(activation_type):
    if activation_type == "RELU":
        return F.relu
    elif activation_type == "TANH":
        return torch.tanh
    else:
        raise ValueError("Unknown activation_type: {}".format(activation_type))

def model_factory(config: dict) -> nn.Module:
    if config["type"] == "MultiLayerPerceptron":
        return MultiLayerPerceptron.default_config(input_size=config["in"],layers=config["layers"],activation=config["activation"],reshape= True,output_size=config["out"])
    elif config["type"] == "DuelingNetwork":
        return DuelingNetwork(config)
    elif config["type"] == "ConvolutionalNetwork":
        return ConvolutionalNetwork(config)
    elif config["type"] == "EgoAttentionNetwork":
        return EgoAttentionNetwork(config)
    else:
        raise ValueError("Unknown model type")

def size_model_config(env, model_config):
    """
        Update the configuration of a model depending on the environment observation/action spaces

        Typically, the input/output sizes.

    :param env: an environment
    :param model_config: a model configuration
    """
    if model_config["type"] == "ConvolutionalNetwork":  # Assume CHW observation space
        model_config["in_channels"] = int(env.observation_space.shape[0])
        model_config["in_height"] = int(env.observation_space.shape[1])
        model_config["in_width"] = int(env.observation_space.shape[2])
    else:
        model_config["in"] = int(np.prod(env.observation_space.shape))
    model_config["out"] = env.action_space.n