#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

#include "Bus.h"
#include "Company.h"
#include "Driver.h"
#include "Line.h"
#include "Shift.h"

using namespace std;

// protótipos das funções do main
void openFiles();
void definirHorario();
void menu();

int main()
{
	cout << "--- EMPRESA DE TRANSPORTES SEMPRARROLAR ---\n" << endl;

	// ler os ficheiros
	openFiles();
	// definir horario de funcionamento
	definirHorario();

	menu();

	// testes
	Company abc("abc", "condutores", "linhas");
	abc.createDriver();
	abc.createLine();
	abc.removeDriver();
	abc.removeLine();

	return 0;
}

// menu principal
void menu()
{
	cout << endl;
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n";
	cout << "1. Gestao de linhas\n"
		<< "2. Gestao de condutores\n"
		<< "3. Visualizar percursos\n"
		<< "4. Visualizar linhas\n"
		<< "5. Visualizar condutores\n"
		<< "0. Sair\n";
	cout << endl;

	int choice;
	cout << "--> opcao ";
	cin >> choice;

	while (choice > 5 || choice < 0)
	{
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
	}

	switch (choice)
	{
	case 0:
		// atualizaFicheiroLinhas();
		// atualizaFicheiroCondutores();
		cout << endl;
		break;
	case 1:
		//menuGestaoLinhas();
		break;
	case 2:
		//menuGestaoCondutores();
		break;
	case 3:
		//menuOpcoesPercursos();
		break;
	case 4:
		//menuOpcoesLinha();
		break;
	case 5:
		// visualizaCondutores();
		break;
	default:
		cout << "Introduza uma opcao valida!\n";
	}
}

// resto dos menus
/*
void menuGestaoLinhas()
{
	cout << endl;
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n";
	cout << "A. Criar linha\n"
		<< "B. Alterar linha\n"
		<< "C. Remover linha\n"
		<< "# MENU ANTERIOR\n\n";

	char opcao;
	cout << "--> opcao ";
	cin >> opcao;

	while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> opcao;
	}

	switch (opcao)
	{
	case '#':
		menu();
		break;
	case 'A':
		//createLine();
		break;
	case 'B':
		//alteraLinha();
		break;
	case 'C':
		//removeLinha();
		break;
	}
}

void menuGestaoCondutores()
{
	cout << endl;
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n";
	cout << "A. Criar condutor\n"
		<< "B. Alterar condutor\n"
		<< "C. Remover condutor\n"
		<< "# MENU ANTERIOR\n\n";

	char opcao;
	cout << "--> opcao ";
	cin >> opcao;

	while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> opcao;
	}

	switch (opcao)
	{
	case '#':
		menu();
		break;
	case 'A':
		//criaCondutor();
		break;
	case 'B':
		//alteraCondutor();
		break;
	case 'C':
		//removeCondutor();
		break;
	}
}

void menuOpcoesLinha()
{
	cout << endl;
	cout << "A. Visualizar informacao de linha\n"
		<< "B. Visualizar horario de linha\n"
		<< "# MENU ANTERIOR\n\n";

	char newChoice;
	cout << "--> opcao ";
	cin >> newChoice;

	while (newChoice != 'A' && newChoice != 'B' && newChoice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> newChoice;
	}

	switch (newChoice)
	{
	case '#':
		menu();
		break;
	case 'A':
		//visualizaLinhas();
		break;
	case 'B':
		//horarioLinha();
		break;
	}
}

void menuOpcoesPercursos()
{
	cout << endl;
	cout << "A. Pesquisar por paragem nas linhas\n"
		<< "B. Visualizar percurso entre 2 paragens\n"
		<< "C. Visualizar horario de paragem\n"
		<< "# MENU ANTERIOR\n";
	cout << endl;

	char newChoice;
	cout << "--> opcao ";
	cin >> newChoice;

	while (newChoice != 'A' && newChoice != 'B' && newChoice != 'C' && newChoice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> newChoice;
	}

	switch (newChoice)
	{
	case '#':
		menu();
		break;
	case 'A':
		//pesquisaParagem();
		break;
	case 'B':
		//percursoEntreParagens();
		break;
	case 'C':
		//horarioParagem();
		break;
	}
}
*/

// abrir ficheiros de linhas e condutores
void openFiles()
{
	// OPENING OF THE INPUT FILE - CONDUTORES
	string inCondutores;
	cout << "Nome do ficheiro de condutores a abrir ? (.txt)\n";
	cout << "--> ";
	getline(cin, inCondutores);

	ifstream fCondutores(inCondutores + ".txt");
	if (fCondutores.fail())
	{
		cerr << "Erro ao abrir o ficheiro de condutores!" << endl;
		cout << "Pressione uma tecla para sair ...\n";
		_getch();
		exit(1);
	}
	// --------------------------------------------------------

	// OPENING OF THE INPUT FILE - LINHAS
	string inLinhas;
	cout << "Nome do ficheiro de linhas a abrir ? (.txt)\n";
	cout << "--> ";
	getline(cin, inLinhas);

	ifstream fLinhas(inLinhas + ".txt");
	if (fLinhas.fail())
	{
		cerr << "Erro ao abrir o ficheiro de linhas!" << endl;
		cout << "Pressione uma tecla para sair ...\n";
		_getch();
		exit(1);
	}
}

// definir horario de inicio e fim de serviço
int horaInicio, horaFim;
void definirHorario()
{
	int horaDeInicio;
	cout << "Horario de inicio de servico: ";
	cin >> horaDeInicio;

	while (cin.fail() || horaDeInicio > 23 || horaDeInicio < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma hora valida!\n";
		cout << "Horario de inicio de servico: ";
		cin >> horaDeInicio;
	}
	horaInicio = horaDeInicio;

	int horaDeFim;
	cout << "Horario de fim de servico: ";
	cin >> horaDeFim;

	while (cin.fail() || horaDeFim > 23 || horaDeFim < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma hora valida!\n";
		cout << "Horario de fim de servico: ";
		cin >> horaDeFim;
	}
	horaFim = horaDeFim;
}