import numpy as np
import math
from scipy import interpolate

class optimizer(object):
    def __init__(self, nelem, dt, Mveh, fuel_estimator, s , ALTI_X, ALTI):
        self.nelem = nelem
        self.dt = dt
        self.Mveh = Mveh
        self.s = s
        self.fuel_estimator = fuel_estimator
        self.ALTI_X = ALTI_X
        self.ALTI = ALTI

    
    def calc_k(self, Q, f_init):
        ndof = (self.nelem + 1)*2
        Kg = np.zeros((ndof,ndof))
        Fg = np.zeros((ndof, 1))
        Fg_int = np.zeros((ndof, 1))

        Ke = np.zeros((4, 4, self.nelem))
        Fe = np.zeros((4, self.nelem))
        Fe_int = np.zeros((4, self.nelem))

        x_node = self.ALTI_X
        # x_node[0] = x_node[0]+offset
        # for i in range(1, self.nelem):
        #     x_node[i] = x_node[i]+offset
        # gt = interpolate.interp1d(self.ALTI_X, self.ALTI, kind='linear', fill_value='extrapolate')
        h_node = self.ALTI
        dx_elem = np.array([x_node[i+1] - x_node[i] for i in range(0, len(x_node)-1)])
        dh_elem = np.array([h_node[i+1] - h_node[i] for i in range(0, len(h_node)-1)])
        Ge = dh_elem/dx_elem

        for ielem in range(self.nelem):
            inode1 = ielem
            inode2 = ielem + 1
            idof_x1 = inode1*2 
            # idof_v1 = inode1*2
            # idof_x2 = inode2*2 - 1
            idof_v2 = inode2*2 +2
            # x1 = Q[idof_x1]
            # v1 = Q[idof_v1]
            # x2 = Q[idof_x2]
            # v2 = Q[idof_v2]
            Qe = np.array([Q[i] for i in range(idof_x1,idof_v2)])
            g_e = Ge[ielem]
            
            for iga in range(3):
                q = self.s.Np[:, :, iga].T.dot(Qe)
                vga = q[0]
                aga = q[1]
                
                
                fc,_,_ = self.fuel_estimator.calc_fc(aga + self.s.da, vga + self.s.dv, g_e)
                fc_cond = fc - fc[4]
                if f_init == 1:
                    m = [1,0,0,0,0,0]
                else:
                    m = np.linalg.inv(self.s.pp).dot(self.s.p.T.dot(fc_cond))

                C1 = np.zeros((2,2))
                C2 = [[0, 0],[2*m[1], m[2]]]
                C3 = np.zeros((2,2))
                C4 = [[2*m[1], m[2]],[m[2], 2*m[0]]]
                B1 = [[0],[m[4]]]
                B2 = [[m[4]],[m[3]]]
                Kga = self.s.N[:, :, iga].dot(C1).dot(self.s.N[:, :, iga].T)\
                    + self.s.N[:, :, iga].dot(C2).dot(self.s.Np[:, :, iga].T)\
                    + self.s.Np[:, :, iga].dot(C3).dot(self.s.N[:, :, iga].T) + self.s.Np[:, :, iga].dot(C4).dot(self.s.Np[:, :, iga].T)
                
                Fga = self.s.N[:, :, iga].dot(B1) + self.s.Np[:, :, iga].dot(B2)

                Ke[:, :, ielem] = Ke[:, :, ielem] + Kga*(self.dt)/2
                Fe[:, ielem] = Fe[:, ielem] - np.squeeze(Fga)*(self.dt)/2
                
            Fe_int[:, ielem] = np.squeeze(Ke[:, :, ielem].dot(Qe))
            
            Kg[idof_x1 : idof_v2, idof_x1 : idof_v2] = \
                Kg[idof_x1 : idof_v2, idof_x1 : idof_v2] + Ke[:, :, ielem]

            Fg[idof_x1 : idof_v2] = Fg[idof_x1 : idof_v2] + np.reshape(Fe[:, ielem],(4,1))

            Fg_int[idof_x1 : idof_v2] = Fg_int[idof_x1 : idof_v2] + np.reshape(Fe_int[:, ielem],(4,1))


        return Ke, Fe, Fe_int, Kg, Fg, Fg_int, Ge 