%module "pylmfit"

%include "std_vector.i"

namespace std {
    %template(VectorDouble) vector<double>;
};

%{
#include <Python.h>
#include <iostream>

#include "lib/lmdecls.h"
#include "lib/lmstruct.h"
#include "lib/lmfit.hpp"

/* Variables to be used in function_g and function_eval */
static PyObject *callback;
static int len_par = 1;

/* Wrappers for the python callback function */
double function_g(const double t, const double *p);
void function_eval(const double *const par, const int m_dat,
    const void *const data, double *const fvec, int *const userbreak);
%}

%include "lib/lmdecls.h"
%include "lib/lmstruct.h"
%include "lib/lmfit.hpp"

/* Declaring function_g and function_eval as callback functions.
   Cannot be used otherwise */
%constant double function_g(const double t, const double *p);
%constant void function_eval(const double *const par, const int m_dat,
    const void *const data, double *const fvec, int *const userbreak);

/* Extra methods for setting python callback, number of parameters,
   and printing the lm infomessages */
%inline %{
void set_callback(PyObject *callable)
{
    callback = callable;
    std::cout << "Callback was set." << '\n';
}
void set_parlen(int parlen)
{
    len_par = parlen;
    std::cout << "Length of parameter array was set." << '\n';
}
int parlen() { return len_par; }
void print_infmsg(int outcome)
{
    std::cout << lm_infmsg[outcome] << '\n';
}
struct Data_Wrap {
    PyObject *content;
    Data_Wrap(PyObject* o): content(o) {}
};
void* to_void(Data_Wrap *data)
{
    void *d = (void*)data;
    return d;
}
%}

/* Implementation of function_g and function_eval */
%{

double function_g(const double t, const double *p)
{
    if (!callback) {
        std::cerr << "Callback function not set correctly!" << '\n';
    }
    else
    {
        PyObject *args = PyTuple_New(2);
        PyTuple_SetItem(args, 0, PyFloat_FromDouble(t));
        PyObject *list = PyList_New(len_par);
        int i;
        for (i = 0; i < len_par; ++i)
        {
            PyList_SetItem(list, i, PyFloat_FromDouble(p[i]));
        }
        PyTuple_SetItem(args, 1, list);
        PyObject *result = PyObject_CallObject(callback, args);
        if (PyErr_Occurred()) {
            PyErr_PrintEx(0);
            PyErr_Clear();
        }
        Py_XDECREF(list);
        Py_XDECREF(args);
        if (!PyFloat_Check(result)) {
            Py_XDECREF(result);
            std::cerr << "The callback did not return a python float!" << '\n';
        }
        else
        {
            return PyFloat_AsDouble(result);
        }
    }
    return -1.;
}

void function_eval(const double *const par, const int m_dat,
    const void *const data, double *const fvec, int *const userbreak)
{
    if (!callback) {
        std::cerr << "Callback function not set correctly!" << '\n';
    }
    else
    {
        PyObject *args;
        if (data) {
            args = PyTuple_New(2);
            Data_Wrap *D = (Data_Wrap*)data;
            PyTuple_SetItem(args, 1, D->content);
        } else {
            args = PyTuple_New(1);
        }
        PyObject *pars = PyList_New(len_par);
        int i;
        for (i = 0; i < len_par; ++i) {
            PyList_SetItem(pars, i, PyFloat_FromDouble(par[i]));
        }
        PyTuple_SetItem(args, 0, pars);
        PyObject *result = PyObject_CallObject(callback, args);
        if (PyErr_Occurred()) {
            PyErr_PrintEx(0);
            PyErr_Clear();
        }
        if (!PyTuple_Check(result)) {
            Py_XDECREF(result);
            std::cerr << "Callback should return a tupel, but does not!!!";
        } else {
            PyObject *vec = PyTuple_GetItem(result, 0);
            PyObject *ub = PyTuple_GetItem(result, 1);
            *userbreak = (int) PyLong_AsLong(ub);
            for (i = 0; i < m_dat; ++i) {
                fvec[i] = PyFloat_AsDouble(PyList_GetItem(vec, i));
            }
            Py_XDECREF(result);
        }
    }
}

%}
