#include <iostream>
using namespace std;

void menuprincipal();
float menusoma();
float menusubtracao();
float menumultiplicacao();
float menudivisao();

int main()
{
	cout << "CALCULADORA\n\n";
	menuprincipal();
	return 0;
}

void menuprincipal()
{
	int opcao;
	cout << "MENU PRINCIPAL\n";
	cout << "1. Soma\n";
	cout << "2. Subtracao\n";
	cout << "3. Multiplicacao\n";
	cout << "4. Divisao\n";
	cout << "5. Sair\n\n";
	cin >> opcao;

	if (opcao != 5)
	{
		switch (opcao)
		{
		case 1:
			menusoma();
			break;
		case 2:
			menusubtracao();
			break;
		case 3:
			menumultiplicacao();
			break;
		case 4:
			menudivisao();
			break;
		}
	}
	else exit(0);
}

float menusoma()
{
	float valor1, valor2, soma;
	cout << "-----MENU SOMA-----" << endl;
	cout << "PARA SAIR PRESS 0" << endl;
	cout << "Insere operando1: ";
	cin >> valor1;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando1: ";
		cin >> valor1;
	}

	if (valor1 == 0) {
		cout << endl;
		menuprincipal();
	}

	cout << "Insere operando2: ";
	cin >> valor2;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando2: ";
		cin >> valor2;
	}

	if (valor1 != 0)
	{
		soma = valor1 + valor2;
		cout << "Resultado = " << soma << endl << endl;
		menuprincipal();
	}
	else
		menuprincipal();

	return 0;
}

float menusubtracao()
{
	float valor1, valor2, subtracao;
	cout << "--MENU DIFERENCA--" << endl;
	cout << "PARA SAIR PRESS 0" << endl;
	cout << "Insere operando1: ";
	cin >> valor1;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando1: ";
		cin >> valor1;
	}

	if (valor1 == 0) {
		cout << endl;
		menuprincipal();
	}

	cout << "Insere operando2: ";
	cin >> valor2;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando2: ";
		cin >> valor2;
	}

	if (valor1 != 0)
	{
		subtracao = valor1 - valor2;
		cout << "Resultado = " << subtracao << endl << endl;
		menuprincipal();
	}
	else
		menuprincipal();

	return 0;
}

float menumultiplicacao()
{
	float valor1, valor2, produto;
	cout << "MENU MULTIPLICACAO" << endl;
	cout << "PARA SAIR PRESS 0" << endl;
	cout << "Insere operando1: ";
	cin >> valor1;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando1: ";
		cin >> valor1;
	}

	if (valor1 == 0) {
		cout << endl;
		menuprincipal();
	}

	cout << "Insere operando2: ";
	cin >> valor2;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando2: ";
		cin >> valor2;
	}

	if (valor1 != 0)
	{
		produto = valor1 * valor2;
		cout << "Resultado = " << produto << endl << endl;
		menuprincipal();
	}
	else
		menuprincipal();

	return 0;
}

float menudivisao()
{
	float valor1, valor2, divisao;
	cout << "---MENU DIVISAO---" << endl;
	cout << "PARA SAIR PRESS 0" << endl;
	cout << "Insere operando1: ";
	cin >> valor1;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando1: ";
		cin >> valor1;
	}

	if (valor1 == 0) {
		cout << endl;
		menuprincipal();
	}

	cout << "Insere operando2: ";
	cin >> valor2;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insere operando2: ";
		cin >> valor2;
	}

	if (valor1 != 0)
	{
		divisao = valor1 / valor2;
		cout << "Resultado = " << divisao << endl << endl;
		menuprincipal();
	}
	else
		menuprincipal();

	return 0;
}
