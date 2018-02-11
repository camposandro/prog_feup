#include <iostream>
#include <string>
using namespace std;

void decompose(string compound)
{
	for (int i = 0; i < compound.length(); i++)
	{
		if (compound[i] >= 'A' && compound[i] <= 'Z')
			if (compound[i + 1] < 'a' || compound[i + 1] > 'z')
				cout << compound[i] << endl;
			else cout << compound[i];
		else if (compound[i] >= 'a' && compound[i] <= 'z')
			cout << compound[i] << endl;
	}
}

int main()
{
	string compound;
	cout << "INSERT COMPOUND: \n";
	cin >> compound;
	decompose(compound);
	return 0;
}