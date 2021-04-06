#include "Header.h"

void test() {
	int amountOfThreads, t=0;
	int numberOfTests = 10; // amounts of tests
	int k = 8;
	bool IsRight;
	clock_t start_time, end_time, time;
	for (int i = 0; i < numberOfTests; i++) {
	
		double* arr = new double[k];
		double* tmp = new double[k];
		double* arr2 = new double[k];
		double* arr3 = new double[k];
		for (int j = 0; j < k; j++) {
				arr[j] = rand() % k;
				arr2[j] = arr[j];
				arr3[j] = arr[j];
		}
			
		cout << "Количество чисел: " << k << endl;
		//cout << setw(10) <<"Количество чисел "<< setw(10) << "2 " << setw(10) << "4 " << setw(10) << "8 " << setw(10) << "Время " << endl;
	
		//cout << "\nПоследовательная сортировка: " << endl;

		start_time = clock();
		task_1(arr, k, tmp);
		end_time = clock();
		time = end_time - start_time;
		cout << "Time of sequential sort: " << (double)time / CLOCKS_PER_SEC << endl;
		for (int l = 2; l <=16; l=l*2) {
			amountOfThreads = l;
			
			
		

			//
			/*for (int i = 0; i < k; i++) {
				 tmp[i]=0;
			}*/
			//cout << "\nПараллельная сортировка: " << endl;
			cout << "Number of threads: " << amountOfThreads << endl;

			if (l > 2) {
				for (int j = 0; j < k; j++) {
					arr2[j] = arr3[j];
				}
			}

			start_time = clock();
			task_2(arr2, k, tmp, amountOfThreads);
			end_time = clock();
			time = end_time - start_time;
			cout << "Time parallel sort: " << (double)time / CLOCKS_PER_SEC << endl;
		
			
		}
		//cout << setw(10) << k << setw(10) << l << setw(10) << "Время " << endl;
		k = k * 2;
	}
}
