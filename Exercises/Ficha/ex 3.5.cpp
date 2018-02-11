#include <iostream>
using namespace std;

bool readFracc(int &numerator, int &denominator)
{
	char character;
	cout << "Numerator / Denominator ?\n";
	cin >> numerator;
	cin >> character;
	cin >> denominator;

	if (character == '/')
		if (!cin.fail())
			return true;
		else return false;
	else return false;
}

void writeFracc(int numerator, int denominator)
{
	cout << numerator << " / " << denominator << endl;
}


// ALGORITMO DE EUCLIDES - mdc
int gcd(int x, int y)
{
	if (x < y)
		std::swap(x, y);

	while (y > 0)
	{
		int f = x % y;
		x = y;
		y = f;
	}
	return x;
}

void reduceFracc(int &numerator, int &denominator)
{
	int mdc = gcd(numerator, denominator);
	numerator /= mdc;
	denominator /= mdc;
	
}

void sum(int numerator, int denominator, int numerator1, int denominator1)
{
	int result_numerator = numerator + numerator1;
	int result_denominator = denominator;

	if (denominator != denominator1)
	{
		result_denominator = denominator * denominator1;
		result_numerator = numerator * denominator1 + numerator1 * denominator;
	} 

	reduceFracc(result_numerator, result_denominator);
	cout << "SUM = " << result_numerator << " / " << result_denominator << endl;
}

void diff(int numerator, int denominator, int numerator1, int denominator1)
{
	int result_numerator = numerator - numerator1;
	int result_denominator = denominator;

	if (denominator != denominator1)
	{
		result_denominator = denominator * denominator1;
		result_numerator = numerator * denominator1 - numerator1 * denominator;
	}

	reduceFracc(result_numerator, result_denominator);
	cout << "DIFF = " << result_numerator << " / " << result_denominator << endl;
}

void prod(int numerator, int denominator, int numerator1, int denominator1)
{
	int result_numerator = numerator * numerator1;
	int result_denominator = denominator * denominator1;

	reduceFracc(result_numerator, result_denominator);
	cout << "PROD = " << result_numerator << " / " << result_denominator << endl;
}

void div(int numerator, int denominator, int numerator1, int denominator1)
{
	int result_numerator = numerator * denominator1;
	int result_denominator = numerator1 * denominator;

	reduceFracc(result_numerator, result_denominator);
	cout << "DIV = " << result_numerator << " / " << result_denominator << endl;
}

int main()
{
	int num = 0, denom = 0, num1 = 0, denom1 = 0;
	readFracc(num, denom);
	readFracc(num1, denom1);
	reduceFracc(num, denom);
	
	sum(num, denom, num1, denom1);
	diff(num, denom, num1, denom1);
	prod(num, denom, num1, denom1);
	div(num, denom, num1, denom1);

	return 0;
}