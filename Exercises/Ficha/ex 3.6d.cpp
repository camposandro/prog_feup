#include <iostream>
using namespace std;

bool bissexto(int ano)
{
	if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)
		return true;
	else return false;
}

int ndiasmes(int ano, int mes)
{
	int ndias;

	switch (mes)
	{
	case 1: case 3: case 5: case 7:	case 8: case 10: case 12:
		ndias = 31;
		break;
	case 4: case 6: case 9: case 11:
		ndias = 30;
		break;
	case 2:
		if (bissexto(ano))
			ndias = 29;
		else ndias = 28;
	}

	return ndias;
}

int doisprimeirosdigitos(int ano)
{
	while (ano > 99)
		ano /= 10;

	return ano;
}

int diadasemana(int ano, int mes, int dia)
{
	int a = ano % 100;
	int c = 0;
	int d = dia;
	int s = doisprimeirosdigitos(ano);

	if (bissexto(ano))
	{
		switch (mes)
		{
		case 1: case 4: case 7:
			c = 6;
			break;
		case 2: case 8:
			c = 2;
			break;
		case 3: case 11:
			c = 3;
			break;
		case 9: case 12:
			c = 5;
			break;
		case 6:
			c = 4;
			break;
		case 5:
			c = 1;
			break;
		case 10:
			c = 0;
			break;
		}
	}
	else
	{
		switch (mes)
		{
		case 4: case 7:
			c = 6;
			break;
		case 8:
			c = 2;
			break;
		case 2: case 3: case 11:
			c = 3;
			break;
		case 9: case 12:
			c = 5;
			break;
		case 6:
			c = 4;
			break;
		case 5:
			c = 1;
			break;
		case 1: case 10:
			c = 0;
			break;
		}
	}

	int ds = (((5 * a) / 4) + c + d - 2 * (s % 4) + 7) % 7;
	return ds;
}

void calendario(int ano, int mes)
{
	switch (mes)
	{
	case 1:
		cout << "Janeiro/" << ano << endl;
		break;
	case 2:
		cout << "Fevereiro/" << ano << endl;
		break;
	case 3:
		cout << "Marco/" << ano << endl;
		break;
	case 4:
		cout << "Abril/" << ano << endl;
		break;
	case 5:
		cout << "Maio/" << ano << endl;
		break;
	case 6:
		cout << "Junho/" << ano << endl;
		break;
	case 7:
		cout << "Julho/" << ano << endl;
		break;
	case 8:
		cout << "Agosto/" << ano << endl;
		break;
	case 9:
		cout << "Setembro/" << ano << endl;
		break;
	case 10:
		cout << "Outubro" << ano << endl;
		break;
	case 11:
		cout << "Novembro/" << ano << endl;
		break;
	case 12:
		cout << "Dezembro/" << ano << endl;
		break;
	}

	cout << "Dom\t" << "Seg\t" << "Ter\t" << "Qua\t"
		<< "Qui\t" << "Sex\t" << "Sab\t" << endl;

	/**
	Se o dia for domingo (1) imprimem-se 7 dias na linha
	Se for segunda (2) imprimem-se 6
	Se for terca (3) imprimem-se 5
	Se for quarta (4) imprimem-se 4
	Se for quinta (5) imprimem-se 3
	Se for sexta (6) imprimem-se 2
	Se for sabado (0) imprime-se 1 ...
	Ou seja, imprimem-se:
	-> 7 - diasemana() + 1 (desde domingo até sexta)
	-> 1 no caso de ser sabado
	**/

	bool primeirasemana = true;
	for (int i = 1; i <= ndiasmes(ano, mes); i++)
	{
		if (primeirasemana)
		{
			for (int j = 1; j <= (8 - diadasemana(ano, mes, i)); j++)
			{
				// para definir a posicao de partida
				switch (diadasemana(ano, mes, 1))
				{
				case 1:
					cout << i << "\t";
					break;
				case 2:
					cout << "\t" << i << "\t";
					break;
				case 3:
					cout << "\t" << "\t" << i << "\t";
					break;
				case 4:
					cout << "\t" << "\t" << "\t" << i << "\t";
					break;
				case 5:
					cout << "\t" << "\t" << "\t" << "\t" << i << "\t";
					break;
				case 6:
					cout << "\t" << "\t" << "\t" << "\t" << "\t" << i << "\t";
					break;
				case 0:
					cout << "\t" << "\t" << "\t" << "\t" << "\t" << "\t" << i << endl;
					break;
				}
				break;
			}
			primeirasemana = false;
		}
		else
		{
			if (diadasemana(ano, mes, i) == 0)
				cout << i << endl;
			else
			{
				if (i == ndiasmes(ano, mes))
					cout << i << endl;
				else cout << i << "\t";
			}
		}
	}
}


int main()
{
	int ano, mes, dia;
	cout << "*********************\n";
	cout << "***CALENDARIO V1.0***\n";
	cout << "*********************\n\n";
	cout << "MES ? "; cin >> mes;
	cout << "ANO ? "; cin >> ano;
	cout << endl;

	/*
	int diasemana = diadasemana(ano, mes, dia);
	switch (diasemana)
	{
	case 0:
		cout << "Sabado" << endl;
		break;
	case 1:
		cout << "Domingo" << endl;
		break;
	case 2:
		cout << "Segunda" << endl;
		break;
	case 3:
		cout << "Terca-feira" << endl;
		break;
	case 4:
		cout << "Quarta-feira" << endl;
		break;
	case 5:
		cout << "Quinta-feira" << endl;
		break;
	case 6:
		cout << "Sexta-feira" << endl;
		break;
	}
	*/

	calendario(ano, mes);
	return 0;
}