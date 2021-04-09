#include "lmfit.hpp"
#include <iostream>

double f(double tx, double tz, const double *p)
{
    return p[0] + p[1]*tx + p[2]*tz;
}

typedef struct {
    double *tx, *tz;
    double *y;
    double (*f)(double tx, double tz, const double *p);
} data_struct;

void evaluate_surface(const double *par, int m_dat, const void *data,
                      double *fvec, int *info)
{
    data_struct *D;
    D = (data_struct*)data;

    int i;
    for (i = 0; i < m_dat; i++)
        fvec[i] = D->y[i] - D->f(D->tx[i], D->tz[i], par);
}

int main()
{
    int n_par = 3;
    std::vector<double> par{ -1, 0, 1 };

    int m_dat = 4;
    std::vector<double> tx{ -1, -1, 1, 1};
    std::vector<double> tz{ -1, 1, -1, 1};
    std::vector<double> y{ 0, 1, 1, 2};

    data_struct data = {tx.data(), tz.data(), y.data(), f};

    //lm_status_struct status;
    lm_control_struct control = lm_control_double;
    control.verbosity = 9;

    std::cout << "Fitting:" << '\n';
    //lmfit::lmmin_cpp(n_par, &par, m_dat, NULL, (const void*) &data,
    //                 evaluate_surface, &control, &status);
    auto result = lmfit::lm_min(n_par, par, m_dat, (const void*) &data,
                                &evaluate_surface, &control);

    std::cout << "\nResults:" << '\n';
    std::cout << "status after " << result.status.nfev
              << " function evaluations:\n" << lm_infmsg[result.status.outcome]
              << '\n';
    std::cout << "obtained parameters:" << '\n';
    int i;
    for (i = 0; i < n_par; ++i)
        std::cout << "par[" << i << "] = " << result.par[i] << '\n';

    if (result.status.fnorm < 1e-14) {
        std::cout << "SUCCESS (obtained norm = " << result.status.fnorm << ")\n";
        return 0;
    }
    std::cout << "FAILURE (obtained norm = " << result.status.fnorm << " is too large)\n";
    return 1;
}
