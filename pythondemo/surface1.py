import swig.pylmfit as pylm

class Data_t(object):
    y: list()
    tx: list()
    tz: list()
    def __init__(self, y, tx, tz):
        self.y = y
        self.tx = tx
        self.tz = tz

    def f(self, tx, tz, p):
        return p[0] + p[1]*tx + p[2]*tz

def eval_surface(p, data=None):
    fvec = []
    for i in range(4):
        fvec.append(data.y[i] - data.f(data.tx[i], data.tz[i], p))
    return (fvec, 0)

def surface1():
    par0 = pylm.VectorDouble([-1, 0, 1])
    tx = [-1, -1, 1, 1]
    tz = [-1, 1, -1, 1]
    y = [0, 1, 1, 2]
    data = Data_t(y, tx, tz)
    wrap = pylm.Data_Wrap(data)
    pylm.set_parlen(3)
    pylm.set_callback(eval_surface)
    control = pylm.lm_control_double

    print("Fitting:")
    result = pylm.minimize(par0, pylm.to_void(wrap), 4, pylm.function_eval, control)

    print("\nResults:")
    print(f"status after {result.status.nfev} function evaluations:")
    pylm.print_infmsg(result.status.outcome)
    print("Obtained parameters:")
    for j in range(par0.size()):
        print(f"par[{j}] = {result.par[j]}")

    print("Fitting data as follows:")
    for i in range(len(tx)):
        ff = data.f(tx[i], tz[i], result.par)
        print(f"  t[{i}]={tx[i]},{tz[i]}  y={y[i]} fit={ff} residue={y[i]-ff}")

    if (result.status.fnorm > 1e-14):
        print(f"FAILURE (obtained norm = {result.status.fnorm} is too large)")
        return 1
    print(f"SUCCESS (obtained norm = {result.status.fnorm})")
    return 0

if __name__ == "__main__":
    print(surface1())
