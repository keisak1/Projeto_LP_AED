//
// Created by arpinto on 19-09-2016.
//

#include "lib_stats.h"

/**
 * Return maximum value in array, -infinity if no such value.
 */
double max_double(double* a, int N) {

    double max = DBL_MIN;
    int i;
    for (i = 0; i < N; i++) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

/**
 * Return maximum value in subarray a[lo..hi], -infinity if no such value.
 */
double max_double_subarray(double* a, int N, int lo, int hi) {
    int i;
    if (lo < 0 || hi >= N || lo > hi) {
        printf("error: subarray indices out of bounds");
        return 0;
    }
    double max = DBL_MIN;
    for (i = lo; i <= hi; i++) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

/**
 * Return maximum value of array, Integer.MIN_VALUE if no such value
 */
int max_int(int* a, int N) {
    int max = INT_MIN, i;
    for (i = 0; i < N; i++) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

/**
 * Return minimum value in array, +infinity if no such value.
 */
double min_double(double* a, int N) {
    double min = DBL_MAX;
    int i;
    for (i = 0; i < N; i++) {
        if (a[i] < min) min = a[i];
    }
    return min;
}

/**
 * Return minimum value in subarray a[lo..hi], +infinity if no such value.
 */
double min_double_subarray(double* a, int N, int lo, int hi) {
    int i;
    if (lo < 0 || hi >= N || lo > hi) {
        printf("error: subarray indices out of bounds");
        return 0;
    }
    double min = DBL_MAX;
    for (i = lo; i <= hi; i++) {
        if (a[i] < min) min = a[i];
    }
    return min;
}

/**
 * Return minimum value of array, Integer.MAX_VALUE if no such value
 */
int min_int(int* a, int N) {
    int min = INT_MAX,i;
    for (i = 0; i < N; i++) {
        if (a[i] < min) min = a[i];
    }
    return min;
}

/**
 * Return average value in array, NaN if no such value.
 */
double mean_double(double* a, int N) {
    if (N == 0) return 0;
    double sum = sum_double(a, N);
    return sum / N;
}

/**
 * Return average value in subarray a[lo..hi], NaN if no such value.
 */
double mean_double_subarray(double* a, int N, int lo, int hi) {
    int length = hi - lo + 1;
    if (lo < 0 || hi >= N || lo > hi) {
        printf("error: subarray indices out of bounds");
        return 0;
    }

    if (length == 0) return 0;
    double sum = sum_double_subarray(a, N, lo, hi);
    return sum / length;
}

/**
 * Return average value in array, NaN if no such value.
 */
double mean_int(int* a, int N) {
    int i;
    if (N == 0) return 0;
    double sum = 0.0;
    for (i = 0; i < N; i++) {
        sum = sum + a[i];
    }
    return sum / N;
}


/**
 * Return sample variance of subarray a[lo..hi], NaN if no such value.
 */
double var_double_subarray(double* a, int N, int lo, int hi) {
    int length = hi - lo + 1,i;
    if (lo < 0 || hi >= N || lo > hi) {
        printf("error: subarray indices out of bounds");
        return 0;
    }

    if (length == 0) return 0;
    double avg = mean_double_subarray(a, N, lo, hi);
    double sum = 0.0;
    for (i = lo; i <= hi; i++) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (length - 1);
}

/**
 * Return sample variance of array, NaN if no such value.
 */
double var_int(int* a, int N) {
    int i;
    if (N == 0) return 0;
    double avg = mean_int(a, N);
    double sum = 0.0;
    for (i = 0; i < N; i++) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (N - 1);
}

/**
 * Return population variance of array, NaN if no such value.
 */
double varp_double(double* a, int N) {
    int i;
    if (N == 0) return 0;
    double avg = mean_double(a, N);
    double sum = 0.0;
    for (i = 0; i < N; i++) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / N;
}

/**
 * Return sample variance of array, NaN if no such value.
 */
double var_double(double* a, int N) {
    int i;
    if (N == 0) return 0;
    double avg = mean_double(a, N);
    double sum = 0.0;
    for (i = 0; i < N; i++) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (N - 1);
}

/**
 * Return population variance of subarray a[lo..hi],  NaN if no such value.
 */
double varp_double_subarray(double* a, int N, int lo, int hi) {
    int length = hi - lo + 1,i;
    if (lo < 0 || hi >= N || lo > hi) {
        printf("error: subarray indices out of bounds");
        return 0;
    }

    if (length == 0) return 0;
    double avg = mean_double_subarray(a, N, lo, hi);
    double sum = 0.0;
    for (i = lo; i <= hi; i++) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / length;
}

/**
 * Return sample standard deviation of array, NaN if no such value.
 */
double stddev_double(double* a, int N) {
    return sqrt(var_double(a, N));
}

/**
 * Return sample standard deviation of subarray a[lo..hi], NaN if no such value.
 */
double stddev_double_subarray(double* a, int N, int lo, int hi) {
    return sqrt(var_double_subarray(a, N, lo, hi));
}

/**
 * Return sample standard deviation of array, NaN if no such value.
 */
double stddev_int(int* a, int N) {
    return sqrt(var_int(a, N));
}

/**
 * Return population standard deviation of array, NaN if no such value.
 */
double stddevp_double(double* a, int N) {
    return sqrt(varp_double(a, N));
}


/**
 * Return population standard deviation of subarray a[lo..hi], NaN if no such value.
 */
double stddevp_double_subarray(double* a, int N, int lo, int hi) {
    return sqrt(varp_double_subarray(a, N, lo, hi));
}

/**
 * Return sum of all values in array.
 */
double sum_double(double* a, int N) {
    double sum = 0.0;
    int i;
    for (i = 0; i < N; i++) {
        sum += a[i];
    }
    return sum;
}

/**
 * Return sum of all values in subarray a[lo..hi].
 */
double sum_double_subarray(double* a, int N, int lo, int hi) {
    int i;
    if (lo < 0 || hi >= N || lo > hi) {
        printf("error: subarray indices out of bounds");
        return 0;
    }
    double sum = 0.0;
    for (i = lo; i <= hi; i++) {
        sum += a[i];
    }
    return sum;
}

/**
 * Return sum of all values in array.
 */
int sum_int(int* a, int N) {
    int sum = 0,i;
    for (i = 0; i < N; i++) {
        sum += a[i];
    }
    return sum;
}


