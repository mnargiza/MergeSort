#pragma once

#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <math.h>
#include <time.h>
#include <utility>
#include <iomanip>
using namespace std;


class barrier {
    int threadCount;
    std::atomic<unsigned int>threadsWaiting;
    bool isNotWaiting;
    std::condition_variable waitVariable;
    std::mutex mutex;
public:
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
    void reduce() {
        threadCount = threadCount - 2;
    }
};

void Sort(double arr[], int n, double* tmp);
void Merge(double arr1[], int n1, double arr2[], int n2, double* arr3, int j);

// Merge Sort
void task_1(double arr[], int n, double* res);

// Merge Sort with threads
void task_2(double arr[], int n, double* tmp, int amountOfThreads);

void sort_with_threads(double arr[], int cur_thread, int step, double* t, int amountOfThreads);
pair< int, int > memory_distribution(int step, int cur_thread, int i);

void test();

