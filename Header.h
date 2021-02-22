#pragma once

#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <math.h>
#include <time.h>



using namespace std;

const int amountOfTthreads = 2;

void Sort(double arr[], int n, double* tmp);
void Merge(double arr1[], int n1, double arr2[], int n2, double* arr3, int j);

// Merge Sort
void task_1(double arr[], int n, double* res);

// Merge Sort with threads
void task_2(double arr[], int n, double* tmp);

void ParallelSort(double arr[], int size, double* tmp, int iter, int rem);
void ParallelMerge(double arr[], boost::thread threads[], double* res, int n, int step, int remainder);

void test();
