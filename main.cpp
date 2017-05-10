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
void definirHorario();
Company createCompany();
unsigned int menuPrincipal();
void menuGestaoLinhas(Company semprarrolar);
void menuGestaoCondutores(Company semprarrolar);
void menuOpcoesLinha(Company semprarrolar);
void menuOpcoesPercursos(Company semprarrolar);

// variáveis globais
string nameCompany;
string inCondutores;
string inLinhas;
unsigned int horaInicio, horaFim;

int main()
{
	cout << "Nome da companhia: ";
	getline(cin, nameCompany);

	cout << "--- EMPRESA DE TRANSPORTES " + nameCompany + " ---\n" << endl;

	// ler os ficheiros e criar companhia
	Company semprarrolar = createCompany();

	// definir horario de funcionamento
	definirHorario();
	
	// chamar menu com companhia
	menuPrincipal();

	// testes
	semprarrolar.addDriver();
	semprarrolar.addLine();
	semprarrolar.visualizaCondutores();
	semprarrolar.visualizaLinhas();
	semprarrolar.changeDriver();
	semprarrolar.changeLine();
	semprarrolar.visualizaCondutores();
	semprarrolar.visualizaLinhas();
	semprarrolar.removeDriver();
	semprarrolar.removeLine();
	semprarrolar.visualizaCondutores();
	semprarrolar.visualizaLinhas();

	// falta alterar linhas e condutores, horarios ...
	// falta atualizar ficheiros no final

	return 0;
}

// definir horario de inicio e fim de serviço
void definirHorario()
{
	unsigned int horaDeInicio;
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

	unsigned int horaDeFim;
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

// menus
unsigned int menuPrincipal()
{
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n";
	cout << "1. Gestao de linhas\n"
		<< "2. Gestao de condutores\n"
		<< "3. Visualizar percursos\n"
		<< "4. Visualizar linhas\n"
		<< "5. Visualizar condutores\n"
		<< "0. Sair\n";
	cout << endl;

	unsigned int choice;
	cout << "--> opcao ";
	cin >> choice;

	while (choice > 5 || choice < 0)
	{
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
	}
	
	return choice;
}

void OpcoesPrincipal(Company semprarrolar)
{
	unsigned int choice;
	while (choice = menuPrincipal())
	{
		switch (choice)
		{
		case 0:
			semprarrolar.atualizaFicheiroCondutores(inCondutores);
			semprarrolar.atualizaFicheiroLinhas(inLinhas);
			cout << endl;
			break;
		case 1:
			menuGestaoLinhas(semprarrolar);
			break;
		case 2:
			menuGestaoCondutores(semprarrolar);
			break;
		case 3:
			menuOpcoesPercursos(semprarrolar);
			break;
		case 4:
			menuOpcoesLinha(semprarrolar);
			break;
		case 5:
			semprarrolar.visualizaCondutores();
			break;
		default:
			cout << "Introduza uma opcao valida!\n";
		}
	}
}

unsigned int menuGestaoLinhas()
{
	cout << endl;
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n";
	cout << "A. Criar linha\n"
		<< "B. Alterar linha\n"
		<< "C. Remover linha\n"
		<< "# MENU ANTERIOR\n\n";

	char choice;
	cout << "--> opcao ";
	cin >> choice;

	while (choice != 'A' && choice != 'B' && choice != 'C' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
	}

	return choice;
}

void opcoesGestaoLinhas(Company semprarrolar)
{
	unsigned int choice;
	while (choice = menuGestaoLinhas())
	{
		switch (choice)
		{
		case 'A':
			semprarrolar.addLine();
			break;
		case 'B':
			semprarrolar.changeLine();
			break;
		case 'C':
			semprarrolar.removeLine();
			break;
		}
	}
}

unsigned int menuGestaoCondutores()
{
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n";
	cout << "A. Criar condutor\n"
		<< "B. Alterar condutor\n"
		<< "C. Remover condutor\n"
		<< "# MENU ANTERIOR\n\n";

	char choice;
	cout << "--> opcao ";
	cin >> choice;

	while (choice != 'A' && choice != 'B' && choice != 'C' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
	}

	return choice;
}

void opcoesGestaoCondutores(Company semprarrolar)
{
	unsigned int choice;
	while (choice = menuGestaoCondutores())
	{
		switch (choice)
		{
		case 'A':
			semprarrolar.addDriver();
			break;
		case 'B':
			semprarrolar.changeDriver();
			break;
		case 'C':
			semprarrolar.removeDriver();
			break;
		}
	}
}

unsigned int menuOpcoesVisualizarLinha()
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
}

void opcoesVisualizarLinha(Company semprarrolar)
{
	unsigned int choice;
	while (choice = menuOpcoesVisualizarLinha())
	{
		switch (choice)
		{
		case 'A':
			semprarrolar.visualizaLinhas();
			break;
		case 'B':
			//semprarrolar.horarioLinha();
			break;
		}
	}
}

unsigned int menuOpcoesPercursos()
{
	cout << "A. Pesquisar por paragem nas linhas\n"
		<< "B. Visualizar percurso entre 2 paragens\n"
		<< "C. Visualizar horario de paragem\n"
		<< "# MENU ANTERIOR\n";
	cout << endl;

	char choice;
	cout << "--> opcao ";
	cin >> choice;

	while (choice != 'A' && choice != 'B' && choice != 'C' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
	}

	return choice;
}

void opcoesPercursos(Company semprarrolar)
{
	unsigned int choice;
	while (choice = menuOpcoesPercursos())
	{
		switch (choice)
		{
		case 'A':
			semprarrolar.pesquisaParagem();
			break;
		case 'B':
			//semprarrolar.percursoEntreParagens();
			break;
		case 'C':
			//semprarrolar.horarioParagem();
			break;
		}
	}
}

// abrir ficheiros de linhas e condutores
Company createCompany()
{
	// OPENING OF THE INPUT FILE - CONDUTORES
	cout << "Nome do ficheiro de condutores a abrir ? \n";
	cout << "--> ";
	getline(cin, inCondutores);

	ifstream fCondutores(inCondutores);
	if (fCondutores.fail())
	{
		cerr << "Erro ao abrir o ficheiro de condutores!" << endl;
		cout << "Pressione uma tecla para sair ...\n";
		_getch();
		exit(1);
	}
	// --------------------------------------------------------

	// OPENING OF THE INPUT FILE - LINHAS
	cout << "Nome do ficheiro de linhas a abrir ? \n";
	cout << "--> ";
	getline(cin, inLinhas);

	ifstream fLinhas(inLinhas);
	if (fLinhas.fail())
	{
		cerr << "Erro ao abrir o ficheiro de linhas!" << endl;
		cout << "Pressione uma tecla para sair ...\n";
		_getch();
		exit(1);
	}

	Company semprarrolar(nameCompany, inCondutores, inLinhas);
	return semprarrolar;
}