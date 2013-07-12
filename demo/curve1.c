/*
 * Library:  lmfit (Levenberg-Marquardt least squares fitting)
 *
 * File:     demo/curve1.c
 *
 * Contents: Example for one-dimensional curve fitting,
 *           using the simplified interface from lmcurve.h.
 *
 * Author:   Joachim Wuttke <j.wuttke@fz-juelich.de> 2004-2013
 * 
 * Licence:  see ../COPYING (FreeBSD)
 * 
 * Homepage: apps.jcns.fz-juelich.de/lmfit
 */
 
#include "lmcurve.h"
#include <stdio.h>

/* model function: a parabola */

double f( double t, const double *p )
{
    return p[0] + p[1]*t + p[2]*t*t;
}

int main()
{
    int n = 3; /* number of parameters in model function f */
    double par[3] = { 100, 0, -10 }; /* really bad starting value */
    
    /* data points: a slightly distorted standard parabola */
    int m = 9;
    int i;
    double t[9] = { -4., -3., -2., -1.,  0., 1.,  2.,  3.,  4. };
    double y[9] = { 16.6, 9.9, 4.4, 1.1, 0., 1.1, 4.2, 9.3, 16.4 };

    lm_status_struct status;

    printf( "Fitting ...\n" );
    lmcurve( n, par, m, t, y, f, &lm_control_double, NULL, &status );
        
    printf( "Results:\n" );
    printf( "status after %d function evaluations:\n  %s\n",
            status.nfev, lm_infmsg[status.info] );

    printf("obtained parameters:\n");
    for ( i = 0; i < n; ++i)
        printf("  par[%i] = %12g\n", i, par[i]);
    printf("obtained norm:\n  %12g\n", status.fnorm );
    
    printf("fitting data as follows:\n");
    for ( i = 0; i < m; ++i)
        printf( "  t[%2d]=%4g y=%6g fit=%10g residue=%12g\n",
                i, t[i], y[i], f(t[i],par), y[i] - f(t[i],par) );

    return 0;
}
