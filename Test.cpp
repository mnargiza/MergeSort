#include "Header.h"

void test() {
	int numberOfTests = 5; // amounts of tests
	int k = 5;
	clock_t start_time, end_time, time;


	for (int i = 0; i < numberOfTests; i++) {
		double* arr = new double[k];
		double* tmp = new double[k];
		for (int j = 0; j < k; j++) {
			arr[j] = rand() % k;
		}
		
		cout << "Количество чисел: "<<k<<endl;

		/*for (int i = 0; i < k; i++) {
			cout << arr[i] << ' ';
		}*/

		//cout << endl;
		//cout << "\nПоследовательная сортировка: " << endl;

		start_time = clock();
		task_1(arr, k, tmp);
		end_time = clock();
		time = end_time - start_time;
		cout << "\nTime of sequential sort: " << (double)time/ CLOCKS_PER_SEC << "  \n";

		//cout << endl;
		//cout << "\nПараллельная сортировка: " << endl;

		start_time = clock();
		task_2(arr, k, tmp);
		end_time = clock();
		time = end_time - start_time;
		cout << "\nTime parallel sort: " << (double)time / CLOCKS_PER_SEC << "  \n";
		//ParallelSort(arr, k, tmp);
		//cout << arr[i] << ' ';
		k = k * 2;
	}


}