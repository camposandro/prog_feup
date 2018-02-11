#include <iostream>
#include <string>
#include <vector>

using namespace std;

void bubblesort(vector<string> &v)
{
	// vao ser feitas n comparacoes
	for (int i = 0; i < v.size(); i++)
	{
		// comparar elem com o elem seg.
		for (size_t j = 0; j < v.size() - 1; j++)
		{
			// fazer swap se n+1 < n
			if (v[j + 1] < v[j])
			{
				string t = v[j + 1];
				v[j + 1] = v[j];
				v[j] = t;
			}
		}
	}
}

int main()
{
	vector<string> vnames;
	string name;
	cout << "Insira nomes de pessoas:" << endl;

	// ciclo para adicionar nomes ao vetor vnames
	for (size_t i = 0;; i++)
	{
		cout << "Pessoa " << i + 1 << ": ";
		cin >> name;
		if (cin.eof()) break;
		vnames.push_back(name);
	}

	bubblesort(vnames);

	// imprime vetor ordenado
	cout << "Vetor ordenado: ";
	for (size_t k = 0; k < vnames.size(); k++)
		cout << vnames[k] << " ";
	cout << endl;

	return 0;
}