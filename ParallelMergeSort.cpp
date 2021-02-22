#include "Header.h"

const int amountOfTthreads = 4;


void ParallelSort(double arr[], int size, double* tmp, int iter, int rem) 
{
	int l1, l2;

	if (size <= 1) 
		return;

	l1 = size / 2;
	l2 = size - l1;
	ParallelSort(arr, l1, tmp + iter * size + rem, iter, rem);
	ParallelSort(arr + l1, l2, tmp + iter * size + rem, iter, rem);
	Merge(arr, l1, arr + l1, l2, tmp + iter * size + rem,0);
	memcpy(arr, tmp+ iter*size+ rem, size * sizeof(double));
}

void ParallelMerge(double arr[], boost::thread threads[], double* res, int n, int step, int remainder)
{
	//Merge with threads

	for (int j = 0; j < ceil(amountOfTthreads / 2); j++) {
		for (int i = j; i < amountOfTthreads; i ++) {
			if (i >= 1 && i % 2 != 0 && i * step * (j + 1) < n) {
				if (i == amountOfTthreads - 1 && remainder != 0)
					threads[i-1] = boost::thread(Merge, arr + (i - 1) * step, step*(j+1), arr + i * step * (j + 1) + remainder, step * (j + 1) + remainder, ref(res), (i - 1) * step);
				else
					threads[i-1] = boost::thread(Merge, arr + (i - 1) * step, step * (j + 1), arr + i * step * (j + 1), step * (j + 1), ref(res), (i - 1) * step);
				
			}
			
		}

		for (int i = 0; i < amountOfTthreads-2*j; i=i+2)
			threads[i].join();
		memcpy(arr, res, n * sizeof(double));
	}

}

int main(int argc, char* argv[])
{

	setlocale(LC_CTYPE, "rus");

	int n; // the size of array

	cout << "Введите размер массива чисел: ";
	cin >> n;

	
	double *arr = new double[n];
	double* arr2 = new double[n];

	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 100;
		arr2[i] = arr[i];
		cout << arr[i] << ' ';
	}

	double *tmp = new double[n];
	Sort(arr, n, tmp);

	cout << endl;
	cout << "Последовательная сортировка: "<< endl;
	for (int i = 0; i < n; i++) {
		if(n==1) cout << arr[i] << ' ';
		else cout << tmp[i] << ' ';
	}


	///  parallel
	double* t = new double[n];
	double* result = new double[n];

	if (n < amountOfTthreads) {
		Sort(arr2, n, t);
		for (int i = 0; i < n; i++) {
			cout << t[i] << ' ';
		}
		return 0;
	}

	int step, remainder;
	step = n / amountOfTthreads;
	remainder = n % amountOfTthreads;

	boost::thread threads[amountOfTthreads];

	if (n == amountOfTthreads) {
		ParallelMerge(arr2, threads, ref(result), n, step, remainder);
	}
	else {

		for (int i = 0; i < amountOfTthreads; i++) {

			double* a;

			if (i == amountOfTthreads - 1 && remainder != 0) {
				a = new double[step + remainder];
				memcpy(a, arr2 + i * step + remainder, (step + remainder) * sizeof(double));
				threads[i] = boost::thread(ParallelSort, a, step + remainder, ref(t), i, remainder);
				

			}
			else {
				a = new double[step];
				memcpy(a, arr2 + i * step, step * sizeof(double));
				threads[i] = boost::thread(ParallelSort, a, step, ref(t), i, remainder);


			}


		}


		for (int i = 0; i < amountOfTthreads; i++)
			threads[i].join();


		ParallelMerge(t, threads, ref(result), n, step, remainder);
	}

	cout << endl;
	cout << "Параллельная сортировка: " << endl;

	for (int i = 0; i < n; i++) 
		cout << result[i] << ' ';
	
	
	return 0;
}
