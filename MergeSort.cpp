 #include "Header.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Merge(double arr1[], int n1, double arr2[], int n2, double* arr3)
{
    int i1 = 0, i2 = 0, j = 0; //i1- индекс arr1[], i2-индекс arr2[] , j-индекс полученного отсортиров. 2 массивов
    for (i1 = 0, i2 = 0, j = 0; i1 < n1 && i2 < n2;)
    {
        if (arr1[i1] < arr2[i2])
        {
            arr3[j++] = arr1[i1++];
        }
        else
            arr3[j++] = arr2[i2++];
        memcpy(arr3 + j, arr1 + i1, (n1 - i1) * sizeof(double));
        memcpy(arr3 + j, arr2 + i2, (n2 - i2) * sizeof(double));
    }
}
void Sort(double arr[], int n, double* tmp) //делим массив на 2 части, потом эти 2 части еще на 2 и т.д
{
    int l1, l2;
    if (n <= 1) return;
    l1 = n / 2;
    l2 = n - l1;
    Sort(arr, l1, tmp);
    Sort(arr + l1, l2, tmp);
    Merge(arr, l1, arr + l1, l2, tmp);// cортируем каждый часть длины не меньше 1
    memcpy(arr, tmp, n * sizeof(double));//
}



