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
Company createCompany();
void definirHorario();
unsigned int menuPrincipal();
void opcoesPrincipal(Company &semprarrolar);
char menuGestaoLinhas();
void opcoesGestaoLinhas(Company &semprarrolar);
char menuGestaoCondutores();
void opcoesGestaoCondutores(Company &semprarrolar);
char menuOpcoesVisualizarLinha();
void opcoesVisualizarLinha(Company semprarrolar);
char menuOpcoesPercursos();
void opcoesPercursos(Company semprarrolar);
void changeDriver(unsigned int driverId, Company &semprarrolar);
void removeDriver(int posDriver, Company &semprarrolar);
void changeLine(unsigned int lineId, Company &semprarrolar);
void removeLine(unsigned int posLine, Company &semprarrolar);

// variáveis globais
string nameCompany;
string inCondutores;
string inLinhas;
unsigned int horaInicio, horaFim;

int main()
{
	cout << "Nome da companhia: ";
	getline(cin, nameCompany);

	cout << endl;
	cout << "--- EMPRESA DE TRANSPORTES " + nameCompany + " ---\n" << endl;

	// ler os ficheiros e criar companhia
	Company semprarrolar = createCompany();

	// definir horario de funcionamento
	definirHorario();

	// chamar menu com companhia
	opcoesPrincipal(semprarrolar);

	return 0;
}

// definir horario de inicio e fim de serviço
void definirHorario()
{
	unsigned int horaDeInicio;
	cout << endl;
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
	cout << endl;
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

void opcoesPrincipal(Company &semprarrolar)
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
			opcoesGestaoLinhas(semprarrolar);
			break;
		case 2:
			opcoesGestaoCondutores(semprarrolar);
			break;
		case 3:
			opcoesPercursos(semprarrolar);
			break;
		case 4:
			opcoesVisualizarLinha(semprarrolar);
			break;
		case 5:
			semprarrolar.visualizaCondutores();
			break;
		default:
			cout << "Introduza uma opcao valida!\n";
		}
	}
}

char menuGestaoLinhas()
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

void opcoesGestaoLinhas(Company &semprarrolar)
{
	char choice;
	while (choice = menuGestaoLinhas())
	{
		switch (choice)
		{
		case 'A':
		{
			unsigned int id, freqBus;
			int posLine;
			do
			{
				cout << "ID do condutor a criar: ";
				cin >> id;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ID do condutor a criar: ";
					cin >> id;
				}

				posLine = semprarrolar.procuraIdVetorCondutores(id);

				if (posLine != -1) cout << "O ID de condutor introduzido ja existe!" << endl;

			} while (posLine != -1);

			// introducao da freq
			cout << "Frequencia: ";
			cin >> freqBus;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Frequencia: ";
				cin >> freqBus;
			}

			vector<string> busStopList;
			vector<int> timesList;

			int numParagem = 1;
			string paragem;
			cout << "(Escrever FIM para terminar)" << endl;
			cout << "Paragem" << numParagem << ": ";
			getline(cin, paragem);
			while (paragem != "FIM")
			{
				busStopList.push_back(paragem);
				numParagem++;
				cout << "Paragem" << numParagem << ": ";
				getline(cin, paragem);
			}

			if (busStopList.size() > 1) // se nParagens > 1
			{
				int nParagem = 1;
				int nIntervalosTempo = timesList.size() - 1;
				string intervaloTempo;

				cout << "(Escrever FIM para terminar)" << endl;
				while (nParagem <= nIntervalosTempo)
				{
					cout << "Tempo de viagem paragens " << nParagem << " e "
						<< nParagem + 1 << ": ";
					getline(cin, intervaloTempo);
					timesList.push_back(stoi(intervaloTempo));
					nParagem++;
				}
			}
			
			Line newLine(id,freqBus,busStopList,timesList);
			semprarrolar.addLine(newLine);
			break;
		}
		case 'B':
		{
			cout << endl;
			if (semprarrolar.getLinesVector().size() == 0)
			{
				cout << "Nao existem linhas a alterar!\n";
				return;
			}

			unsigned int lineId;
			int posLine = -1;
			do
			{
				cout << "ID da linha a alterar: ";
				cin >> lineId;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ID da linha a alterar: ";
					cin >> lineId;
				}

				posLine = semprarrolar.procuraIdVetorLinhas(lineId);

				if (posLine == -1)
					cout << "O ID da linha introduzido nao existe!" << endl;

			} while (posLine == -1);

			changeLine(lineId, semprarrolar);
			break;
		}
		case 'C':
		{
			if (semprarrolar.getLinesVector().size() == 0)
			{
				cout << "Nao existem linhas a remover!\n";
				return;
			}
			else
			{
				unsigned int lineId;
				int posLine;
				do
				{
					cout << "ID da linha a remover: ";
					cin >> lineId;

					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "ID da linha a remover: ";
						cin >> lineId;
					}

					posLine = semprarrolar.procuraIdVetorLinhas(lineId);

					if (posLine == -1) cout << "Introduza um ID de condutor valido!" << endl;

				} while (posLine == -1);

				removeDriver(posLine, semprarrolar);
			}
			break;
		}
		}
	}
}

char menuGestaoCondutores()
{
	cout << endl;
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

void opcoesGestaoCondutores(Company &semprarrolar)
{
	char choice;
	while (choice = menuGestaoCondutores())
	{
		switch (choice)
		{
		case 'A':
		{
			unsigned int id, maxHours, maxWeekWorkingTime, minRestTime;
			int posDriver;
			string driverName;
			vector<Shift> vShifts;
			do
			{
				cout << "ID do condutor a criar: ";
				cin >> id;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ID do condutor a criar: ";
					cin >> id;
				}

				posDriver = semprarrolar.procuraIdVetorCondutores(id);

				if (posDriver != -1)
					cout << "O ID de condutor introduzido ja existe!" << endl;

			} while (posDriver != -1);

			// ignorar newline para introduzir strings
			cin.ignore();

			// introducao do nome do condutor
			cout << "Nome do condutor: ";
			getline(cin, driverName);

			// introducao dos tempos dos turnos
			cout << "Numero de horas consecutivas do turno diario: ";
			cin >> maxHours;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Numero de horas consecutivas do turno diario: ";
				cin >> maxHours;
			}

			cout << "Numero maximo de horas por semana: ";
			cin >> maxWeekWorkingTime;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Numero maximo de horas por semana: ";
				cin >> maxWeekWorkingTime;
			}

			cout << "Numero minimo horas de descanso entre turnos: ";
			cin >> minRestTime;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Numero minimo horas de descanso entre turnos: ";
				cin >> minRestTime;
			}

			Driver newDriver(id, driverName, maxHours, maxWeekWorkingTime, minRestTime, vShifts);
			semprarrolar.addDriver(newDriver);
			break;
		}
		case 'B':
		{
			cout << endl;
			if (semprarrolar.getDriversVector().size() == 0)
			{
				cout << "Nao existem condutores a alterar!\n";
				return;
			}

			unsigned int driverId;
			int posDriver = -1;
			do
			{
				cout << "ID do condutor a alterar: ";
				cin >> driverId;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ID do condutor a alterar: ";
					cin >> driverId;
				}

				posDriver = semprarrolar.procuraIdVetorCondutores(driverId);

				if (posDriver == -1) cout << "O ID de condutor introduzido nao existe!" << endl;

			} while (posDriver == -1);

			changeDriver(driverId, semprarrolar);
			break;
		}
		case 'C':
		{
			if (semprarrolar.getDriversVector().size() == 0)
			{
				cout << "Nao existem condutores a remover!\n";
				return;
			}
			else
			{
				unsigned int driverId;
				int posDriver;
				do
				{
					cout << "ID do condutor a remover: ";
					cin >> driverId;

					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "ID: ";
						cin >> driverId;
					}

					posDriver = semprarrolar.procuraIdVetorCondutores(driverId);

					if (posDriver == -1)
						cout << "Introduza um ID de condutor valido!" << endl;

				} while (posDriver == -1);

				removeDriver(posDriver, semprarrolar);
			}
			break;
		}
		}
	}
}

char menuOpcoesVisualizarLinha()
{
	cout << endl;
	cout << "A. Visualizar informacao de linha\n"
		<< "B. Visualizar horario de linha\n"
		<< "# MENU ANTERIOR\n\n";

	char choice;
	cout << "--> opcao ";
	cin >> choice;

	while (choice != 'A' && choice != 'B' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
	}

	return choice;
}

void opcoesVisualizarLinha(Company semprarrolar)
{
	char choice;
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

char menuOpcoesPercursos()
{
	cout << endl;
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
	char choice;
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

// -------------- CONDUTORES ------------------
// altera condutor
void changeDriver(unsigned int driverId, Company &semprarrolar)
{
	int posDriver = semprarrolar.procuraIdVetorCondutores(driverId);

	if (posDriver == -1)
		cout << "Condutor inexistente" << endl;
	else
	{
		// char para escolha de opcoes
		char option;

		cout << "Alterar ID? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			unsigned int newId;
			cout << "Insira o novo ID: ";
			cin >> newId;
			semprarrolar.getDriversVector().at(posDriver).setId(newId);
		}

		cout << "Alterar nome? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			string newName;
			cout << "Insira o novo nome: ";
			cin >> newName;
			semprarrolar.getDriversVector().at(posDriver).setName(newName);
		}

		cout << "Alterar o numero de horas consecutivas de turno diario? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			unsigned int newMaxHours;
			cout << "Insira o novo numero de horas consecutivas de turno diario: ";
			cin >> newMaxHours;
			semprarrolar.getDriversVector().at(posDriver).setMaxHours(newMaxHours);
		}

		cout << "Alterar o numero maximo de horas de trabalho por semana? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			unsigned int newMaxWeekHours;
			cout << "Insira o novo numero maximo de horas de trabalho por semana: ";
			cin >> newMaxWeekHours;
			semprarrolar.getDriversVector().at(posDriver).setMaxWeekWorkingTime(newMaxWeekHours);
		}

		cout << "Alterar o numero minimo de horas de descanso entre turnos? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			unsigned int newMinRestTime;
			cout << "Insira o novo numero maximo de horas de trabalho por semana: ";
			cin >> newMinRestTime;
			semprarrolar.getDriversVector().at(posDriver).setMinRestTime(newMinRestTime);
		}
	}
}

// remover condutor
void removeDriver(int posDriver, Company &semprarrolar)
{
	semprarrolar.getDriversVector().erase(semprarrolar.getDriversVector().begin() + posDriver);
}

// ---------------- LINHAS --------------------
void changeLine(unsigned int lineId, Company &semprarrolar)
{
	int posLine = semprarrolar.procuraIdVetorLinhas(lineId);

	if (posLine == -1)
		cout << "Linha inexistente" << endl;
	else
	{
		// char para escolha de opcoes
		char option;

		cout << "Alterar ID? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			unsigned int newId;
			cout << "Insira o novo ID: ";
			cin >> newId;
			semprarrolar.getLinesVector().at(posLine).setId(newId);
		}

		cout << "Alterar frequencia? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			unsigned int newFreq;
			cout << "Insira a nova frequencia: ";
			cin >> newFreq;
			semprarrolar.getLinesVector().at(posLine).setFreqBus(newFreq);
		}

		// ignorar newline para introduzir strings
		cin.ignore();

		cout << "Alterar paragens? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 'y' || option == 'Y')
		{
			// introducao de paragens
			vector<string> newBusStopList;
			int numParagem = 1;
			string paragem;
			cout << "(Escrever FIM para terminar)" << endl;

			cout << "Paragem" << numParagem << ": ";
			getline(cin, paragem);
			while (paragem != "FIM")
			{
				newBusStopList.push_back(paragem);
				numParagem++;
				cout << "Paragem" << numParagem << ": ";
				getline(cin, paragem);
			}

			// introducao dos tempos
			vector<int> newTimesList;
			int nParagem = 1, nIntervalosTempo = newBusStopList.size() - 1;
			string intervaloTempo;
			if (newBusStopList.size() > 1) // se nParagens > 1
			{
				cout << "(Escrever FIM para terminar)" << endl;
				while (nParagem <= nIntervalosTempo)
				{
					cout << "Tempo de viagem paragens " << nParagem << " e "
						<< nParagem + 1 << ": ";
					getline(cin, intervaloTempo);
					newTimesList.push_back(stoi(intervaloTempo));
					nParagem++;
				}
			}
			semprarrolar.getLinesVector().at(posLine).setBusStopList(newBusStopList);
			semprarrolar.getLinesVector().at(posLine).setTimesList(newTimesList);
		}
	}
}

void removeLine(unsigned int posLine, Company &semprarrolar)
{
	semprarrolar.getLinesVector().erase(semprarrolar.getLinesVector().begin() + posLine);
}