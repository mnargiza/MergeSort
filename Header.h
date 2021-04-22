#pragma once

#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <math.h>
#include <time.h>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;


class barrier {
    
    atomic<unsigned int>threadsWaiting;
    
    std::condition_variable waitVariable;
    std::mutex mutex;
public:
    int threadCount;
    bool isNotWaiting;
    barrier(unsigned int n) : threadCount(n) {
        threadsWaiting = 0;
        isNotWaiting = false;
    }
    barrier(const barrier&) = delete;
    void wait() {
        if (threadsWaiting.fetch_add(1) >= threadCount - 1) {
            isNotWaiting = true;
            waitVariable.notify_all();
            threadsWaiting.store(0);
        }
        else {
            std::unique_lock<std::mutex> lock(mutex);
            waitVariable.wait(lock, [&] { return isNotWaiting; });
        }
    }

};

extern barrier *b1, *b2, *b3, *b4;



extern int f, f1;
extern bool _var ;
void Sort(double arr[], int n, double* tmp);
void Merge(double arr1[], int n1, double arr2[], int n2, double* arr3, int j);

// Merge Sort
void task_1(double arr[], int n, double* res);

// Merge Sort with threads
void task_2(double arr[], int n, double* tmp, int amountOfThreads);

void sort_with_threads(double arr[], int cur_thread, int step, double* t, int amountOfThreads);
pair< int, int > memory_distribution(int step, int cur_thread, int i);

void test();

