#include "Header.h"

// Merge Sort
void task_1(double arr[], int n, double* res) {
	Sort(arr, n, res);

}


barrier * b1, * b2, * b3, * b4;

mutex m;

void b_wait(int i) {

	if (i == 0) {
		b1->wait();
	}
	else if (i == 1) {
		b2->wait();	
	}
	else if (i == 2) {
		b3->wait();	
	}
	else if (i == 3) {
		b4->wait();	
	}

}
void sort_with_threads(double arr[], int cur_thread, int step, double* tmp, int amountOfThreads)
{

	for (int i = 0; i < log2(amountOfThreads); i++) {
		//pair< int, int > block = memory_distribution(step, cur_thread, i);
		int s = cur_thread * step;
		Sort(arr + s, (1 << i) * step, tmp); 
		int a = 1 << i+1;

		
		b_wait(i);
	
		if (cur_thread % a != 0 ) {
			
			return;
		}
		
	
	}	
}

// Merge Sort with threads
void task_2(double arr[], int n, double* tmp, int amountOfThreads) {

	if (n < amountOfThreads) {
		Sort(arr, n, tmp);

		return;
	}

	int step, remainder;
	step = n / amountOfThreads;

	boost::thread* threads = new boost::thread[amountOfThreads];

	for (int i = 0; i < amountOfThreads; i++)
		threads[i] = boost::thread(sort_with_threads, arr, i, step, ref(tmp), amountOfThreads);


	for (int i = 0; i < amountOfThreads; i++)
		threads[i].join();


	Merge(arr, n / 2, arr + n / 2, n / 2, tmp, 0);
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
		//cout << arr[i] << " ";
	}

}



int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");

	test();

	return 0;
}
