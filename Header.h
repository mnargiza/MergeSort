#pragma once

#include <iostream>
#include <vector>
#include <boost/thread.hpp>

using namespace std;

void Sort(double arr[], int n, double* tmp);
void Merge(double arr1[], int n1, float arr2[], int n2, double* arr3);