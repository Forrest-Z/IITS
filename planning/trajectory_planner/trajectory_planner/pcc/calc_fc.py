import math
from scipy import interpolate
import numpy as np

class FuelModel(object):
    def __init__(self, Mveh):
        self.cd = 0.398125
        self.front_area = 9.773749
        self.mu = 0.012
        self.Mveh = Mveh
        self.gb_eff = 0.931
        self.bsfc = np.array([203.677,193.671,190.933076923077,187.523076923077,
                    185.423076923077,184.325384615385,184,185.933846153846,
                    188.483846153846,192.326153846154,198.624390243902])
        self.bsfc_pe = np.array([39584.0674352314,78749.2558499842,119380.520836412,
                            158964.588271644,198548.655706875,239598.799713782,247766.940613115,
                            280439.504210449,321280.208707116,360654.836632108,402123.859659494])
        self.fc = interpolate.interp1d(self.bsfc_pe, self.bsfc, kind='linear', fill_value='extrapolate')


    def calc_fuel(self, x, v, grad): 
    
        v = np.array(v)/3.6

        grad_x = []
        for i in range(len(grad)):
            grad_x.append(float(x[-1])*i/(len(grad)-1))
        gf = interpolate.interp1d(grad_x, grad, kind='linear', fill_value='extrapolate')
        grad = gf(x)

        a = []
        for i in range(1,len(x)):
            dt = 2*(x[i] - x[i-1])/(v[i-1]+v[i])
            a.append((v[i] - v[i-1])/dt)
        a.append(a[-1])
        v = np.array(v)
        grad = np.array(grad)
        x = np.array(x)
        a = np.array(a)
        Frl = np.power(self.cd*self.front_area*v,2) + self.mu*self.Mveh*9.801*np.cos(grad)
        Fgr = self.Mveh*9.801*np.sin(grad)
        Fac = a*self.Mveh

        pe = np.multiply((Frl + Fgr + Fac),v)/self.gb_eff
        pe_pos = (pe + abs(pe))/2
        bsfc = self.fc(pe_pos)/3.6e6
        fc = bsfc*pe_pos + 0.5
        fuel = 0
        for i in range(1,len(x)):
            dt = (x[i] - x[i-1])/v[i-1]
            fuel += fc[i-1]*dt 
        fcp = fc + 0.5*a^2 + 5000*(a - 1.5)^2.*(abs(a)>1.5)
        return fcp, pe, fc
        # fcp = fc + 0.5*a.^2 + 5000*(a - 1.5).^2.*(abs(a)>1.5)

    def calc_fc(self, a, v, grad): 
    
        # v = np.array(v)/3.6

        # grad_x = []
        # for i in range(len(grad)):
        #     grad_x.append(float(x[-1])*i/(len(grad)-1))
        # gf = interpolate.interp1d(grad_x, grad, kind='linear', fill_value='extrapolate')
        # grad = gf(x)
        v = np.array(v)
        grad = np.array(grad)
        # x = np.array(x)
        Frl = self.cd*self.front_area*v**2 + self.mu*self.Mveh*9.801*np.cos(grad)
        Fgr = self.Mveh*9.801*np.sin(grad)
        Fac = a*self.Mveh

        pe = np.multiply((Frl + Fgr + Fac),v)/self.gb_eff
        pe_pos = (pe + abs(pe))/2
        bsfc = self.fc(pe_pos)/3.6e6
        fc = bsfc*pe_pos + 0.5
        # fuel = 0
        # for i in range(1,len(x)):
        #     dt = (x[i] - x[i-1])/v[i-1]
        #     fuel += fc[i-1]*dt 
        fcp = fc + 0.5*a**2 + 5000*(a - 1.5)**2.*(abs(a)>1.5)
        return fcp, pe, fc
        # fcp = fc + 0.5*a.^2 + 5000*(a - 1.5).^2.*(abs(a)>1.5)