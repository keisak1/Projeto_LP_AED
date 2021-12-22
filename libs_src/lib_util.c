/**
 *  @file lib_util.c
 *  @brief Implementation of some util function prototypes for aed1.
 *
 *  This file contains the implementations for
 *  some util functions you will need for aed1.
 *
 *  @author José Torres (jtorres@ufp.edu.pt)
 *  @bug No known bugs.
 */

#include <time.h>
#include <assert.h>
#include <string.h>
#include "lib_util.h"


int readInts(char *filename, int *intvec, int nmax) {
    FILE *fp;
    int n = 0;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while (!feof(fp) && n < nmax)
            fscanf(fp, "%d\n", &intvec[n++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return n;
}

int readIntsHeader(char *filename, int **intvec) {
    FILE *fp;
    int n = 0, nmax;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        fscanf(fp, "%d\n", &nmax); // header - size of array
        *intvec = newIntArray(nmax);
        while (!feof(fp) && n < nmax)
            fscanf(fp, "%d\n", &((*intvec)[n++]));
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return nmax;
}

#ifdef WIN32
/*
int gettimeuseconds(long long * time_usec) {
    union {
        long long ns100; //time since 1 Jan 1601 in 100ns units
        FILETIME ft;
    } now;
    GetSystemTimeAsFileTime( &(now.ft) ); // win32 function!
    *time_usec=(long long) (now.ns100 / 10LL);
    return 0;
}
*/

int gettimeuseconds(long long * time_usec) {
    LARGE_INTEGER StartingTime;
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
    //
    // We now have the elapsed number of ticks, along with the
    // number of ticks-per-second. We use these values
    // to convert to the number of elapsed microseconds.
    // To guard against loss-of-precision, we convert
    // to microseconds *before* dividing by ticks-per-second.
    //
    StartingTime.QuadPart *= 1000000;
    StartingTime.QuadPart /= Frequency.QuadPart;
    *time_usec=(long long) StartingTime.QuadPart;
    return 0;
}

#else
int gettimeuseconds(long long *time_usec) {
    struct timeval time;
    gettimeofday(&time, NULL);
    *time_usec = (long long) (time.tv_sec * 1000000 + time.tv_usec);
    return 0;
}
#endif

/** 
  @brief gera um inteiro aleatoriamente/uniformemente no intervalo: val_min...val_max 
 */
int uniform(int val_min, int val_max) {
    return val_min + rand() % (val_max - val_min + 1);
}

/**
 * C99 Long Long 64bit random
 * @return
 */
long long uniformLL(long long val_min, long long val_max) {
    unsigned long long r = 0;
    unsigned byte_size = 8, rand_max_size = 15; //bits
    unsigned n = 1 + (byte_size * (unsigned)sizeof(long long)) % rand_max_size;
    for (int i = 0; i < n; ++i) {
        r = (r << rand_max_size) | (rand() & 0x7FFF);
    }
    r = r & 0xFFFFFFFFFFFFFFFFULL;
    return val_min + r % (val_max - val_min + 1);
}

/** @brief gera um double aleatoriamente/uniformemente no intervalo 0..1 */
double uniform_double(void) {
    return rand() / (double) (RAND_MAX);
}


double uniform_double_interval(double val_min, double val_max) {
    return val_min + (val_max - val_min) * (rand() / (double) (RAND_MAX));
}

/**
 * Return a real number with a standard Gaussian distribution.
 */
double gaussian_normal(void) {
    // use the polar form of the Box-Muller transform
    double r, x, y;
    do {
        x = uniform_double_interval(-1.0, 1.0);
        y = uniform_double_interval(-1.0, 1.0);
        r = x*x + y*y;
    } while (r >= 1 || r == 0);
    return x * sqrt(-2 * log(r) / r);
    
    // Remark:  y * sqrt(-2 * log(r) / r)
    // is an independent random gaussian
}

/**
 * Return a real number from a gaussian distribution with given mean and stddev
 */
double gaussian(double mean, double stddev) {
    return mean + stddev * gaussian_normal();
}

/// @brief function to fill an array with integer random uniformly distributed values (returns -1 if error)
int uniformArray(int *a, int N, int val_min, int val_max) {
    int i;
    for (i = 0; i < N; i++) {
        a[i] = uniformLL(val_min, val_max);
    }
    return 0;
}

int uniformDistinctArray(int *a, int N, int val_min, int val_max) {
    int i, j, M = val_max - val_min + 1;
    int val;
    assert(M >= N); //erro
    assert(val_max >= val_min); //erro
    int * b = newIntArray(M);
    for (i = 0; i < M; i++) {
        b[i] = i;
    }
    for (i = 0; i < N; i++) {
        j = uniformLL(i, M-1);
        val = b[j];
        b[j] = b[i];
        b[i] = val;
        a[i] = val_min + b[i];
    }
    freeIntArray(b);
    return 0;
}

void knuth_shuffle(int * v, int n) {
    int aux,r,i;
    for (i = 0; i < n; i++) {
        r = uniform(0,i);
        aux=v[i];
        v[i]=v[r];
        v[r]=aux;
    }
}

char *newCharArray(int N) {
    return (char *) malloc(sizeof(char) * N);
}

void freeCharArray(char *v) {
    free(v);
}

double *newDoubleArray(int N) {
    return (double *) malloc(sizeof(double) * N);
}

void freeDoubleArray(double *v) {
    free(v);
}

/**
 *  @brief int array dynamic managing
 *
 *  @param N size of int array to be created
 *
 *  @return new int array allocate in heap memory
 */
int *newIntArray(int N) {
    return (int *) malloc(sizeof(int) * N);
}

void freeIntArray(int *v) {
    free(v);
}

int **newIntPArray(int N) {
    return (int **) malloc(sizeof(int *) * N);
}

void freeIntPArray(int **v) {
    free(v);
}

void printArrayDoubles(double *a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%lf ", a[i]);
    }
    printf("\n");
}

void printArray(int *a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void printArray2(int* a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%2d ",a[i]);
    }
    printf("\n");
}

void printArrayRange(int *a, int lo, int hi) {
    int i;
    for (i = lo; i < hi; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int compareDoubleValues (const void *a, const void *b) {
    if (*(double *)a > *(double *)b) return 1;
    else if (*(double *)a < *(double *)b) return -1;
    return 0;
}

void sortDoubleArray (double *v, int n) {
    qsort(v, n, sizeof(v[0]), compareDoubleValues);
}

int compareIntValues(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

/**
 *  Sort int arrays using quick sort from the C library
 */
void sortIntArray(int *v, int n) {
    qsort(v, n, sizeof(int), compareIntValues);
}

int binarySearch(int a[], int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (key < a[mid]) hi = mid - 1;
        else if (key > a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

int writeInts(char *filename, int *intvec, int n) {
    FILE *fp;
    int i = 0;
    fp = fopen(filename, "w");
    if (fp != NULL) {
        while (i < n)
            fprintf(fp, "%d\n", intvec[i++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return 0;
}

int writeIntsHeader(char *filename, int *intvec, int n) {
    FILE *fp;
    int i = 0;
    fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "%d\n", n); // header - size of array
        while (i < n)
            fprintf(fp, "%d\n", intvec[i++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return 0;
}

int writeDoubles(char *filename, double *vec, int n) {
    FILE *fp;
    int i = 0;
    fp = fopen(filename, "w");
    if (fp != NULL) {
        while (i < n)
            fprintf(fp, "%lf\n", vec[i++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return 0;
}

int readDoubles(char *filename, double *vec, int nmax) {
    FILE *fp;
    int n = 0;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while (!feof(fp) && n < nmax)
            fscanf(fp, "%lf\n", &vec[n++]);
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return n;
}

int fread_test_case_input_file (char * line, char *input_file_name, char *test_case_name) {
    char comment_prefix[] = "///";
    char temp[MAX_STR_SIZE];
    FILE *fp = fopen(input_file_name, "r");
    if (fp == 0)
        return 0;
    int len_temp, len_comment_prefix = strlen(comment_prefix), len_test_case_name = strlen(test_case_name);
    while (fgets(temp, MAX_STR_SIZE, fp) != NULL) {
        len_temp = strlen(temp);
        if (len_temp > len_comment_prefix && memcmp(temp, comment_prefix, len_comment_prefix) == 0)
            continue; // ignore comment at beginning of line
        if (strstr(temp, test_case_name) != NULL) {
            strcpy(line, &temp[len_test_case_name+1]);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0; // error not found
}

int readStringsHeader(char *filename, StringElementsArray *a) {
    FILE *fp;
    int n = 0;
    char line[MAX_STR_SIZE];
    fp = fopen(filename, "r");
    if (fp != NULL) {
        fscanf(fp, "%d\n", &(a->N)); // header - size of arrray
        createStringElementsArray(a,a->N);
        while (!feof(fp) && n < a->N) {
            fgets(line,MAX_STR_SIZE,fp);
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';
            a->str[n] = (char *) malloc(sizeof(char)*strlen(line));
            strcpy(a->str[n], line);
            a->len[n] = strlen(line);
            n++;
        }
        fclose(fp);
    } else return -1; // erro na leitura do ficheiro
    return n;
}

/*************************************************************************
 * Util functions for struct StringElementsArray
 ************************************************************************/

void createStringElementsArray(StringElementsArray * si, int N) {
    si->N = N;
    si->str = (char **) malloc(sizeof(char *)*N);
    si->len = (int *) malloc(sizeof(int)*N);
    return;
}

void createStringElementsArrayAndFill(StringElementsArray * si, int N, char ** strings){
    int i;
    createStringElementsArray(si, N);
    for (i = 0; i < N; i++) {
        si->str[i] = strings[i];
        si->len[i] = (int)strlen(strings[i]);
    }
    return;
}

void freeStringElementsArray(StringElementsArray * si) {
    free(si->str);
    free(si->len);
    return;
}

void printStringElementsArray(StringElementsArray * a) {
    int i;
    printf("\n-------------\nStringElementsArray (N=%d):\n",a->N);
    for (i = 0; i < a->N; i++) {
        printf("\t%s\t(len=%d)\n", a->str[i], a->len[i]);
    }
    printf("-------------\n");
}

int charAt(StringElementsArray * a, int i, int d) {
    return (d < a->len[i]) ? (a->str[i][d]) : STRING_END_CHAR;
}

/**
 *  exchange a[i] and a[j] in collection StringElementsArray *a
 *
 *  @param a strin elements array
 *  @param i
 *  @param j
 */
void exchStringElementsArray(StringElementsArray *a, int i, int j) {
    char * temp_str = a->str[i];
    a->str[i] = a->str[j];
    a->str[j] = temp_str;
    int temp_len = a->len[i];
    a->len[i] = a->len[j];
    a->len[j] = temp_len;
}

