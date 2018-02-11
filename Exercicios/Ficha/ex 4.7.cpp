#include <iostream>
#include <vector>
#include <cstddef>
using namespace std;

void readIntVector(vector<int> &v, int nElem)
{
	int valor;
	for (size_t i = 0; i < nElem; i++)
	{
		cin >> valor;
		v.push_back(valor);
	}
}

int searchValueInVector(const vector<int> &v, int value)
{
	for (int j = 0; j < v.size(); j++)
	{
		if (v.at(j) == value)
		{
			return j;
		}
	}
	return -1;
}

vector<int> searchMultValuesInIntVector(const vector<int> &v, int value)
{
	vector<int> result;

	for (size_t j = 0; j < v.size(); j++)
	{
		if (v[j] == value)
			result.push_back(j);
	}
	return result;
}

int main()
{
	int NElem, value;
	cout << "Number of elements of the array = ";
	cin >> NElem;

	cout << "Value to be found : ";
	cin >> value;

	vector<int> v;

	readIntVector(v, NElem);

	cout << "Value in position " <<
		searchValueInVector(v, value) << endl;

	cout << "Number of its appearances = " <<
		searchMultValuesInIntVector(v, value).size() << endl;

	return 0;
}