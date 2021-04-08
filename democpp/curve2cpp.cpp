#include "lmfit.hpp"
#include <iostream>
#include <vector>
double f(double t, std::vector<double> p)
{
    return p[0]+ p[1]*t + p[2]*t*t;
}

int main()
{
    int n = 3;
    std::vector<double> par{100, 0, -10};

    int m = 9;
    int i;
    std::vector<double> t{-4., -3., -2., -1., 0., 1., 2., 3., 4.};
    std::vector<double> y{16.6, 9.9, 4.4, 1.1, 0., 1.1, 4.2, 9.3, 16.4};
    std::vector<double> dy{4, 3, 2, 1, 2, 3, 4, 5, 6};

    lm_control_struct control = lm_control_double;
    lm_status_struct status;
    control.verbosity = 1;

    std::cout << "Fitting ..." << std::endl;

    lmfit::lmcurve_tyd_cpp(n, par, m, t, y, dy, f, &control, &status);

    std::cout << "Results:" << '\n';
    std::cout << "status after " << status.nfev << " function evaluations:" << '\n';
    std::cout << " " << lm_infmsg[status.outcome] << '\n';

    std::cout << "obtained parameters:" << '\n';
    for (i=0; i<n; ++i)
        std::cout << "  par[" << i << "] = " << par[i] << '\n';
    std::cout << "obtained norm:" << '\n' << status.fnorm << '\n';

    std::cout << "fitting data as follows:" << '\n';

}
