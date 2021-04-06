#include "Header.h"

// Merge Sort
void task_1(double arr[], int n, double* res) {
	Sort(arr, n, res);

	/*for (int i = 0; i < n; i++) {
		if (n == 1) {
			cout << arr[0] << ' ';
			continue;
		}
		else cout << res[i] << ' ';
	}*/

}


//распределение памяти для каждого треда
//pair< int, int > data; начало и конец блока памяти
// i - номер итерации
pair< int, int > memory_distribution(int step, int cur_thread, int i)
{
	pair< int, int > data;
	int s;
	s = cur_thread * step;
	data.first = s;
	data.second = s + pow(2, i) * step - 1;

	return data;
}
	
barrier* b;

int create_b(int amountOfThreads) {
	
	return amountOfThreads / 2;
}

int f = 0;

void sort_with_threads(double arr[], int cur_thread, int step, double* tmp, int amountOfThreads)
{
	f++;
	pair< int, int > block;
	int i = 0, size;
	
	if (f == 1) {
		create_b(amountOfThreads); 
		b = new barrier(amountOfThreads / 2);
	}
	
	int a=1;
	for (int i = 0; i <log2(amountOfThreads); i++) {
			block = memory_distribution(step, cur_thread, i); 		
			Sort(arr + block.first, pow(2, i) * step, tmp);
			a = 1 << i + 1;
			if (cur_thread % a != 0) 		
				return;
			else {
				if (a == amountOfThreads) 
					return;
					
				b->wait();
				b->reduce();	
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

	boost::thread *threads=new boost::thread[amountOfThreads];

	for (int i = 0; i < amountOfThreads; i++) 
		threads[i] = boost::thread(sort_with_threads, arr, i, step, ref(tmp),amountOfThreads);

	
	for (int i = 0; i < amountOfThreads; i++)
		threads[i].join();


	Merge(arr, n / 2, arr + n / 2, n - n / 2, tmp, 0);
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
	
	}

}



int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");

	test();

	return 0;
}
