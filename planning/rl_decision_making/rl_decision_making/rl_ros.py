#!/usr/bin/python3
#
# Copyright (c) 2020 Inceptio
#
import datetime
import random
import json
import logging
import os
import math
from multiprocessing.pool import Pool
from pathlib import Path
import numpy as np
from tensorboardX import SummaryWriter
import torch as nn
import copy
try:
    from utils import lmap
    from dqnagent import DQNAgent
except:
    from rl_decision_making.utils import lmap
    from rl_decision_making.dqnagent import DQNAgent


from collections import deque

logging.basicConfig(level = logging.INFO,format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)


class RL_lc(object):
    SPEED_MAX = 20.0
    DEFAULT_WIDTH = 4
    LANE_NUM = 2
    NUM_HISTORY = 32
    SAVED_MODELS_FOLDER = 'saved_models'
    def __init__(self,train = False,recover = False,num_episodes = 1000):
        self.agent = DQNAgent()
        self.recover = recover
        self.num_episodes = num_episodes 
        self.train = train
        self.test = not train
        self.directory = os.getcwd()
        #create writer object,log will be saved in the filepath
        self.writer = SummaryWriter(str(os.path.join(self.directory,self.SAVED_MODELS_FOLDER)))
        if self.recover:
            self.load_agent_model(recover)
        self.steps = 0
        self.observation = None
        self.filtered_agent_stats = 0
        self.best_agent_stats = -np.infty, 0 #Negative infinity
        self.history_obs = self.get_obs_deque(num_history = self.NUM_HISTORY)
        self.use_histroy = True

    def set_mode(self):
        if self.use_histroy == True:
            self.agent.config['model']['in'] = 168

    def get_action(self,observation):
        if observation is None:
            raise Exception("The agent did not get any observation")      
        if self.test:
            self.agent.eval()
    
        actions = self.agent.plan(observation)
        if not actions:
            raise Exception("The agent did not plan any action")
        action =actions[0]
        return action
        
    def record(self,observation, action,reward,next_observation,done,info):
        return self.agent.record(observation,action,reward,next_observation,done,info)

    def get_obs_deque(self,num_history):
        init_ob_deque = deque(maxlen=num_history)
        for i in range(num_history):
            init_ob_deque.append(np.zeros((9,6)))
        return init_ob_deque

    def init_obs_deque(self):
        for i in range(self.NUM_HISTORY):
            self.history_obs.append(np.zeros((9,6)))


    def lanechange(self,observation):
        observation = self.normalize_obs(observation)
        if self.test:
            self.agent.eval()
            lc = self.agent.plan(observation)
    
    def normalize_obs(self,obs_input):
        obs = copy.deepcopy(obs_input)
        self.feattures_range={
                "x": [-5.0 * self.SPEED_MAX, 5.0 * self.SPEED_MAX],
                "y": [ -self.DEFAULT_WIDTH * self.LANE_NUM, self.DEFAULT_WIDTH * self.LANE_NUM],
                "vx": [-2 * self.SPEED_MAX, 2 * self.SPEED_MAX],
                "vy": [-2 * self.SPEED_MAX, 2 * self.SPEED_MAX]}
        for row in range(len(obs)):
            for col in range(len(obs[row])):
                if row == 0 and col == 1:
                    obs[row][col] = 1.0
                    continue
                if col == 1 :
                    obs[row][col] =np.clip(lmap(obs[row][col], [self.feattures_range['x'][0], self.feattures_range['x'][1]],[-1,1]), -1, 1)
                if col == 2:
                    obs[row][col] =np.clip(lmap(obs[row][col], [self.feattures_range['y'][0], self.feattures_range['y'][1]],[-1,1]), -1, 1)
                if col == 3 or col ==5:
                    obs[row][col] =np.clip(lmap(obs[row][col], [self.feattures_range['vx'][0], self.feattures_range['vx'][1]],[-1,1]), -1, 1)
                if col == 4:
                    obs[row][col] =np.clip(lmap(obs[row][col], [self.feattures_range['vy'][0], self.feattures_range['vy'][1]],[-1,1]), -1, 1)
                # print(obs[row][col])  
        return obs

    def load_agent_model(self, model_path):
        if model_path is True:
            model_path = os.path.join(self.directory , self.SAVED_MODELS_FOLDER , "latest.tar")
        if isinstance(model_path, str):
            model_path = Path(model_path)
            if not model_path.exists():
                model_path = os.path.join(self.directory ,self.SAVED_MODELS_FOLDER , model_path)
        try:
            model_path = self.agent.load(filename=model_path)
            if model_path:
                logger.info("Loaded {} model from {}".format(self.agent.__class__.__name__, model_path))
        except FileNotFoundError:
            logger.warning("No pre-trained model found at the desired location.")
        except NotImplementedError:
            pass

    def save_agent_model(self, identifier, do_save=True):
        # Create the folder if it doesn't exist
        self.permanent_folder = os.path.join(self.directory,self.SAVED_MODELS_FOLDER)
        os.makedirs(self.permanent_folder, exist_ok=True)
        episode_path = None
        if do_save:
            episode_path = os.path.join(self.permanent_folder,"checkpoint-{}.tar".format(identifier))
            try:
                self.agent.save(filename=os.path.join(self.permanent_folder , "latest.tar"))
                episode_path = self.agent.save(filename=episode_path)
                if episode_path:
                    logger.info("Saved {} model to {}".format(self.agent.__class__.__name__, episode_path))
            except NotImplementedError:
                pass
        return episode_path

    def after_all_episodes(self, episode, rewards, speed_error, loss, step):
        rewards = np.array(rewards)
        loss = np.array(loss)
        speed_error = np.array(speed_error)
        gamma = self.agent.config.get("gamma", 1)
        self.writer.add_scalar('episode/length', len(rewards), episode)
        self.writer.add_scalar('episode/total_reward', sum(rewards)/step, episode)
        self.writer.add_scalar('episode/return', sum(r*gamma**t for t, r in enumerate(rewards)), episode)
        self.writer.add_scalar('episode/speed_error', sum(speed_error)/step, episode)
        self.writer.add_scalar('episode/loss', sum(loss)/step, episode)
        self.writer.add_histogram('episode/rewards', rewards, episode)
        logger.info("Episode {} score: {:.1f}".format(episode, sum(rewards))) 

    def after_some_episodes(self, episode, rewards,
                        best_increase=1.1,
                        episodes_window=50):
        if self.train:
            self.save_agent_model(episode)
            # Save best model so far, averaged on a window
            best_reward, best_episode = self.best_agent_stats
            self.filtered_agent_stats += 1 / episodes_window * (np.sum(rewards) - self.filtered_agent_stats)
            if self.filtered_agent_stats > best_increase * best_reward \
                    and episode >= best_episode + episodes_window:
                self.best_agent_stats = (self.filtered_agent_stats, episode)
                self.save_agent_model("best")

    def close(self):
        if self.train:
            self.save_agent_model("final")
            self.writer.close()

    def store_history(self,observation):
        self.history_obs.append(observation)
        currobs_list = [self.history_obs[self.NUM_HISTORY - 1], 
                        self.history_obs[self.NUM_HISTORY - 11],
                        self.history_obs[self.NUM_HISTORY - 21],
                        self.history_obs[self.NUM_HISTORY - 31]]
        currobs = np.vstack((currobs_list[0],currobs_list[1],currobs_list[2],currobs_list[3]))

        preobs_list = [self.history_obs[self.NUM_HISTORY - 2], 
                        self.history_obs[self.NUM_HISTORY - 12],
                        self.history_obs[self.NUM_HISTORY - 22],
                        self.history_obs[self.NUM_HISTORY - 32]]
        preobs = np.vstack((preobs_list[0],preobs_list[1],preobs_list[2],preobs_list[3]))
        
        return currobs,preobs


if __name__ == "__main__":
    rl = RL_lc()
    curr,pre = rl.store_history(np.ones((9,6)))
    print(curr)
    print(pre)
    
     
