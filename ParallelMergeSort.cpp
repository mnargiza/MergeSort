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

mutex m;
int f;
std::mutex mu;
std::condition_variable cv;
bool _var = false;
bool ret() { return _var; }
int z=0,l=0;
bool endB = false;
void sort_with_threads(double arr[], int cur_thread, int step, double* tmp, int amountOfThreads)
{

	for (int i = 0; i < log2(amountOfThreads); i++) {
		//pair< int, int > block = memory_distribution(step, cur_thread, i);
		int s = cur_thread * step;
		Sort(arr + s, (1 << i) * step, tmp);
		int a = 1 << i + 1;
		endB = false;
		/*m.lock();
		cout << "a = "<<a<<" cur_thread = "<< cur_thread<<" size ="<< (1 << i) * step<<endl;
		cout <<"threadCount = "<< b->threadCount << endl;
		m.unlock();*/
		int k = 0;
		
		if (cur_thread % a != 0) {
			m.lock();
			f++;
			/*cout << "z = " << z << endl;
			cout << "endB" << endB<< endl;*/
			m.unlock();
			return;
			
		}
		else {

			/*z = 0;
			m.lock();
			b->reduce();
			m.unlock();*/

			b->wait();
			
			endB = true;
			_var = (f == b->threadCount);
			m.lock();
			cout << "var=" << _var << endl;
			m.unlock();
			unique_lock<mutex> ulm(mu);
			cv.wait(ulm, ret);
			cout << "f = " << f << endl;
			if (f == b->threadCount) {
				//m.lock();
				cout << "reduce" << endl;
				b->reduce();
				cout << "threadCount = " << b->threadCount << " cur_thread = " << cur_thread << endl;
				_var = true;
				cv.notify_all();
				//m.unlock();
			}
			/*endB = false;
			z = 0;
			l = 0;*/

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
