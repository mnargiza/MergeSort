 #include "Header.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void Sort(double arr[], int n, double* tmp)
{
  
    int l1, l2,i;
    if (n <= 1) return;
    l1 = n / 2;
    l2 = n - l1;
    Sort(arr, l1, tmp);
    Sort(arr + l1, l2, tmp);
    Merge(arr, l1, arr + l1, l2, tmp, 0);
    for (i = 0; i < n; i++)
        arr[i] = tmp[i];
 
}

void Merge(double arr1[], int n1, double arr2[], int n2, double* arr3, int pos)
{
    int i1 = 0, i2 = 0, j; //i1- index arr1[], i2-index arr2[] , j-индекс полученного отсортиров. 2 массивов
    for (i1 = 0, i2 = 0, j=pos; i1 < n1 && i2 < n2;)
    {
        if (arr1[i1] < arr2[i2])
        {
           arr3[j++] = arr1[i1++];
        }
        else
            arr3[j++] = arr2[i2++];

        for (int i = 0; i < n1 - i1; i++)
            arr3[j + i] = arr1[i + i1];
        for (int i = 0; i < n2 - i2; i++)
            arr3[j + i] = arr2[i + i2];
    
    }
}
