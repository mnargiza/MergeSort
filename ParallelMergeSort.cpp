#include "Header.h"




void ParallelSort(double arr[], int size, double* tmp, int iter, int rem) 
{
	int l1, l2;

	if (size <= 1) 
		return;

	l1 = size / 2;
	l2 = size - l1;
	ParallelSort(arr, l1, tmp + iter * size, iter, rem);
	ParallelSort(arr + l1, l2, tmp + iter * size, iter, rem);
	Merge(arr, l1, arr + l1, l2, tmp + iter * size,0);
	memcpy(arr, tmp+ iter*size, size * sizeof(double));
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

// Merge Sort
void task_1(double arr[], int n, double* res){
	Sort(arr, n, res);

	
	/*for (int i = 0; i < n; i++) {
		if (n == 1) {
			cout << arr[0] << ' ';
			continue;
		}
		else cout << res[i] << ' ';
	}*/

}

// Merge Sort with threads
void task_2(double arr[], int n, double* tmp) {
	

	if (n < amountOfTthreads) {
		Sort(arr, n, tmp);
		/*for (int i = 0; i < n; i++) {
			if (n == 1) {
				cout << arr[0] << ' ';
				continue;
			}

			else cout << tmp[i] << ' ';
		}*/
		return;
	}

	int step, remainder;
	step = n / amountOfTthreads;
	remainder = n % amountOfTthreads;
	//cout << "step = " << step << "   remainder = " << remainder << endl;
	boost::thread threads[amountOfTthreads];

	double* result = new double[n];
	if (n == amountOfTthreads) {
		ParallelMerge(arr, threads, ref(result), n, step, remainder);
	}
	else {

		for (int i = 0; i < amountOfTthreads; i++) {

			double* a;

			if (i == amountOfTthreads - 1 && remainder != 0) {
				a = new double[step + remainder];
				memcpy(a, arr + i * step, (step + remainder) * sizeof(double));
				threads[i] = boost::thread(ParallelSort, a, step + remainder, ref(tmp), i, remainder);
				///cout << "массив эл:\n";
							/*for (int i = 0; i < step+remainder; i++)
								cout << a[i] << " ";
							cout << endl;*/

			}
			else {
				a = new double[step];

				memcpy(a, arr + i * step, step * sizeof(double));

				/*cout << "массив эл:\n";
				for (int i = 0; i < step; i++)
					cout << a[i] << " ";
				cout << endl;*/



				threads[i] = boost::thread(ParallelSort, a, step, ref(tmp), i, remainder);

			}
		}


		for (int i = 0; i < amountOfTthreads; i++)
			threads[i].join();
		//cout << "Merging" << endl;

		ParallelMerge(tmp, threads, ref(result), n, step, remainder);
	}
	/*for (int i = 0; i < n; i++)
		cout << result[i] << ' ';*/
}
int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");

	test();

	return 0;
}
