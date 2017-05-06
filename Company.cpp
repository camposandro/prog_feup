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
void Company::addDriver()
{
	unsigned int id, maxHours, maxWeekWorkingTime, minRestTime;
	string name;
	vector<Shift> shifts;
	obterParametrosDriver(id, name, maxHours, maxWeekWorkingTime, minRestTime, shifts);

	Driver newDriver(id, name, maxHours, maxWeekWorkingTime, minRestTime, shifts);
	vectorDrivers.push_back(newDriver);

	driversBubblesort();
}

// altera condutor
void Company::changeDriver()
{
	
}

// remove condutor
void Company::removeDriver()
{
	if (vectorDrivers.size() == 0)
	{
		cout << "Nao existem condutores a remover!\n";
	}
	else
	{
		unsigned int posCondutorRemover = obterPosCondutorRemover();
		vectorDrivers.erase(vectorDrivers.begin() + posCondutorRemover);
		driversBubblesort();
	}
}

// cria linha
void Company::addLine()
{
	unsigned int id, freqBus;
	vector<string> busStopList;
	vector<int> timesList;
	obterParametrosLinha(id, freqBus, busStopList, timesList);

	Line newLine(id, freqBus, busStopList, timesList);
	vectorLines.push_back(newLine);

	linesBubblesort();
}

// altera linha
void Company::changeLine()
{

}

// remove linha
void Company::removeLine()
{
	if (vectorLines.size() == 0)
	{
		cout << "Nao existem linhas a remover!\n";
	}
	else
	{
		unsigned int posLinhaRemover = obterPosLinhaRemover();
		vectorLines.erase(vectorLines.begin() + posLinhaRemover);
		linesBubblesort();
	}
}

// pesquisa por paragem
void Company::pesquisaParagem()
{
	string nomeParagem;
	obterNomeParagem(nomeParagem);
	// vetor que contem os ids das linhas que contiverem a paragem
	vector<int> idLinhasParagem = procuraNomeVetorLinhas(nomeParagem);

	if (idLinhasParagem.size() == 0)
		cout << "Nao foi encontrada nenhuma paragem com o nome dado ...\n";
	else
	{
		cout << endl << "ID's das linhas que contem a paragem \"" << nomeParagem << "\": ";
		for (size_t k = 0; k < idLinhasParagem.size(); k++)
		{
			if (k == idLinhasParagem.size() - 1)
				cout << vectorLines.at(idLinhasParagem.at(k)).getId() << endl;
			else cout << vectorLines.at(idLinhasParagem.at(k)).getId() << ", ";
		}
	}
}

////////////////////////////////
// metodos get
///////////////////////////////
string Company::getName() const
{
  return name;
}

void Company::visualizaCondutores()
{
	if (vectorDrivers.size() == 0) cout << "Nao existem condutores!\n";

	cout << endl;
	for (int j = 0; j < vectorDrivers.size(); j++)
	{
		cout << "ID DO CONDUTOR: " << vectorDrivers.at(j).getId() << endl;
		cout << "NOME DO CONDUTOR: " << vectorDrivers.at(j).getName() << endl;
		cout << "MAX. HORAS TURNO: " << vectorDrivers.at(j).getShiftMaxDuration() << endl;
		cout << "MAX. HORAS SEMANA: " << vectorDrivers.at(j).getMaxWeekWorkingTime() << endl;
		cout << "MIN. HORAS DESCANSO: " << vectorDrivers.at(j).getMinRestTime() << endl;

		if (j < vectorDrivers.size() - 1) cout << endl;
	}
	cout << endl;
}

void Company::visualizaLinhas()
{
	if (vectorLines.size() == 0) cout << "Nao existem linhas!\n";

	for (int i = 0; i < vectorLines.size(); i++)
	{
		cout << "LINHA " << vectorLines.at(i).getId() << endl;

		cout << "PARAGENS: ";
		vector<string> vetorParagens = vectorLines.at(i).getBusStops();
			for (int j = 0; j < vetorParagens.size(); j++)
			{
				if (j < vetorParagens.size() - 1)
					cout << vetorParagens.at(j) << " , ";
				else
					cout << vetorParagens.at(j) << endl;
			}

		cout << "TEMPO ENTRE PARAGENS (min): ";
		vector<int> vetorTempos = vectorLines.at(i).getTimings();
			for (int k = 0; k < vetorTempos.size(); k++)
			{
				if (k < vetorParagens.size() - 2)
					cout << vetorTempos.at(k) << " , ";
				else
					cout << vetorTempos.at(k) << endl;
			}

		if (i < vectorLines.size() - 1) cout << endl;
	}
	cout << endl;
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

void Company::obterParametrosLinha(unsigned int& id, unsigned int &freqBus, vector<string>& busStopList, vector<int>& timesList)
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

	cout << "Frequencia dos autocarros: ";
	cin >> freqBus;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Frequencia dos autocarros: ";
		cin >> freqBus;
	}

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

void Company::obterNomeParagem(string &nomeParagem)
{
	cin.ignore();
	cout << "Introduza o nome da paragem a pesquisar: ";
	getline(cin, nomeParagem);
}

void Company::serviceDistribution()
{
}

// funções auxiliares
void Company::driversBubblesort()
{
	// vao ser feitas n comparacoes
	for (int i = 0; i < vectorDrivers.size(); i++)
	{
		// comparar elem com o elem seg.
		for (size_t j = 0; j < vectorDrivers.size() - 1; j++)
		{
			// fazer swap se n+1 < n
			if (vectorDrivers[j + 1].getId() < vectorDrivers[j].getId())
			{
				Driver t = vectorDrivers[j + 1];
				vectorDrivers[j + 1] = vectorDrivers[j];
				vectorDrivers[j] = t;
			}
		}
	}
}

void Company::linesBubblesort()
{
	// vao ser feitas n comparacoes
	for (int i = 0; i < vectorLines.size(); i++)
	{
		// comparar elem com o elem seg.
		for (size_t j = 0; j < vectorLines.size() - 1; j++)
		{
			// fazer swap se n+1 < n
			if (vectorLines[j + 1].getId() < vectorLines[j].getId())
			{
				Line t = vectorLines[j + 1];
				vectorLines[j + 1] = vectorLines[j];
				vectorLines[j] = t;
			}
		}
	}
}

unsigned int Company::obterPosCondutorAlterar()
{
	unsigned int idCondutorAlterar;
	int posCondutorAlterar;
	do
	{
		cout << "ID do condutor a alterar: ";
		cin >> idCondutorAlterar;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ID: ";
			cin >> idCondutorAlterar;
		}

		posCondutorAlterar = procuraIdVetorCondutores(idCondutorAlterar);

		if (posCondutorAlterar == -1)
			cout << "Introduza um ID de condutor valido!" << endl;

	} while (posCondutorAlterar == -1);

	return posCondutorAlterar;
}

unsigned int Company::obterPosCondutorRemover()
{
	unsigned int idCondutorRemover;
	int posCondutorRemover;
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

	} while (posCondutorRemover == -1);

	return posCondutorRemover;
}

unsigned int Company::obterPosLinhaAlterar()
{
	unsigned int idLinhaAlterar;
	int posLinhaAlterar;
	do
	{
		cout << "ID da linha a remover: ";
		cin >> idLinhaAlterar;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ID da linha a remover: ";
			cin >> idLinhaAlterar;
		}

		posLinhaAlterar = procuraIdVetorLinhas(idLinhaAlterar);

		if (posLinhaAlterar == -1)
			cout << "Introduza um ID de linha valido!" << endl;

	} while (posLinhaAlterar == -1);

	return  posLinhaAlterar;
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

vector<int> Company::procuraNomeVetorLinhas(string nomeParagem)
{
	// coloca o nomeParagem a minuscula
	string nomeParagemMinuscula = nomeParagem;
	for (size_t k = 0; k <= nomeParagem.length(); k++)
		nomeParagemMinuscula[k] = tolower(nomeParagem[k]);

	// vetor que contem as posicoes das linhas que contiverem a paragem
	vector<int> posLinhasParagem;

	for (size_t i = 0; i < vectorLines.size(); i++)
	{
		vector<string> vetorParagens = vectorLines.at(i).getBusStops();
		for (size_t j = 0; j < vetorParagens.size(); j++)
		{
			// colocar cada elemento procurado no vetor em minuscula
			string paragemVetor = vetorParagens.at(j);
			for (int p = 0; p < paragemVetor.length(); p++)
				paragemVetor[p] = tolower(paragemVetor[p]);

			if (paragemVetor == nomeParagemMinuscula)
			{
				// coloca o id no vetor
				posLinhasParagem.push_back(i);
				break;
			}
		}
	}

	return posLinhasParagem;
}