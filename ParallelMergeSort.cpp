#include "Header.h"

/*void hello()
{
	cout <<
		"Hello world, I'm a thread!"
		<< endl;
}*/

int main(int argc, char* argv[])
{
	///boost::thread thrd(&hello);
	//thrd.join();

	setlocale(LC_CTYPE, "rus");

	int n; // размер массива

	cout << "Введите размер массива чисел: ";
	cin >> n;

	
	double *arr = new double[n];

	for (int i = 0; i < n; i++) {
		arr[i] = rand() % n;
		cout << arr[i] << ' ';
	}

	double *tmp = new double[n];
	Sort(arr, n, tmp);

	cout << endl;
	cout << "Ответ: "<< endl;
	for (int i = 0; i < n; i++) {
		cout << tmp[i] << ' ';
	}
	return 0;
}