#include <iostream>
using namespace std;

struct Fraction
{
	int numerator;
	int denominator;
};

Fraction readFracc();
Fraction reduceFracc(Fraction f);
Fraction sum(Fraction f, Fraction f1);
Fraction diff(Fraction f, Fraction f1);
Fraction prod(Fraction f, Fraction f1);
Fraction div(Fraction f, Fraction f1);

int main()
{
	Fraction f = readFracc();
	f = reduceFracc(f);

	Fraction f1 = readFracc();
	f1 = reduceFracc(f1);

	sum(f, f1);
	diff(f, f1);
	prod(f, f1);
	div(f, f1);

	return 0;
}

Fraction readFracc()
{
	Fraction f;
	char character;
	cout << "Numerator / Denominator ?\n";
	cin >> f.numerator;
	cin >> character;
	cin >> f.denominator;

	return f;
}

// ALGORITMO DE EUCLIDES - mdc
int gcd(int x, int y)
{
	if (x < y)
		swap(x, y);

	while (y > 0)
	{
		int f = x % y;
		x = y;
		y = f;
	}
	return x;
}

Fraction reduceFracc(Fraction f)
{
	int mdc = gcd(f.numerator, f.denominator);
	f.numerator /= mdc;
	f.denominator /= mdc;
	
	return f;
}

Fraction sum(Fraction f, Fraction f1)
{
	int result_numerator = f.numerator + f1.numerator;
	int result_denominator = f.denominator;

	if (f.denominator != f1.denominator)
	{
		result_denominator = f.denominator * f1.denominator;
		result_numerator = f.numerator * f1.denominator + f1.numerator * f.denominator;
	}

	Fraction fr = { result_numerator , result_denominator };
	fr = reduceFracc(fr);
	cout << "SUM = " << fr.numerator << " / " << fr.denominator << endl;
	return fr;
}

Fraction diff(Fraction f, Fraction f1)
{
	int result_numerator = f.numerator - f1.numerator;
	int result_denominator = f.denominator;

	if (f.denominator != f1.denominator)
	{
		result_denominator = f.denominator * f1.denominator;
		result_numerator = f.numerator * f1.denominator - f1.numerator * f.denominator;
	}

	Fraction fr = { result_numerator , result_denominator };
	fr = reduceFracc(fr);
	cout << "DIFF = " << fr.numerator << " / " << fr.denominator << endl;
	return fr;
}

Fraction prod(Fraction f, Fraction f1)
{
	int result_numerator = f.numerator * f1.numerator;
	int result_denominator = f.denominator * f1.denominator;

	Fraction fr = { result_numerator , result_denominator };
	fr = reduceFracc(fr);
	cout << "PROD = " << fr.numerator << " / " << fr.denominator << endl;
	return fr;
}

Fraction div(Fraction f, Fraction f1)
{
	int result_numerator = f.numerator * f1.denominator;
	int result_denominator = f1.numerator * f.denominator;

	Fraction fr = { result_numerator , result_denominator };
	fr = reduceFracc(fr);
	cout << "DIV = " << fr.numerator << " / " << fr.denominator << endl;
	return fr;
}
