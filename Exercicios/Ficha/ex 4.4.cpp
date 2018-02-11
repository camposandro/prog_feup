#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string normalizeName(string name)
{
	const int NELEM = 5;
	size_t posFirstNotSpace, posLastNotSpace;
	string forbidden[] = { " DE ", " DO ", " DA ", " DAS ", " E " };

	// encontra pos de primeiro que nao e espaco
	posFirstNotSpace = name.find_first_not_of(' ');

	// encontra posicao do ultimo que nao e espaco
	for (size_t i = name.length() - 1; i >= 0; i--)
	{
		if (name.at(i) != ' ')
		{
			posLastNotSpace = i;
			break;
		}
	}

	// remove primeiro e ultimo espaco se houver
	name = name.substr(posFirstNotSpace, posLastNotSpace + 1);

	for (size_t i = 0; i <= name.length(); i++)
	{
		// coloca tudo a maiuscula
		name[i] = toupper(name[i]);
	}

	for (size_t j = 0; j < NELEM; j++)
	{
		int indexFound = name.find(forbidden[j]);
		int forbiddenLength = forbidden[j].length();

		if (indexFound != string::npos)
			name.replace(indexFound, forbiddenLength, " ");
	}

	return name;
}

int main()
{
	string name;

	cout << "Insert name: ";
	getline(cin, name);
	cout << "Normalized name: " << normalizeName(name) << endl;

	return 0;
}