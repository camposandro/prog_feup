#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
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
void opcoesPrincipal(Company &semprarrolar);
char menuGestaoLinhas();
void opcoesGestaoLinhas(Company &semprarrolar);
char menuGestaoCondutores();
void opcoesGestaoCondutores(Company &semprarrolar);
char menuOpcoesVisualizarLinha();
void opcoesVisualizarLinha(Company semprarrolar);
char menuOpcoesPercursos();
void opcoesPercursos(Company semprarrolar);
void opcoesAutocarros(Company semprarrolar);
void opcoesEscalonamento(Company &semprarrolar);

// variáveis globais
string nameCompany;
string inCondutores;
string inLinhas;
unsigned int horaInicio, horaFim;

int main()
{
	cout << "NOME DA COMPANHIA DE TRANSPORTES: ";
	getline(cin, nameCompany);

	system("cls");

	cout << "--- EMPRESA DE TRANSPORTES " + nameCompany + " ---\n" << endl;

	// ler os ficheiros e criar companhia
	Company semprarrolar = createCompany();

	// definir horario de funcionamento
	definirHorario();

	// criacao dos autocarros para a companhia
	semprarrolar.createBuses(horaInicio, horaFim);

	// chamar menu com companhia
	opcoesPrincipal(semprarrolar);

	// save changes
	semprarrolar.atualizaFicheiros(inCondutores, inLinhas);
	cout << endl << "Programa a encerrar ..." << endl << endl;

	return 0;
}

// definir horario de inicio e fim de serviço
void definirHorario()
{
	unsigned int horaDeInicio;
	cout << endl;
	cout << "Hora de inicio de servico: ";
	cin >> horaDeInicio;

	while (cin.fail() || horaDeInicio > 23 || horaDeInicio < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma hora valida!\n";
		cout << "Hora de inicio de servico: ";
		cin >> horaDeInicio;
	}
	horaInicio = horaDeInicio;

	unsigned int horaDeFim;
	cout << "Hora de fim de servico: ";
	cin >> horaDeFim;

	while (cin.fail() || horaDeFim > 23 || horaDeFim < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma hora valida!\n";
		cout << "Hora de fim de servico: ";
		cin >> horaDeFim;
	}
	horaFim = horaDeFim;

	intervaloTempoServico(horaInicio, horaFim);
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

// ---- menus -----
unsigned int menuPrincipal()
{
	cout << endl;
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n";
	cout << "1. Gestao de linhas\n"
		<< "2. Gestao de condutores\n"
		<< "3. Visualizar percursos\n"
		<< "4. Visualizar linhas\n"
		<< "5. Visualizar condutores\n"
		<< "6. Visualizar informacoes de autocarros\n"
		<< "7. Escalonamento de condutores\n"
		<< "0. Sair\n";
	cout << endl;

	unsigned int choice;
	cout << "--> opcao ";
	cin >> choice;

	while (choice > 7 || choice < 0)
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
			return;
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
		case 6:
			opcoesAutocarros(semprarrolar);
			break;
		case 7:
			opcoesEscalonamento(semprarrolar);
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
	choice = tolower(choice);
	while (choice != 'a' && choice != 'b' && choice != 'c' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
		choice = tolower(choice);
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
		case 'a':
		{
			unsigned int id, freqBus;
			int posLine;
			do
			{
				cout << "ID da linha a criar: ";
				cin >> id;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ID da linha a criar: ";
					cin >> id;
				}

				posLine = semprarrolar.procuraIdVetorLinhas(id);

				if (posLine != -1) cout << "O ID de linha introduzido ja existe!" << endl;

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

			cin.ignore();

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

			int nParagem = 1;
			int nIntervalosTempo = busStopList.size() - 1;
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

			Line newLine(id, freqBus, busStopList, timesList);
			semprarrolar.addLine(newLine);
			break;
		}
		case 'b':
		{
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

			semprarrolar.changeLine(lineId);
			break;
		}
		case 'c':
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

					if (posLine == -1) cout << "Introduza um ID de linha valido!" << endl;

				} while (posLine == -1);

				semprarrolar.removeLine(posLine);
			}
			break;
		}
		case '#':
			return;
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
	choice = tolower(choice);
	while (choice != 'a' && choice != 'b' && choice != 'c' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
		choice = tolower(choice);
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
		case 'a':
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
		case 'b':
		{
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

			semprarrolar.changeDriver(driverId);
			break;
		}
		case 'c':
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

				semprarrolar.removeDriver(posDriver);
			}
			break;
		}
		case '#':
			return;
		}
	}
}

char menuOpcoesVisualizarLinha()
{
	cout << endl;
	cout << "A. Visualizar informacao de linhas\n"
		<< "B. Visualizar horario de linha\n"
		<< "# MENU ANTERIOR\n\n";

	char choice;
	cout << "--> opcao ";
	cin >> choice;
	choice = tolower(choice);
	while (choice != 'a' && choice != 'b' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
		choice = tolower(choice);
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
		case 'a':
			semprarrolar.visualizaLinhas();
			break;
		case 'b':
		{
			unsigned int lineId;
			int posLine;
			do
			{
				cout << "ID da linha a mostrar: ";
				cin >> lineId;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ID da linha a mostrar: ";
					cin >> lineId;
				}

				posLine = semprarrolar.procuraIdVetorLinhas(lineId);

				if (posLine == -1)
					cout << "O ID de linha introduzido nao existe!" << endl;

			} while (posLine == -1);

			semprarrolar.horarioLinha(lineId, posLine, horaInicio, horaFim);
			break;
		}
		case '#':
			return;
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
	choice = tolower(choice);
	while (choice != 'a' && choice != 'b' && choice != 'c' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
		choice = tolower(choice);
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
		case 'a':
		{
			cin.ignore();
			string nomeParagem;
			cout << "Introduza o nome da paragem a pesquisar: ";
			getline(cin, nomeParagem);

			// vetor que contem os ids das linhas que contiverem a paragem
			vector<int> idLinhasComParagem = semprarrolar.procuraNomeVetorLinhas(nomeParagem);

			if (idLinhasComParagem.size() == 0)
				cout << "Nao foi encontrada nenhuma paragem com o nome dado ...\n";
			else
				semprarrolar.pesquisaParagem(nomeParagem, idLinhasComParagem);

			break;
		}
		case 'b':
		{
			cin.ignore(); // para limpar o buffer

			string nomeParagem1;
			cout << "Introduza o nome da paragem de partida: ";
			getline(cin, nomeParagem1);
			vector<int> linhasParagem1 = semprarrolar.procuraNomeVetorLinhas(nomeParagem1);
			while (linhasParagem1.size() == 0)
			{
				cout << "A paragem " << nomeParagem1 << " nao existe." << endl;
				cout << "Introduza o nome da paragem de partida: ";
				getline(cin, nomeParagem1);
				linhasParagem1 = semprarrolar.procuraNomeVetorLinhas(nomeParagem1);
			}

			string nomeParagem2;
			cout << "Introduza o nome da paragem de destino: ";
			getline(cin, nomeParagem2);
			vector<int> linhasParagem2 = semprarrolar.procuraNomeVetorLinhas(nomeParagem2);
			while (linhasParagem2.size() == 0)
			{
				cout << "A paragem " << nomeParagem2 << " nao existe." << endl;
				cout << "Introduza o nome da paragem de destino: ";
				getline(cin, nomeParagem2);
				linhasParagem2 = semprarrolar.procuraNomeVetorLinhas(nomeParagem2);
			}

			// verificar se existem linhas em comum e caso existam, guardar num vetor linhasComum
			vector<int> linhasComum;
			for (size_t i = 0; i < linhasParagem1.size(); i++)
			{
				for (size_t j = 0; j < linhasParagem2.size(); j++)
				{
					if (linhasParagem1.at(i) == linhasParagem2.at(j))
						linhasComum.push_back(linhasParagem1.at(i));
				}
			}

			if (linhasComum.size() == 0) // nao existem linhas constituidas por ambas as paragens
			{
				cout << "Nao existem linhas constituidas por ambas as paragens!" << endl;
			}
			else
			{
				// coloca o nomeParagem1 a minuscula
				string nomeParagem1Minuscula = nomeParagem1;
				for (size_t k = 0; k <= nomeParagem1.length(); k++)
					nomeParagem1Minuscula[k] = tolower(nomeParagem1[k]);

				// coloca o nomeParagem2 a minuscula
				string nomeParagem2Minuscula = nomeParagem2;
				for (size_t k = 0; k <= nomeParagem2.length(); k++)
					nomeParagem2Minuscula[k] = tolower(nomeParagem2[k]);

				// percorre vetor de posicoes das linhas que contêm ambas as paragens
				for (size_t i = 0; i < linhasComum.size(); i++)
				{
					Line linhaEmComum = semprarrolar.getLinesVector().at(linhasComum.at(i));

					// encontrar posicoes respetivas na linha
					int posParagem1, posParagem2;
					for (size_t j = 0; j < linhaEmComum.getBusStops().size(); j++)
					{
						// colocar cada elemento procurado no vetor em minuscula
						string paragemVetor = linhaEmComum.getBusStops().at(j);
						for (int p = 0; p < paragemVetor.length(); p++)
							paragemVetor[p] = tolower(linhaEmComum.getBusStops().at(j).at(p));

						if (paragemVetor == nomeParagem1Minuscula)
							posParagem1 = j;
						if (paragemVetor == nomeParagem2Minuscula)
							posParagem2 = j;
					}

					cout << endl;
					if (posParagem1 == posParagem2)
						cout << "Introduza diferentes paragens!\n";
					else
						semprarrolar.percursoEntreParagens(linhaEmComum, posParagem1, posParagem2);
				}
			}
			break;
		}
		case 'c':
		{
			cin.ignore();
			string nomeParagem;
			vector<int> linhasComAParagem;
			do
			{
				cout << "Nome da paragem a mostrar: ";
				getline(cin, nomeParagem);

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Nome da paragem a mostrar: ";
					getline(cin, nomeParagem);
				}

				// vetor que contem as posicoes das linhas que contiverem a paragem
				linhasComAParagem = semprarrolar.procuraNomeVetorLinhas(nomeParagem);

				if (linhasComAParagem.size() == 0)
					cout << "Nao foi encontrada nenhuma paragem com o nome dado ...\n";

			} while (linhasComAParagem.size() == 0);

			semprarrolar.horarioParagem(nomeParagem, linhasComAParagem, horaInicio, horaFim);
			break;
		}
		case '#':
			return;
		}
	}
}

char menuOpcoesAutocarros()
{
	cout << endl;
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n" <<
			 "A. Visualizar informacao de autocarro\n" <<
			 "# MENU ANTERIOR\n\n";

	char choice;
	cout << "--> opcao ";
	cin >> choice;
	choice = tolower(choice);
	while (choice != 'a' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
		choice = tolower(choice);
	}

	return choice;
}

void opcoesAutocarros(Company semprarrolar)
{
	char choice;
	while (choice = menuOpcoesAutocarros())
	{
		switch (choice)
		{
		case 'a':
		{
			unsigned int lineId, busId;
			int posLine = -1;
			do
			{
				cout << "Insira o ID da linha do autocarro: ";
				cin >> lineId;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Insira o ID da linha do autocarro: ";
					cin >> lineId;
				}

				posLine = semprarrolar.procuraIdVetorLinhas(lineId);

				if (posLine == -1)
					cout << "O ID da linha introduzido nao existe!" << endl;

			} while (posLine == -1);

			unsigned int maxBusId = semprarrolar.numBusesNeededLine(posLine);

			cout << "Insira o ID do autocarro: ";
			cin >> busId;
			while (cin.fail() || busId > maxBusId || busId < 1)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "O ID de autocarro introduzido e invalido!\n";
				cout << "Insira o ID do autocarro: ";
				cin >> busId;
			}

			semprarrolar.printBusInfo(lineId, busId);
		}
		case '#':
			return;
		}
	}
}

char menuEscalonamento()
{
	cout << endl;
	cout << "SELECIONE UMA DAS OPCOES SEGUINTES:\n" <<
			 "A. Atribuir turno a condutor\n" <<
			 "B. Visualizar trabalho de condutor\n" <<
			 "C. Visualizar periodos de autocarro sem trabalho atribuido\n" <<
			 "D. Visualizar condutores sem servico completo atribuido\n" <<
			 "# MENU ANTERIOR\n\n";

	char choice;
	cout << "--> opcao ";
	cin >> choice;
	choice = tolower(choice);
	while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd' && choice != '#')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "--> opcao ";
		cin >> choice;
		choice = tolower(choice);
	}

	return choice;
}

void opcoesEscalonamento(Company &semprarrolar)
{
	char choice;
	while (choice = menuEscalonamento())
	{
		switch (choice)
		{
		case 'a':
		
		case 'b':

		case 'c':

		case 'd':

		case '#':
			return;
		}
	}
}