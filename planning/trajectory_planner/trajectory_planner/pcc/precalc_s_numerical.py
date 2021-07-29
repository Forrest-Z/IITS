import numpy as np


class precalc_s_numerical(object):
    def __init__(self, dt, h_a, h_v):
        self.dt = dt
        self.h_a = h_a
        self.h_v = h_v
        self.h = dt
        self.K = np.zeros((4, 4, 3, 4))
        self.cal_kwn()

    def cal_kwn(self):
        h = self.h
        Ng1 = np.array([[(3*15**(1/2))/25 + 1/2,-3/(5*h)],[(h*(15**(1/2) + 5))/100, 15**(1/2)/10 + 1/5],\
            [1/2 - (3*15**(1/2))/25,3/(5*h)],[(h*(15**(1/2) - 5))/100, 1/5 - 15**(1/2)/10]])

        Ng2 = np.array([[1/2, -3/(2*h)],[h/8,-1/4],[1/2,  3/(2*h)],[-h/8, -1/4]])

        Ng3 = np.array([[1/2 - (3*15**(1/2))/25,-3/(5*h)],[-(h*(15**(1/2) - 5))/100, 1/5 - 15**(1/2)/10],\
            [(3*15**(1/2))/25 + 1/2,3/(5*h)],[ -(h*(15**(1/2) + 5))/100, 15**(1/2)/10 + 1/5]])
        
        Npg1 = np.array([[-3/(5*h),-(6*15**(1/2))/(5*h**2)],[15**(1/2)/10 + 1/5, -((3*15**(1/2))/5 + 1)/h],\
            [3/(5*h),(6*15**(1/2))/(5*h**2)],[1/5 - 15**(1/2)/10, -((3*15**(1/2))/5 - 1)/h]])
        
        Npg2 = np.array([[-3/(2*h),0],[-1/4, -1/h],\
            [ 3/(2*h),0],[-1/4,1/h]])

        Npg3 = np.array([[ -3/(5*h),(6*15**(1/2))/(5*h**2)],\
            [1/5 - 15**(1/2)/10, ((3*15**(1/2))/5 - 1)/h],\
                [3/(5*h),  -(6*15**(1/2))/(5*h**2)],\
            [ 15**(1/2)/10 + 1/5, ((3*15**(1/2))/5 + 1)/h]])

        self.K[:, :, 0, 0] = Ng1.dot(Ng1.T)
        self.K[:, :, 1, 0] = Ng2.dot(Ng2.T)
        self.K[:, :, 2, 0] = Ng3.dot(Ng3.T)

        self.K[:, :, 0, 1] = Ng1.dot(Npg1.T)
        self.K[:, :, 1, 1] = Ng2.dot(Npg2.T)
        self.K[:, :, 2, 1] = Ng3.dot(Npg3.T)

        self.K[:, :, 0, 2] = Npg1.dot(Ng1.T)
        self.K[:, :, 1, 2] = Npg2.dot(Ng2.T)
        self.K[:, :, 2, 2] = Npg3.dot(Ng3.T)

        self.K[:, :, 0, 3] = Npg1.dot(Npg1.T)
        self.K[:, :, 1, 3] = Npg2.dot(Npg2.T)
        self.K[:, :, 2, 3] = Npg3.dot(Npg3.T)

        wg1 = 5/9
        wg2 = 8/9
        wg3 = 5/9
        self.w = [[wg1],[wg2],[wg3]]

        self.N = np.zeros((4, 2, 3))
        self.N[:, :, 0] = Ng1
        self.N[:, :, 1] = Ng2
        self.N[:, :, 2] = Ng3

        self.Np = np.zeros((4, 2, 3))
        self.Np[:, :, 0] = Npg1
        self.Np[:, :, 1] = Npg2
        self.Np[:, :, 2] = Npg3

        self.da = np.array([-1,  0,  1, -1,  0,  1, -1,  0,  1]).T.dot(self.h_a)
        self.dv = np.array([-1, -1, -1,  0,  0,  0,  1,  1,  1]).T.dot(self.h_v)
        self.p = np.array([(self.da**2).tolist(), np.power(self.dv,2).tolist(),self.da*(self.dv).tolist(),self.da.tolist(),self.dv.tolist()]).T
        self.pp = self.p.T.dot(self.p)


