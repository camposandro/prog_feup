#include <iostream>
#include <vector>
using namespace std;

int binarySearch(const vector<int> &v, int value)
{
	int bottom = 0;
	int top = v.size() - 1;
	int middle = 0;

	bool found = false;
	while (bottom <= top && found == false)
	{
		middle = (bottom + top) / 2;
		if (v[middle] < value)
			bottom += 1;
		else if (v[middle] > value)
			top -= 1;
		else
		{
			found = true;
			return middle;
		}
	}
	return -1;
}

int main()
{
	vector<int> vnumbers;
	int number, value;
	cout << "Insira valor a procurar: ";
	cin >> value;
	cout << "Insira valores em ordem crescente" << endl;

	// ciclo para adicionar nomes ao vetor vnames
	for (size_t i = 0;; i++)
	{
		cout << "Valor " << i << ": ";
		cin >> number;
		if (cin.eof()) break;
		vnumbers.push_back(number);
	}

	cout << "Valor encontrado na posicao " <<
		binarySearch(vnumbers, value) << endl;

	return 0;
}