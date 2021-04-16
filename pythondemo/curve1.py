import swig.pylmfit as pylm

def f(t, p):
    return p[0] + p[1]*t + p[2]*t**2

def curve1():
    par0 = pylm.VectorDouble([100, 0, -10])
    t = pylm.VectorDouble([-4, -3, -2, -1, 0, 1, 2, 3, 4])
    y = pylm.VectorDouble([16.6, 9.9, 4.4, 1.1, 0, 1.1, 4.2, 9.3, 16.4])
    control = pylm.lm_control_double
    pylm.set_parlen(3)
    pylm.set_callback(f)

    print("Fitting...")
    result = pylm.fit_curve(par0, t, y, pylm.function_g, control)

    print("Results:")
    print(f"status after {result.status.nfev} function evaluations:")
    pylm.print_infmsg(result.status.outcome)

    print("Obtained parameters:")
    for j in range(pylm.parlen()):
        print(f"par[{j}] = {result.par[j]}")
    print("Obtained norm:")
    print(result.status.fnorm)

    print("fitting data as follows:")
    for i in range(t.size()):
        fi = f(t[i], result.par)
        print(f"t[{i}] = {t[i]}  y = {y[i]}  fit = {fi}  residue = {y[i]-fi}")

    if (result.status.outcome > 3):
        print("FAILURE")
        return 1
    print("SUCCESS")
    return 0

if __name__ == "__main__":
    print(curve1())
