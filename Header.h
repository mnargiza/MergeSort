#pragma once

#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <math.h>
#include <time.h>
#include <utility>

using namespace std;

const int amountOfThreads = 4;

void Sort(double arr[], int n, double* tmp);
void Merge(double arr1[], int n1, double arr2[], int n2, double* arr3, int j);

// Merge Sort
void task_1(double arr[], int n, double* res);

// Merge Sort with threads
void task_2(double arr[], int n, double* tmp);

void sort_with_threads(double arr[], int cur_thread, int step, double* tmp);
pair< int, int > memory_distribution(int step, int cur_thread, int i);

void test();
