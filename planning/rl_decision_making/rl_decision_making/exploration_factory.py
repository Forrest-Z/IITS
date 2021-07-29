#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
import numpy as np
from gym.utils import seeding

class Boltzmann(object):
    """
        Uniform distribution with probability epsilon, and optimal action with probability 1-epsilon
    """

    def __init__(self, config=None):
        self.config = config
        self.action_space = config["action_space"]
        self.values = None

    @classmethod
    def default_config(cls,temperature = 0.5, action_space = [0,1,2]):
        config = dict(temperature = temperature,
                            action_space = action_space)
        bolt = cls(config)
        return bolt

    def get_distribution(self):
        actions = len(self.action_space)
        if self.config['temperature'] > 0:
            weights = np.exp(self.values / self.config['temperature'])
        else:
            weights = np.zeros((len(actions),))
            weights[np.argmax(self.values)] = 1
        return {action: weights[action] / np.sum(weights) for action in actions}

    def update(self, values, step_time=False):
        self.values = values

    def sample(self):
        """
        return: an action sampled from the distribution
        """
        distribution = self.get_distribution()
        return self.np_random.choice(list(distribution.keys()), 1, p=np.array(list(distribution.values())))[0]

    
    def seed(self, seed=None):
        """
            Seed the policy randomness source
        :param seed: the seed to be used
        :return: the used seed
        """
        self.np_random, seed = seeding.np_random(seed)
        return [seed]

class EpsilonGreedy(object):
    """
        Uniform distribution with probability epsilon, and optimal action with probability 1-epsilon
    """

    def __init__(self, config=None):
        self.config = config
        self.action_space = self.config["action_space"]
        self.config['final_temperature'] = min(self.config['temperature'], self.config['final_temperature'])
        self.optimal_action = None
        self.epsilon = 0
        self.time = 0
        self.writer = None
        self.seed()

    @classmethod
    def default_config(cls,temperature = 1.0, final_temperature = 0.1, tau = 5000, action_space = [0, 1, 2]):
        config = dict(temperature= 1.0,
                final_temperature= 0.1,
                tau = 5000,
                action_space = action_space
            )
        greedy = cls(config=config)
        return greedy

    def get_distribution(self):
        distribution = {action: self.epsilon / len(self.action_space) for action in range(len(self.action_space))}
        distribution[self.optimal_action] += 1 - self.epsilon
        return distribution

    def update(self, values, step_time=True):
        """
            Update the action distribution parameters
        :param values: the state-action values
        :param step_time: whether to update epsilon schedule
        """
        self.optimal_action = np.argmax(values)
        self.epsilon = self.config['final_temperature'] + \
            (self.config['temperature'] - self.config['final_temperature']) * \
            np.exp(- self.time / self.config['tau'])
        if step_time:
            self.time += 1
        if self.writer:
            self.writer.add_scalar('exploration/epsilon', self.epsilon, self.time)

    def set_time(self, time):
        self.time = time

    def set_writer(self, writer):
        self.writer = writer

    def sample(self):
        """
        :return: an action sampled from the distribution
        """
        distribution = self.get_distribution()
        return self.np_random.choice(list(distribution.keys()), 1, p=np.array(list(distribution.values())))[0]

    def seed(self, seed=None):
        """
            Seed the policy randomness source
        :param seed: the seed to be used
        :return: the used seed
        """
        self.np_random, seed = seeding.np_random(seed)
        return [seed]

class Greedy(object):
    """
        Always use the optimal action
    """

    def __init__(self, config=None):
        self.config = config
        self.action_space = self.config["action_space"]
        self.values = None
        self.seed()

    def get_distribution(self):
        optimal_action = np.argmax(self.values)
        return {action: 1 if action == optimal_action else 0 for action in range(len(self.action_space))}

    def update(self, values, step_time=False):
        self.values = values

    @classmethod
    def default_config(cls,action_space = [0, 1, 2]):
        config = dict(
                action_space = action_space
            )
        greedy = cls(config)
        return greedy

    def sample(self):
        """
        :return: an action sampled from the distribution
        """
        distribution = self.get_distribution()
        return self.np_random.choice(list(distribution.keys()), 1, p=np.array(list(distribution.values())))[0]

    
    def seed(self, seed=None):
        """
            Seed the policy randomness source
        :param seed: the seed to be used
        :return: the used seed
        """
        self.np_random, seed = seeding.np_random(seed)
        return [seed]


def exploration_factory(exploration_config):
    """
        Handles creation of exploration policies
    :param exploration_config: configuration dictionary of the policy, must contain a "method" key
    :param action_space: the environment action space
    :return: a new exploration policy
    """
    if exploration_config['method'] == 'Greedy':
        return Greedy.default_config(exploration_config['action_space'])
    elif exploration_config['method'] == 'EpsilonGreedy':
        return EpsilonGreedy.default_config(temperature=exploration_config["temperature"],final_temperature=exploration_config["final_temperature"],tau=exploration_config["tau"],action_space=exploration_config["action_space"])
    elif exploration_config['method'] == 'Boltzmann':
        return Boltzmann.default_config(temperature=exploration_config["temperature"],action_space = exploration_config["action_space"])
    else:
        raise ValueError("Unknown exploration method")

if __name__ == "__main__":
    exploration_config =  {
        "method": "EpsilonGreedy",
        "tau": 6000,
        "temperature": 1.0,
        "final_temperature": 0.05,
        "action_space":[0,1,2,3,4]
    }
    explor = exploration_factory(exploration_config)
    print(explor)
    print(explor.epsilon)
