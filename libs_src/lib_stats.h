//
// Created by arpinto on 19-09-2016.
//
#ifndef STATS_LIB_h
#define STATS_LIB_h

#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <math.h>


double max_double(double* a, int N);
double max_double_subarray(double* a, int N, int lo, int hi);
int max_int(int* a, int N);
double min_double(double* a, int N);
double min_double_subarray(double* a, int N, int lo, int hi);
int min_int(int* a, int N);
double mean_double(double* a, int N);
double mean_double_subarray(double* a, int N, int lo, int hi);
double mean_int(int* a, int N);
double var_double(double* a, int N);
double var_double_subarray(double* a, int N, int lo, int hi);
double var_int(int* a, int N);
double varp_double(double* a, int N);
double varp_double_subarray(double* a, int N, int lo, int hi);
double stddev_double(double* a, int N);
double stddev_double_subarray(double* a, int N, int lo, int hi);
double stddev_int(int* a, int N);
double stddevp_double(double* a, int N);
double stddevp_double_subarray(double* a, int N, int lo, int hi);
double sum_double(double* a, int N);
double sum_double_subarray(double* a, int N, int lo, int hi);
int sum_int(int* a, int N);

#endif