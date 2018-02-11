#include <iostream>
#include <string>
using namespace std;

bool isHydroxide(char compound[])
{
	int length = 0;
	while (compound[length] != '\0') length++;

	if (compound[length - 2] == 'O' && compound[length - 1] == 'H')
		return true;
	else return false;
}

bool isHydroxideString(string compound)
{
	string last2chars = compound.substr(compound.length() - 2);
	if (last2chars == "OH")
		return true;
	else return false;
}

int main()
{
	char compound1[] = "KOH";
	char compound2[] = "H202";
	char compound3[] = "NaCl";
	char compound4[] = "NaOH";
	char compound5[] = "C9H8O4";
	char compound6[] = "MgOH";

	cout << "Compound 1: " << isHydroxide(compound1) << endl;
	cout << "Compound 2: " << isHydroxide(compound2) << endl;
	cout << "Compound 3: " << isHydroxide(compound3) << endl;
	cout << "Compound 4: " << isHydroxide(compound4) << endl;
	cout << "Compound 5: " << isHydroxide(compound5) << endl;
	cout << "Compound 6: " << isHydroxide(compound6) << endl;
	cout << endl;

	string compoundA = "KOH";
	string compoundB = "H202";
	string compoundC = "NaCl";
	string compoundD = "NaOH";
	string compoundE = "C9H8O4";
	string compoundF = "MgOH";

	cout << "Compound A: " << isHydroxideString(compoundA) << endl;
	cout << "Compound B: " << isHydroxideString(compoundB) << endl;
	cout << "Compound C: " << isHydroxideString(compoundC) << endl;
	cout << "Compound D: " << isHydroxideString(compoundD) << endl;
	cout << "Compound E: " << isHydroxideString(compoundE) << endl;
	cout << "Compound F: " << isHydroxideString(compoundF) << endl;

	return 0;
}