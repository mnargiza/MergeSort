#include "Header.h"


bool check(double arr1[], double arr2[], int n) {
	
//std::ofstream out;          // поток для записи
//out.open("out.txt");
//for (int j = 0; j < n; j++) {
//	out << arr1[j] << " ";
//}
//out << "\narr2" << endl;
//for (int j = 0; j < n; j++) {
//	out << arr2[j] << " ";
//}
	for (int i = 0; i < n; i++) {
		if (arr1[i] != arr2[i])
			//out << "\nнеправ: "<<i;
			return false;
	}
	
	//out << "\nright: ";
	return true;
}


void test() {
	bool IsRight;

	int amountOfThreads;
	int numberOfTests = 3; // amounts of tests
	int k = 16;
	
	//FILE* out = fopen("out.txt", "w");
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
				//cout << arr[j] << " ";
				//out << arr[j] << " ";
		}
			
		cout << "Количество чисел: " << k << endl;
		//cout << setw(10) <<"Количество чисел "<< setw(10) << "2 " << setw(10) << "4 " << setw(10) << "8 " << setw(10) << "Время " << endl;
		//out << "Количество чисел:"<<k<<endl;
		//cout << "\nПоследовательная сортировка: " << endl;

		start_time = clock();
		task_1(arr, k, tmp);
		end_time = clock();
		time = end_time - start_time;
		cout << "Time of sequential sort: " << (double)time / CLOCKS_PER_SEC << endl;
		//for (int j = 0; j < k; j++) {
		//	//out << arr[j] << " ";
		//}
		for (int l = 2; l <=16; l=l*2) {
			amountOfThreads = l;
			
		
			b1 = new barrier(amountOfThreads);
			b2 = new barrier(amountOfThreads / 2);
			b3 = new barrier(amountOfThreads / 4);
			b4 = new barrier(amountOfThreads / 8);
			
			
			/*for (int i = 0; i < k; i++) {
				 tmp[i]=0;
			}*/
			//cout << "\nПараллельная сортировка: " << endl;
			cout << endl;
			cout << "Number of threads: " << amountOfThreads << endl;
			//out<<"Количество потоков:"<< amountOfThreads<<endl;
			
			

			start_time = clock();
			task_2(arr2, k, tmp, amountOfThreads);
			end_time = clock();
			time = end_time - start_time;
			cout << "Time parallel sort: " << (double)time / CLOCKS_PER_SEC << endl;
			
			delete b1;
			delete b2;
			delete b3;
			delete b4;
	
			
			cout << endl;
			IsRight = check(arr, arr2, k);
			if (IsRight==true) { 
				cout << "RIGHT!" << endl; 
				//out<< "RIGHT!\n";
			}
			else {
				cout << "WRONG!" << endl;
				//out<< "WRONG!\n";
			}
			
			for (int z = 0; z < k; z++) {
					arr2[z] = arr3[z];
				}
			
		}
		
		k = k * 4;
		cout << endl;
	}
}
