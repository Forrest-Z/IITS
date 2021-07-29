from os.path import dirname, join as pjoin
import scipy.io as sio
import os 
import numpy as np
import math

try:
    #### for release #####
    from trajectory_planner.pcc.calc_fc import FuelModel
    from trajectory_planner.pcc.precalc_s_numerical import precalc_s_numerical
    from trajectory_planner.pcc.calc_k import optimizer
except:
    #### for debug #####
    from pcc.calc_fc import FuelModel
    from pcc.precalc_s_numerical import precalc_s_numerical
    from pcc.calc_k import optimizer

class PCC_algorithm(object):
    def __init__(self):

        # self.v0 = 72/3.6
        # self.vf = 72/3.6
        # self.t_pred = 100
        # self.offset = 1000
        # self.dist = 0.5*(self.v0 + self.vf)*self.t_pred
        # self.total_time = self.t_pred
        # self.altimap_jinan = sio.loadmat('/home/dawei/fead_ws/src/planning/trajectory_planner/trajectory_planner/pcc/altimap_jinan.mat')
        # ALTI_X = np.squeeze(np.array(self.altimap_jinan['altimap']['s'].tolist()[0][0]))
        # ALTI = np.squeeze(np.array(self.altimap_jinan['altimap']['z'].tolist()[0][0]))


        self.Mveh = 55e3   # vehicle mass [kg]
        self.fuel_model = FuelModel(self.Mveh)

        self.dt = 0.1
        # self.nelem = math.floor(self.total_time/self.dt) #total step
        # self.nnode = self.nelem + 1
        # self.ndof = self.nnode*2


        #% pertubation grid size
        self.h_a = 0.5
        self.h_v = 0.5
        self.s = precalc_s_numerical(self.dt, self.h_a, self.h_v)

        # self.opt = optimizer(self.nelem, self.dt, self.Mveh, self.fuel_model, self.s, ALTI_X, ALTI)

    def const_speed_planner(self, num_waypoints, target_velocity):
        return np.zeros(num_waypoints)

    def pcc_speed_planner(self, grad_x, grad_h, target_speed):
        ## define parameters:
        self.v0 = target_speed
        self.vf = target_speed
        self.dist = grad_x[-1]
        self.dt = (self.dist/target_speed)/len(grad_x)
        self.s = precalc_s_numerical(self.dt, self.h_a, self.h_v)
        
        self.nelem = len(grad_x)-1 #total step
        self.nnode = self.nelem + 1
        self.ndof = self.nnode*2

        self.opt = optimizer(self.nelem, self.dt, self.Mveh, self.fuel_model, self.s, grad_x, grad_h)
        time = [i*self.dt for i in range(self.nelem)]
        Kg0 = np.zeros((self.ndof,self.ndof))
        Fg0 = np.zeros((self.ndof, 1))
        Q0 = np.zeros((self.ndof, 1))
        Ke, Fe, F_int, Kg, Fg, Fg_int, _ = self.opt.calc_k( Q0, 1 )
        C = 1e5
        Kp = np.zeros((self.ndof,self.ndof))
        Kp[0, 0] = C
        Kp[1, 1] = C
        Kp[-2, -2] = C
        Kp[-1, -1] = C
        Fp = np.zeros((self.ndof, 1))
        Fp[0] = 0*C
        Fp[1] = self.v0*C
        Fp[-2] = self.dist*C
        Fp[-1] = self.vf*C
        Q1 = np.linalg.inv(Kg + Kp).dot(Fg + Fp)

        # % generate initial solution
        Q = Q1
        Ge1 = 0
        for i in range (250):
            [Ke, Fe, Fe_int, Kg, Fg, Fg_int, Ge] = self.opt.calc_k(Q,0)
            try:
                Q = Q - np.linalg.inv(Kg + Kp).dot(Fg_int - Fg)*0.01
            except:
                print("error in np.linalg.inv, singular matrix, cannot update")
                break
            if i == 0:
                Ge1 = Ge
            Q[0] = 0
            Q[1] = self.v0
            Q[-1] = self.vf
            Q[-2] = self.dist
            zero = np.zeros((self.ndof,1))
            Q = np.maximum(Q, zero)
            if (i/50) == math.floor(i/50):
                # x1 = Q1[1 : 2 : end - 1]
                x1 = [Q1[i] for i in range(0,len(Q1)-1,2)]
                # v1 = Q1(2 : 2 : end)
                v1 = [Q1[i] for i in range(1,len(Q1),2)]
                fuel1 = np.zeros((self.nnode, 1))
                pe1 = np.zeros((self.nnode, 1))
                grad1 = np.zeros((self.nnode, 1))
                # x = Q(1 : 2 : end - 1)
                x = [Q[i][0] for i in range(0, len(Q)-1,2)]
                # v = Q(2 : 2 : end)
                v = [Q[i][0] for i in range(1, len(Q), 2)]
                fuel = np.zeros((self.nnode, 1))
                pe = np.zeros((self.nnode, 1))
                grad = np.zeros((self.nnode, 1))

                for itime in range(0, self.nnode - 1):
                    ve1 = (v1[itime + 1] + v1[itime])/2
                    ae1 = (v1[itime + 1] - v1[itime])/self.dt
                    fc1, pe1[itime], _  = self.fuel_model.calc_fc( ae1, ve1, Ge1[itime])
                    fuel1[itime + 1] = fuel1[itime] + fc1*self.dt
                    grad1[itime] = Ge1[itime]
                    
                    ve = (v[itime + 1] + v[itime])/2
                    ae = (v[itime + 1] - v[itime])/self.dt
                    fc, pe[itime],_  = self.fuel_model.calc_fc( ae, ve, Ge[itime])
                    fuel[itime + 1] = fuel[itime] + fc*self.dt
                    grad[itime] = Ge[itime]
                pe1[-1] = pe1[itime]
                pe[-1] = pe[itime]
                grad1[-1] = grad1[itime]
                grad[-1] = grad[itime]
        return v, x

def _calc_relative_x(self, waypoint_buffer):
    def calc_distance(x1,y1,x2,y2):
        return math.sqrt((x1-x2)**2+(y1-y2)**2)
    x = [0]
    for i in range(len(waypoint_buffer)-1):
        x.append(x[i]+calc_distance(waypoint_buffer[i][0], waypoint_buffer[i][1], waypoint_buffer[i+1][0], waypoint_buffer[i+1][1]))
    return x

if __name__ == "__main__":
    altimap_jinan = sio.loadmat('/Users/daweiwang/Desktop/fead/planning/trajectory_planner/trajectory_planner/pcc/altimap_jinan.mat')
    ALTI_X = np.squeeze(np.array(altimap_jinan['altimap']['s'].tolist()[0][0]))
    ALTI = np.squeeze(np.array(altimap_jinan['altimap']['z'].tolist()[0][0]))

    x = ALTI_X[:10]
    h = ALTI[:10]
    # x = [0, 2000, 3000, 4000, 5000, 6000]
    # h = [0,    0,   -30,   -30,    0,   0]
    speed_planner = PCC_algorithm()
    vp, xp = speed_planner.pcc_speed_planner(x, h, 20.0)
    print(vp)
    print(xp)