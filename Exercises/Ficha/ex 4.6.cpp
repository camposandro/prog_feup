#include <iostream>
#include <cstddef>
using namespace std;

void readIntArray(int a[], int nElem)
{
	for (size_t i = 0; i < nElem; i++)
	{
		cout << "Elem " << i << " = ";
		cin >> a[i];
	}
}

int searchValueInIntArray(const int a[], int nElem, int value)
{
	int i = -1;

	for (size_t j = 0; j < nElem; j++)
	{
		if (a[j] == value)
		{
			i = j;
			break;
		}
	}
	return i;
}

int searchMultValuesInIntArray(const int a[], int nElem, int value, int index[])
{
	int i = -1, contador = 0;

	for (size_t j = 0; j < nElem; j++)
	{
		if (a[j] == value)
		{
			index[j] == j;
			contador++;
		}
	}
	return contador;
}

int main()
{
	const unsigned int NELEM = 100;
	int a[NELEM], index[NELEM], nElem, value;

	cout << "Number of elements of the array : ";
	cin >> nElem;
	cout << "Value to be found : ";
	cin >> value;

	readIntArray(a, nElem);
	cout << "Value in position " << 
		searchValueInIntArray(a, nElem, value) << endl;
	cout << "Number of its appearances = " << 
		searchMultValuesInIntArray(a, nElem, value, index) << endl;

	return 0;
}