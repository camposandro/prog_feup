#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include "Company.h"

void menu();

// construtor da classe
Company::Company(string name, string fileDrivers, string fileLines)
{
	this->name = name;
	vectorDrivers = obterCondutores(fileDrivers);
	vectorLines = obterLinhas(fileLines);
}

// cria condutor
void Company::createDriver()
{
	unsigned int id, maxHours, maxWeekWorkingTime, minRestTime;
	string name;
	vector<Shift> shifts;
	obterParametrosDriver(id, name, maxHours, maxWeekWorkingTime, minRestTime, shifts);

	Driver newDriver(id, name, maxHours, maxWeekWorkingTime, minRestTime, shifts);
	vectorDrivers.push_back(newDriver);
}

// remove condutor
void Company::removeDriver()
{
	if (vectorDrivers.size() == 0)
	{
		cout << "Nao existem condutores a remover!\n";
		menu();
	}
	else
	{
		unsigned int posCondutorRemover = obterPosCondutorRemover();
		vectorDrivers.erase(vectorDrivers.begin() + posCondutorRemover);
	}

	menu();
}

// cria linha
void Company::createLine()
{
	unsigned int id;
	vector<string> busStopList;
	vector<int> timesList;
	obterParametrosLinha(id, busStopList, timesList);

	Line newLine(id, busStopList, timesList);
	vectorLines.push_back(newLine);
}

// remove linha
void Company::removeLine()
{
	if (vectorLines.size() == 0)
	{
		cout << "Nao existem linhas a remover!\n";
		menu();
	}
	else
	{
		unsigned int posLinhaRemover = obterPosLinhaRemover();
		vectorLines.erase(vectorLines.begin() + posLinhaRemover);
	}
	
	menu();
}

////////////////////////////////
// metodos get
///////////////////////////////
string Company::getName() const
{
  return name;
}

//////////////////////////////
// metodos set
/////////////////////////////
void Company::setName(string name)
{
	this->name = name;
}

vector<Line> Company::obterLinhas(string fileLines)
{
	// EXTRACT EACH LINE'S INFO
	string LinhaI;
	ifstream fLinhas(fileLines + ".txt");
	while (getline(fLinhas, LinhaI))
	{
		Line newLine(LinhaI);

		// acrescenta linha ao vetor das linhas
		vectorLines.push_back(newLine);
	}
	fLinhas.close();

	return vectorLines;
}

vector<Driver> Company::obterCondutores(string fileDrivers)
{
	// EXTRACT EACH DRIVER'S INFO
	string CondutorI;
	ifstream fCondutores(fileDrivers + ".txt");
	while (getline(fCondutores, CondutorI))
	{
		Driver newDriver(CondutorI);

		// acrescenta condutor ao vetor de condutores
		vectorDrivers.push_back(CondutorI);
	}
	fCondutores.close();

	return vectorDrivers;
}

////////////////////////////
// outros metodos
///////////////////////////
void Company::obterParametrosDriver(unsigned int &id, string &name, unsigned int &maxHours, unsigned int &maxWeekWorkingTime, unsigned int &minRestTime, vector<Shift> &shifts)
{
	unsigned int posCondutorCriar;
	do
	{
		cout << "ID: ";
		cin >> id;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ID: ";
			cin >> id;
		}

		posCondutorCriar = procuraIdVetorCondutores(id);

		if (posCondutorCriar != -1)
			cout << "O ID de condutor introduzido ja existe!" << endl;

	} while (posCondutorCriar != -1);

	// ignorar newline para introduzir strings
	cin.ignore();

	// introducao do nome do condutor
	cout << "Nome: ";
	getline(cin, name);

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
}

void Company::obterParametrosLinha(unsigned int & id, vector<string>& busStopList, vector<int>& timesList)
{
	// atribuicao de ID e da freq dos bus
	int posLinhaCriar;
	do
	{
		cout << "ID: ";
		cin >> id;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ID: ";
			cin >> id;
		}

		posLinhaCriar = procuraIdVetorLinhas(id);

		if (posLinhaCriar != -1)
			cout << "O ID de linha introduzido ja existe!" << endl;

	} while (posLinhaCriar != -1);

	// ignorar newline para introduzir strings
	cin.ignore();

	// introducao de paragens
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

	// introducao dos tempos
	if (busStopList.size() > 1) // se nParagens > 1
	{
		int nParagem = 1, nIntervalosTempo = busStopList.size() - 1;
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
}

void Company::serviceDistribution()
{
}

// funções auxiliares
unsigned int Company::obterPosCondutorRemover()
{
	int idCondutorRemover, posCondutorRemover;
	do
	{
		cout << "ID do condutor a remover: ";
		cin >> idCondutorRemover;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ID: ";
			cin >> idCondutorRemover;
		}

		posCondutorRemover = procuraIdVetorCondutores(idCondutorRemover);

		if (posCondutorRemover == -1)
			cout << "Introduza um ID de condutor valido!" << endl;
		else
			vectorDrivers.erase(vectorDrivers.begin() + posCondutorRemover);

	} while (posCondutorRemover == -1);

	return posCondutorRemover;
}

unsigned int Company::obterPosLinhaRemover()
{
	int idLinhaRemover, posLinhaRemover;
	do
	{
		cout << "ID da linha a remover: ";
		cin >> idLinhaRemover;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ID da linha a remover: ";
			cin >> idLinhaRemover;
		}

		posLinhaRemover = procuraIdVetorLinhas(idLinhaRemover);

		if (posLinhaRemover == -1)
			cout << "Introduza um ID de linha valido!" << endl;

	} while (posLinhaRemover == -1);

	return posLinhaRemover;
}

unsigned int Company::procuraIdVetorCondutores(unsigned int idCondutor)
{
	for (size_t i = 0; i < vectorDrivers.size(); i++)
	{
		if (vectorDrivers.at(i).getId() == idCondutor) return i;
	}
	return -1;
}

unsigned int Company::procuraIdVetorLinhas(int idLinha)
{
	for (size_t i = 0; i < vectorLines.size(); i++)
	{
		if (vectorLines.at(i).getId() == idLinha) return i;
	}
	return -1;
}