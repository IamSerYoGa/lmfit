#include "lmfit.hpp"
#include <iostream>

double f(double tx, double tz, const double *p)
{
    return p[0] + p[1]*tx + p[2]*tz;
}

typedef struct {
    const double *tx;
    const double *tz;
    const double *y;
    double (*const f)(double tx, double tz, const double *p);
} data_struct;

void evaluate_surface(const double *par, int m_dat, const void *data,
                      double *fvec, int *info)
{
    data_struct *D = (data_struct*)data;

    for (int i = 0; i < m_dat; i++)
        fvec[i] = D->y[i] - D->f(D->tx[i], D->tz[i], par);
}

int main()
{
    std::vector<double> par0{ -1, 0, 1 };

    const std::vector<double> tx{ -1, -1, 1, 1};
    const std::vector<double> tz{ -1, 1, -1, 1};
    const std::vector<double> y{ 0, 1, 1, 2};
    const int m_dat = y.size();
    assert((int) tx.size() == m_dat);
    assert((int) tz.size() == m_dat);

    const data_struct data = {tx.data(), tz.data(), y.data(), f};

    lm_control_struct control = lm_control_double;
    control.verbosity = 9;

    std::cout << "Fitting:" << '\n';
    auto result = lmfit::minimize(par0, (const void*) &data, m_dat, &evaluate_surface, &control);

    std::cout << "\nResults:" << '\n';
    std::cout << "status after " << result.status.nfev
              << " function evaluations:\n" << lm_infmsg[result.status.outcome]
              << '\n';
    std::cout << "obtained parameters:" << '\n';
    for (size_t j = 0; j < result.par.size(); ++j)
        std::cout << "par[" << j << "] = " << result.par[j] << '\n';

    if (result.status.fnorm > 1e-14) {
        std::cout << "FAILURE (obtained norm = " << result.status.fnorm << " is too large)\n";
        return 1;
    }
    std::cout << "SUCCESS (obtained norm = " << result.status.fnorm << ")\n";
    return 0;
}
