#include "lmfit.hpp"
#include <iostream>

void evaluate_nonlin1(
    const double *p, int n, const void *data, double *f, int *info)
{
    f[0] = p[0]*p[0] + p[1]*p[1] - 1;
    f[1] = p[1] - p[0]*p[0];
}

int main( int argc, char **argv)
{
    int n = 2;
    std::vector<double> p;

    lm_control_struct control = lm_control_double;
    lm_status_struct status;
    control.verbosity = 31;

    /* get start values from command line */
    if (argc != 3 ){
        std::cout << "usage: nonlin1cpp x_start y_start" << '\n';
        exit(-1);
    }
    p.push_back( atof(argv[1]) );
    p.push_back( atof(argv[2]) );

    std::cout << "Minimization:" << '\n';
    lmfit::lmmin_cpp(n, &p, n, NULL, NULL, evaluate_nonlin1, &control, &status);

    std::cout << "\nlmmin status after " << status.nfev
        << " function evaluations:" << '\n';
    std::cout << lm_infmsg[status.outcome] << '\n';

    std::cout << '\n' << "Solution:\n";
    std::cout << "  x = " << p[0] << '\n';
    std::cout << "  y = " << p[1] << '\n';
    std::cout << "  d = " << status.fnorm << " => ";
    if (status.fnorm >= control.ftol)
        std::cout << "not a valid solution, try other starting values" << '\n';
    else
        std::cout << "valid, though not the only solution: try other starting values" << '\n';

    return 0;
}
