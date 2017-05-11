#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>

#include "Company.h"

// construtor da classe
Company::Company(string name, string fileDrivers, string fileLines)
{
	this->name = name;
	vectorDrivers = obterCondutoresFicheiro(fileDrivers);
	vectorLines = obterLinhasFicheiro(fileLines);
}

// cria linha
void Company::addLine(Line newLine)
{
	vectorLines.push_back(newLine);
	linesBubblesort();
}

// modifica linha
void Company::changeLine(unsigned int lineId)
{
	int posLine = procuraIdVetorLinhas(lineId);

	if (posLine == -1)
		cout << "Linha inexistente" << endl;
	else
	{
		// char para escolha de opcoes
		char option;

		cout << "Alterar ID? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			unsigned int newId;
			int newPosLine;
			do
			{
				cout << "Insira o novo ID: ";
				cin >> newId;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Insira o novo ID: ";
					cin >> newId;
				}

				newPosLine = procuraIdVetorLinhas(newId);

				if (newPosLine != -1) cout << "O ID de linha introduzido ja existe!" << endl;

			} while (newPosLine != -1);

			vectorLines.at(posLine).setId(newId);
		}

		cout << "Alterar frequencia? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			unsigned int newFreq;
			cout << "Insira a nova frequencia: ";
			cin >> newFreq;
			vectorLines.at(posLine).setFreqBus(newFreq);
		}

		cout << "Alterar paragens? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			// ignorar newline para introduzir strings
			cin.ignore();

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
			vectorLines.at(posLine).setBusStopList(newBusStopList);
			vectorLines.at(posLine).setTimesList(newTimesList);
		}
		else if (option == 'N' || option == 'n')
		{
			cout << "Alterar tempos de viagem? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			if (option == 's' || option == 'S')
			{
				// ignorar newline para introduzir tempos
				cin.ignore();

				// introducao dos tempos
				vector<int> newTimesList;
				int nParagem = 1, nIntervalosTempo = vectorLines.at(posLine).getBusStops().size() - 1;
				string intervaloTempo;

				if (nIntervalosTempo > 1) // se nParagens > 1
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
				vectorLines.at(posLine).setTimesList(newTimesList);
			}
		}
		linesBubblesort();
	}
}

// remove linha
void Company::removeLine(unsigned int posLine)
{
	vectorLines.erase(vectorLines.begin() + posLine);
	linesBubblesort();
}

// cria condutor
void Company::addDriver(Driver newDriver)
{
	vectorDrivers.push_back(newDriver);
	driversBubblesort();
}

// modifica condutor
void Company::changeDriver(unsigned int driverId)
{
	int posDriver = procuraIdVetorCondutores(driverId);

	if (posDriver == -1)
		cout << "Condutor inexistente" << endl;
	else
	{
		// char para escolha de opcoes
		char option;

		cout << "Alterar ID? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			unsigned int newId;
			cout << "Insira o novo ID: ";
			cin >> newId;
			vectorDrivers.at(posDriver).setId(newId);
		}

		cout << "Alterar nome? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			string newName;
			cout << "Insira o novo nome: ";
			cin >> newName;
			vectorDrivers.at(posDriver).setName(newName);
		}

		cout << "Alterar o numero de horas consecutivas de turno diario? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			unsigned int newMaxHours;
			cout << "Insira o novo numero de horas consecutivas de turno diario: ";
			cin >> newMaxHours;
			vectorDrivers.at(posDriver).setMaxHours(newMaxHours);
		}

		cout << "Alterar o numero maximo de horas de trabalho por semana? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			unsigned int newMaxWeekHours;
			cout << "Insira o novo numero maximo de horas de trabalho por semana: ";
			cin >> newMaxWeekHours;
			vectorDrivers.at(posDriver).setMaxWeekWorkingTime(newMaxWeekHours);
		}

		cout << "Alterar o numero minimo de horas de descanso entre turnos? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		if (option == 's' || option == 'S')
		{
			unsigned int newMinRestTime;
			cout << "Insira o novo numero maximo de horas de trabalho por semana: ";
			cin >> newMinRestTime;
			vectorDrivers.at(posDriver).setMinRestTime(newMinRestTime);
		}
		driversBubblesort();
	}
}

// remove condutor
void Company::removeDriver(int posDriver)
{
	vectorDrivers.erase(vectorDrivers.begin() + posDriver);
	driversBubblesort();
}

// pesquisa por paragem
void Company::pesquisaParagem(string nomeParagem, vector<int> idLinhasComParagem)
{
	cout << endl << "ID's das linhas que contem a paragem \"" << nomeParagem << "\": ";
	for (size_t k = 0; k < idLinhasComParagem.size(); k++)
	{
		if (k == idLinhasComParagem.size() - 1)
			cout << vectorLines.at(idLinhasComParagem.at(k)).getId() << endl;
		else cout << vectorLines.at(idLinhasComParagem.at(k)).getId() << ", ";
	}
}

// percurso entre paragens
void Company::percursoEntreParagens(Line linhaEmComum, unsigned int posParagem1, unsigned int posParagem2)
{
	cout << "PERCURSO " << "NA LINHA " << linhaEmComum.getId() << ":" << endl;
	// caso se introduza no sentido original
	if (posParagem2 < posParagem1)
	{
		for (size_t k = posParagem1; k > posParagem2; k--)
		{
			// imprime os trajetos entre as paragens entre "-->"
			cout << left << setw(linhaEmComum.getBusStops().at(k).length() + 1) << linhaEmComum.getBusStops().at(k) << "-->"
				<< right << setw(linhaEmComum.getBusStops().at(k - 1).length() + 1) << linhaEmComum.getBusStops().at(k - 1);
			// imprime os tempos de cada trajeto 
			cout << " " << linhaEmComum.getTimings().at(k - 1) << "min" << endl;
		}
	}
	// caso se introduza no sentido inverso
	else if (posParagem2 > posParagem1)
	{
		for (size_t k = posParagem1; k < posParagem2; k++)
		{
			// imprime os trajetos entre as paragens entre "-->"
			cout << left << setw(linhaEmComum.getBusStops().at(k).length() + 1) << linhaEmComum.getBusStops().at(k) << "-->"
				<< right << setw(linhaEmComum.getBusStops().at(k + 1).length() + 1) << linhaEmComum.getBusStops().at(k + 1);
			// imprime os tempos de cada trajeto 
			cout << " " << linhaEmComum.getTimings().at(k) << "min" << endl;
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

vector<Driver> Company::getDriversVector() const
{
	return vectorDrivers;
}

vector<Line> Company::getLinesVector() const
{
	return vectorLines;
}

void Company::visualizaCondutores() const
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
}

void Company::visualizaLinhas() const
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
}

//////////////////////////////
// metodos set
/////////////////////////////
void Company::setName(string name)
{
	this->name = name;
}

vector<Line> Company::obterLinhasFicheiro(string fileLines)
{
	// EXTRACT EACH LINE'S INFO
	string LinhaI;
	ifstream fLinhas(fileLines);
	while (getline(fLinhas, LinhaI))
	{
		Line newLine(LinhaI);

		// acrescenta linha ao vetor das linhas
		vectorLines.push_back(newLine);
	}
	fLinhas.close();

	return vectorLines;
}

vector<Driver> Company::obterCondutoresFicheiro(string fileDrivers)
{
	// EXTRACT EACH DRIVER'S INFO
	string CondutorI;
	ifstream fCondutores(fileDrivers);
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

unsigned int Company::procuraIdVetorCondutores(unsigned int idCondutor)
{
	for (size_t i = 0; i < vectorDrivers.size(); i++)
	{
		if (vectorDrivers.at(i).getId() == idCondutor) return i;
	}
	return -1;
}

unsigned int Company::procuraIdVetorLinhas(unsigned int idLinha)
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