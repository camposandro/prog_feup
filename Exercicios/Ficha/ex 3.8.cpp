#include <iostream>
using namespace std;

int mdc(int m, int n)
{
	int gcd;
	if (m % n == 0)
		gcd = n;
	else
		gcd = mdc(n, m % n);

	return gcd;
}

int main()
{
	int n1, n2;
	cout << "Insert 2 numbers here: ";
	cin >> n1 >> n2;

	cout << mdc(n1, n2) << endl;
	return 0;
}
