#include "lmfit.hpp"
#include <iostream>

double f(const double t, const double* p)
{
    return p[0] + p[1]*t + p[2]*t*t;
}

int main()
{
    int n = 3;
    std::vector<double> par{ 100, 0, -10 };

    int m = 9;
    int i;
    std::vector<double> t{ -4., -3., -2., -1.,  0., 1.,  2.,  3.,  4. };
    std::vector<double> y{ 16.6, 9.9, 4.4, 1.1, 0., 1.1, 4.2, 9.3, 16.4 };

    lm_control_struct control = lm_control_double;
    lm_status_struct status;
    control.verbosity = 9;

    std::cout << "Fitting..." << '\n';
    lmfit::lmcurve_cpp(n, par, m, t, y, f, &control, &status);

    std::cout << "Results:" << '\n';
    std::cout << "status after " << status.nfev << " function evaluations:" << '\n';
    std::cout << lm_infmsg[status.outcome] << '\n';

    std::cout << "Obtained parameters:" << '\n';
    for (i = 0; i < n; ++i)
        std::cout << "par[" << i << "] = " << par[i] << '\n';
    std::cout << "Obtained norm:" << '\n';
    std::cout << status.fnorm << '\n';

    std::cout << "fitting data as follows:" << '\n';
    for (i = 0; i < m; ++i) {
        std::cout << "t[" << i << "]= " << t[i] << '\n';
    }

    if (status.outcome <= 3) {
        std::cout << "SUCCESS" << '\n';
        return 0;
    }
    std::cout << "FAILURE" << '\n';
    return 1;
}
