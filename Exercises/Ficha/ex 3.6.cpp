#include <iostream>
using namespace std;

bool bissexto(int ano)
{
	if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)
		return true;
	else return false;
}

int ndias(int ano, int mes)
{
	switch (mes)
	{
	case '1': case '3': case '5': case '7': case '8': case '10': case '12':
		return 31;
	case '4': case '6': case '9': case '11':
		return 30;
	case '2':
		if (bissexto(ano))
			return 29;
		else return 28;
	}
}

void diasemana(int ano, int mes, int dia)
{
	int a = ano / 100;
	int c = 0; // c depende de ser bissexto ou nao
	int d = dia;
	int s = ano % 100;

	if (bissexto(ano))
	{
		switch (mes)
		{
		case '1': case '4': case '7':
			c = 6;
			break;
		case '2': case '8':
			c = 2;
			break;
		case '3': case '11':
			c = 3;
			break;
		case '6':
			c = 4;
			break;
		case '5':
			c = 1;
			break;
		case '10':
			c = 0;
			break;
		case '9': case '12':
			c = 5;
			break;
		}
	}
	else
	{
		switch (mes)
		{
		case '4': case '7':
			c = 6;
			break;
		case '8':
			c = 2;
			break;
		case '2': case '3': case '11':
			c = 3;
			break;
		case '6':
			c = 4;
			break;
		case '5':
			c = 1;
			break;
		case '1': case '10':
			c = 0;
			break;
		case '9': case '12':
			c = 5;
			break;
		}
	}

	int ds = ((((5 * a) / 4) + c + d - 2 * (s % 4) + 7) % 7);

	switch (ds)
	{
	case '0':
		cout << "Sabado";
		break;
	case '1':
		cout << "Domingo";
		break;
	case '2':
		cout << "Segunda";
		break;
	case '3':
		cout << "Terca";
		break;
	case '4':
		cout << "Quarta";
		break;
	case '5':
		cout << "Quinta";
		break;
	case '6':
		cout << "Sexta";
		break;
	default:
		cout << "ERRO";
	}
}

int main()
{
	int ano, mes, dia;
	cout << "Insere ano, mes e dia: ";
	cin >> ano >> mes >> dia;

	return 0;
}