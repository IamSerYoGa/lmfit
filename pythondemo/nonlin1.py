import swig.pylmfit as pylm
import sys

def eval_nonlin(p, data=None):
    f0 = p[0]**2 + p[1]**2 - 1
    f1 = p[1] - p[0]**2
    return ([f0, f1], 0)

def nonlin1(p0, p1):
    par0 = pylm.VectorDouble([p0, p1])
    control = pylm.lm_control_double
    pylm.set_parlen(2)
    pylm.set_callback(eval_nonlin)

    print("Minimization:")
    result = pylm.minimize(par0, None, 2, pylm.function_eval, control)

    print(f"status after {result.status.nfev} function evaluations:")
    pylm.print_infmsg(result.status.outcome)

    print("\nSolution:")
    print(f"  x = {result.par[0]}")
    print(f"  y = {result.par[1]}")
    stat_str = "valid, though not the only solution: try other starting values"
    if (result.status.fnorm >= control.ftol):
        stat_str = "not a valid solution, try other starting values"
    print(f"  d = {result.status.fnorm} => {stat_str}")

if __name__ == "__main__":
    if (len(sys.argv) < 3):
        print("usage: python nonlin1.py x_start y_start")
    else:
        p0 = float(sys.argv[1])
        p1 = float(sys.argv[2])
        nonlin1(p0, p1)
