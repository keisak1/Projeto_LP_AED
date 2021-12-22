//
// Created by arpinto on 19-09-2016.
//

#ifndef LIB_UTIL_H
#define LIB_UTIL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#if defined _WIN64 || defined _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#define MAX_STR_SIZE 512
// terminate symbol for strings
#define STRING_END_CHAR -1

/**
 *  Structure used for key-index-count, LSD, MSD and other
 */
typedef struct {
    char ** str; // array of strings
    int * len; // array of string lengths
    int N; // number of strings (size of array of strings)
} StringElementsArray;

void createStringElementsArrayAndFill(StringElementsArray * si, int N, char ** a);
void createStringElementsArray(StringElementsArray * si, int N);
void freeStringElementsArray(StringElementsArray * si);
void printStringElementsArray(StringElementsArray * a);
int charAt(StringElementsArray * a, int i, int d);
void exchStringElementsArray(StringElementsArray *a, int i, int j);

int readInts(char * filename, int * intvec, int nmax);
int gettimeuseconds(long long * time_usec);
int uniform(int val_min, int val_max);
long long uniformLL(long long val_min, long long val_max);
double uniform_double(void);
double uniform_double_interval(double val_min, double val_max);
double gaussian_normal(void);
double gaussian(double mean, double stddev);
int readIntsHeader(char * filename, int ** intvec);
void printArray(int* a, int N);
void printArray2(int* a, int N);
void printArrayRange(int *a, int lo, int hi);
void knuth_shuffle(int * v, int n);
void printArrayDoubles(double *a, int N);
double * newDoubleArray(int N); // alloc new int array
void freeDoubleArray(double * v); // frees new int array
int * newIntArray(int N); // alloc new int array
void freeIntArray(int * v); // frees new int array
int **newIntPArray(int N);
void freeIntPArray(int **v);
char * newCharArray(int N);
void freeCharArray(char * v);
int uniformArray(int * a, int N, int val_min, int val_max); // fill array with integer random uniformly distributed values (ret -1 if error)
int uniformDistinctArray(int * a, int N, int val_min, int val_max); // fill array with integer random uniformly distributed distinct
int compareIntValues(const void * a, const void * b);
void sortIntArray(int * v, int n);
int binarySearch(int a[], int n, int key);
void sortDoubleArray(double *v, int n);
int compareDoubleValues(const void *a, const void *b);
int writeInts(char * filename, int * intvec, int n);
int writeIntsHeader(char * filename, int * intvec, int n);
int writeDoubles(char * filename, double * vec, int n);
int readDoubles(char * filename, double * vec, int nmax);
int fread_test_case_input_file (char * line, char *input_file_name, char *test_case_name);
int readStringsHeader(char *filename, StringElementsArray *a);


#endif //LIB_UTIL_H