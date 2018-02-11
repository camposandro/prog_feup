#include <iostream>
#include <vector>
using namespace std;

void bubblesort(vector<int> &v);
void removeDuplicates(vector<int> &v);

vector<int> uniao(const vector<int> &v1, const vector<int> &v2)
{
	vector<int> vresult = v1;

	for (size_t i = 0; i < v2.size(); i++)
		vresult.push_back(v2.at(i));

	removeDuplicates(vresult);
	return vresult;
}

vector<int> intersecao(const vector<int> &v1, const vector<int> &v2)
{
	vector<int> vresult;
	for (size_t i = 0; i < v1.size(); i++)
	{
		for (size_t j = 0; j < v2.size(); j++)
		{
			if (v1.at(i) == v2.at(j))
				vresult.push_back(v1.at(i));
		}
	}

	removeDuplicates(vresult);
	return vresult;
}

int main()
{
	vector<int> vnumbers1, vnumbers2;
	int number;
	cout << "Insert vector values\n(< 0 to END VECTOR)\n\n";

	// insercao de valores
	cout << "---Vector 1---" << endl;
	for (size_t i = 0;; i++)
	{
		cout << "v1[" << i + 1 << "]: ";
		cin >> number;
		if (number < 0) break;
		vnumbers1.push_back(number);
	}

	cout << "---Vector 2---" << endl;
	for (size_t j = 0;; j++)
	{
		cout << "v2[" << j + 1 << "]: ";
		cin >> number;
		if (number < 0) break;
		vnumbers2.push_back(number);
	}
	cout << endl;

	// ORGANIZA VETORES
	bubblesort(vnumbers1);
	bubblesort(vnumbers2);
	//------------------

	// VETORES RESULTADO
	vector<int> vunion, vintersec;

	vunion = uniao(vnumbers1, vnumbers2);
	cout << "UNION VECTOR : {";
	for (int f = 0; f < vunion.size(); f++)
	{
		if (f == vunion.size() - 1)
			cout << vunion[f];
		else
			cout << vunion[f] << ",";
	}
	cout << "}" << endl;

	vintersec = intersecao(vnumbers1, vnumbers2);
	cout << "INTERSECTION VECTOR: {";
	for (int g = 0; g < vintersec.size(); g++)
	{
		if (g == vintersec.size() - 1)
			cout << vintersec[g];
		else
			cout << vintersec[g] << ",";
	}
	cout << "}" << endl << endl;
	// -----------------------------------------

	return 0;
}

// FUNCOES AUXILIARES
void bubblesort(vector<int> &v)
{
	// vao ser feitas n comparacoes
	for (size_t i = 0; i < v.size(); i++)
	{
		// comparar elem com o elem seg.
		for (size_t j = 0; j < v.size() - 1; j++)
		{
			// fazer swap se n+1 < n
			if (v[j + 1] < v[j])
			{
				int t = v[j + 1];
				v[j + 1] = v[j];
				v[j] = t;
			}
		}
	}
}

void removeDuplicates(vector<int> &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		int number = v[i];
		int counter = 0;

		for (size_t a = 0; a < v.size(); a++)
		{
			if (v.at(a) == number)
				counter++;

			if (v.at(a) == number && counter > 1)
			{
				if (a + 1 >= v.size())
					v.resize(v.size() - 1);
				else
				{
					for (size_t b = a; b < v.size() - 1; b++)
					{
						v.at(b) = v.at(b + 1);
					}
					v.resize(v.size() - 1);
				}
				counter = 1;
			}
		}
	}
}