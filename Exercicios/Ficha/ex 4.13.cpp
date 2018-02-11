#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void bubblesort(vector<string> &v);

int main()
{
	vector<string> vnomes;
	string nome;

	ifstream in_stream;
	in_stream.open("nomes.txt");

	if (in_stream.fail())
	{
		cerr << "Falha na leitura do ficheiro.\n";
		exit(1);
	}

	// coloca os nomes no vetor
	while (getline(in_stream,nome))
		vnomes.push_back(nome);

	// ordena valores no vetor
	bubblesort(vnomes);

	ofstream out_stream;
	out_stream.open("nomesOrdenados.txt");
	for (size_t i = 0; i < vnomes.size(); i++)
		out_stream << vnomes[i] << endl;

	if (out_stream.fail())
	{
		cerr << "Falha na escrita do ficheiro.\n";
		exit(1);
	}
	else cout << "Ficheiro criado com sucesso!\n";
	
	out_stream.close();
	in_stream.close();

	return 0;
}

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