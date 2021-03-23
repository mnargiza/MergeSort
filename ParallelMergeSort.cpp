#include "Header.h"

boost::mutex m;


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


void sort_with_threads(double arr[], int cur_thread, int step, double* tmp)
{
	pair< int, int > block;
	int i = 0;
	if (cur_thread % 2 != 0) {
		block = memory_distribution(step, cur_thread, i);
		
		/*cout << "cur_thread = " << cur_thread << " " << "iter = " << i << endl;
		cout << block.first << " ";
		cout << block.second << endl;
		cout << "size = " << pow(2, i) * step << endl;*/
		Sort(arr + block.first, pow(2, i) * step, tmp);
	
	}
	else {
		for (int i = 0; i < log2(amountOfThreads); i++) {
			block = memory_distribution(step, cur_thread, i);
			int size = pow(2, i) * step;
			/*cout << "cur_thread = " << cur_thread << " " << "iter = " << i << endl;
			cout << block.first << " ";
			cout << block.second << endl;
			cout << "size = " << size << endl;*/
			
			if (size == step)
				Sort(arr + block.first, pow(2, i) * step, tmp);
			else {
				m.lock();
				
				//cout << "Merge" << endl;

				Sort(arr + block.first, pow(2, i) * step, tmp);
				/*Merge(arr + block.first, size, arr + block.first+size, size, tmp, block.first);
				for (i = 0; i < size *2; i++)
					arr[i + block.first] = tmp[i + block.first];*/
				//cout << "copied" << endl;
				m.unlock();
				
			}	
			
		}
		
	}
}

// Merge Sort with threads
void task_2(double arr[], int n, double* tmp) {

	if (n < amountOfThreads) {
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
	step = n / amountOfThreads;
	
	boost::thread threads[amountOfThreads];

	for (int i = 0; i < amountOfThreads; i++) {

		threads[i] = boost::thread(sort_with_threads, arr, i, step, ref(tmp));

	}

	for (int i = 0; i < amountOfThreads; i++)
		threads[i].join();

	//cout << "last step" << endl;
	
	Merge(arr, n / 2, arr + n / 2, n-n / 2, tmp, 0);
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
		//cout << arr[i]<<" ";
	}
	
}
int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
	
	test();
	
	return 0;
}
