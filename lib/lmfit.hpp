/*
 * lmfit cpp wrapper
 *
 * Methods: fit_curve, minimize, fit
 *
 */

#ifndef LMFIT_HPP
#define LMFIT_HPP

#include <functional>
#include <vector>
#include <cassert>

extern "C" {
  #include "lmstruct.h"
  #include "lmmin.h"
  #include "lmcurve.h"
}

namespace lmfit{

typedef struct lm_result_struct{
    std::vector<double> par;
    std::vector<double> parerr;
    std::vector<double> covar;
    lm_status_struct status;
    lm_result_struct(std::vector<double>& start_par)
    {
        par = start_par;
        int n = par.size();
        parerr = std::vector<double>(n);
        covar = std::vector<double>(n*n);
    }
} lm_result_struct;

lm_result_struct fit_curve(std::vector<double>& par,
                    const std::vector<double>& t, const std::vector<double>& y,
                    double (*g)(const double t, const double* par),
                    const lm_control_struct* control)
{
    assert (t.size() == y.size());
    lm_result_struct res = lm_result_struct(par);
    lmcurve(par.size(), res.par.data(), t.size(), t.data(), y.data(),
            g, control, &res.status);
    return res;
}

lm_result_struct minimize(std::vector<double>& start_par,
                        const void *const data, const int m_dat,
                        void (*const evaluate)(
                            const double *const par, const int m_dat,
                            const void *const data, double *const fvec,
                            int *const userbreak),
                        const lm_control_struct *const control)
{
    lm_result_struct res = lm_result_struct(start_par);

    lmmin2(start_par.size(), res.par.data(), res.parerr.data(),
           res.covar.data(), m_dat, NULL, data, evaluate, control, &res.status);

    return res;
}

lm_result_struct fit(std::vector<double>& start_par,
                     std::vector<double>& y, const void *const data,
                     void (*const evaluate)(
                            const double *const par, const int m_dat,
                            const void *const data,
                            double *const fvec, int *const userbreak),
                     const lm_control_struct *const control)
{
    lm_result_struct res = lm_result_struct(start_par);

    lmmin2(start_par.size(), res.par.data(), res.parerr.data(),
           res.covar.data(), y.size(), y.data(), data, evaluate, control,
           &res.status);

    return res;
}



} //namespace lmfit


#endif /* LMFIT_HPP */
