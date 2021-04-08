/*
 * lmfit cpp wrapper
 *
 * Methods: lmmin_cpp, lmmin2_cpp, lmcurve_cpp
 *
 */

#ifndef LMFIT_HPP
#define LMFIT_HPP

#include <functional>
#include <vector>

extern "C" {
  #include "lmdecls.h"
  #include "lmstruct.h"
  #include "lmmin.h"
  #include "lmcurve.h"
//  #include "lmcurve_tyd.h"
}
#include <iostream>
__BEGIN_DECLS

namespace lmfit{

typedef struct {
    std::vector<double> par;
    std::vector<double> parerr;
    std::vector<double> covar;
    lm_status_struct status;
} lm_result_struct;

void lmcurve_cpp(
    const int n_par, std::vector<double>& par, const int m_dat,
    const std::vector<double>& t, const std::vector<double>& y,
    double (*g)(const double t, const double* par),
    const lm_control_struct* control, lm_status_struct* status)
{
    lmcurve(n_par, par.data(), m_dat, t.data(), y.data(),
            g, control, status);
}

void lmmin_cpp(
    const int n_par, std::vector<double>* par, const int m_dat,
    std::vector<double>* y, const void *const data,
    void (*const evaluate)(
        const double *const par, const int m_dat, const void *const data,
        double *const fvec, int *const userbreak),
    const lm_control_struct *const control, lm_status_struct *const status)
{
    if(y)
        lmmin(n_par, par->data(), m_dat, y->data(), data, evaluate, control, status);
    else
        lmmin(n_par, par->data(), m_dat, NULL, data, evaluate, control, status);
}

void lmmin2_cpp(
    const int n_par, std::vector<double>* par, std::vector<double>* parerr,
    std::vector<double>* covar, const int m_dat, std::vector<double>* y,
    const void *const data,
    void (*const evaluate)(
        const double *const par, const int m_dat, const void *const data,
        double *const fvec, int *const userbreak),
    const lm_control_struct *const control, lm_status_struct *const status)
{
    double *parerr_;
    double *covar_;
    double *y_;
    if (parerr)
        parerr_ = parerr->data();
    else
        parerr_ = NULL;
    if (covar)
        covar_ = covar->data();
    else
        covar_ = NULL;
    if (y)
        y_ = y->data();
    else
        y_ = NULL;

    lmmin2(n_par, par->data(), parerr_, covar_, m_dat, y_,
           data, evaluate, control, status);
}

lm_result_struct lm_min(const int n_par, std::vector<double> start_par,
                        const int m_dat, const void *const data,
                        void (*const evaluate)(
                            const double *const par, const int m_dat, const void *const data,
                            double *const fvec, int *const userbreak),
                        const lm_control_struct *const control)
{
    lm_result_struct res;
}



} //namespace lmfit

__END_DECLS

#endif /* LMFIT_HPP */
