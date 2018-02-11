#include <iostream>
#include <string>
using namespace std;

bool sequenceSearch(string s, int nc, char c)
{
	bool resultado = false;

	string seqchars;
	for (size_t j = 0; j < nc; j++)
		seqchars += c;


	if (s.find(seqchars) != -1)
		resultado = true;
	
	return resultado;
}

int main()
{
	char c;
	int nc;
	string s;

	cout << "Insert a string here: ";
	cin >> s;
	cout << "Character to be searched ? ";
	cin >> c;
	cout << "Number of times it appears ? ";
	cin >> nc;

	if (sequenceSearch(s, nc, c))
		cout << "TRUE\n";
	else cout << "FALSE\n";

	return 0;
}