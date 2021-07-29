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

from dqnagent import DQNAgent

logging.basicConfig(level = logging.INFO,format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s')
from utils import lmap

logger = logging.getLogger(__name__)


class RL_lc(object):
    SPEED_MAX = 16.67
    DEFAULT_WIDTH = 4
    LANE_NUM = 2
    SAVED_MODELS_FOLDER = 'planning/rl_decision_making/rl_decision_making/saved_models'
    def __init__(self,train = False,test = True,recover = True,num_episodes = 1000):
        self.agent = DQNAgent()
        self.recover = recover
        self.num_episodes = num_episodes 
        self.train = train
        self.test = test
        self.directory = os.getcwd()
        #create writer object,log will be saved in the filepath
        self.writer = SummaryWriter(str(os.path.join(self.directory,self.SAVED_MODELS_FOLDER)))
        if self.recover:
            self.load_agent_model(recover)
        self.steps = 0
        self.observation = None
        self.filtered_agent_stats = 0
        self.best_agent_stats = -np.infty, 0 #Negative infinity

    def train(self):
        self.train = True
        self.run_episodes()
        self.close()

    def run_episodes(self):
        for episode in range(self.num_episodes):
            terminal = False
            observation = self.reset()
            rewards = []
            while not terminal:
                reward,terminal = self.step()
                rewards.append(reward)  
            self.after_all_episodes(episode,rewards)
            self.after_some_episodes(episode,rewards)

    def step(self):
        if not self.observation:
            raise Exception("The agent did not get any onservation")
        actions = self.agent.plan(self.normalize_obs(self.observation))
        if not actions:
            raise Exception("The agent did not plan any action")
        previous_observation, action = observation, actions[0]
        #TODO self.observation,reward,terminal,info = env.step()
        try:
            self.agent.record(previous_observation, action,reward,self.observation,terminal,info)
        except NotImplementedError:
            pass
        return reward,terminal

    def lanechange(self,observation):
        observation = self.normalize_obs(observation)
        print(observation)
        if self.test:
            self.agent.eval()
            lc = self.agent.plan(observation)
        return lc

    
    def normalize_obs(self,obs):
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
        return obs

    def reset(self):
        pass

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
        permanent_folder = os.path.join(self.directory,self.SAVED_MODELS_FOLDER)
        os.makedirs(permanent_folder, exist_ok=True)
        episode_path = None
        if do_save:
            episode_path = os.path.join(self.permanent_folder,"checkpoint-{}.tar".format(identifier))
            try:
                self.agent.save(filename=os.path.join(permanent_folder , "latest.tar"))
                episode_path = self.agent.save(filename=episode_path)
                if episode_path:
                    logger.info("Saved {} model to {}".format(self.agent.__class__.__name__, episode_path))
            except NotImplementedError:
                pass
        return episode_path

    def after_all_episodes(self, episode, rewards):
        rewards = np.array(rewards)
        gamma = self.agent.config.get("gamma", 1)
        self.writer.add_scalar('episode/length', len(rewards), episode)
        self.writer.add_scalar('episode/total_reward', sum(rewards), episode)
        self.writer.add_scalar('episode/return', sum(r*gamma**t for t, r in enumerate(rewards)), episode)
        self.writer.add_histogram('episode/rewards', rewards, episode)
        logger.info("Episode {} score: {:.1f}".format(episode, sum(rewards))) 

    def after_some_episodes(self, episode, rewards,
                        best_increase=1.1,
                        episodes_window=50):
        if self.training:
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

if __name__ == "__main__":
    rl =RL_lc(recover=True)
    observation = np.ones((7,6))
    print(observation)
    print(type(observation))
    rl.lanechange(observation)