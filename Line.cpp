#include <fstream>
#include <sstream>
#include <conio.h>

#include "Company.h"
#include "Line.h"
#include "Driver.h"

// construtor da classe
Line::Line(unsigned int id, unsigned int freqBus, vector<string> busStopList, vector<int> timesList)
{
	this->id = id;
	this->freqBus = freqBus;
	this->busStopList = busStopList;
	this->timesList = timesList;
}

Line::Line(string textLine)
{
	istringstream infoLinha(textLine);
	string paragens;
	string tempos;

	infoLinha >> id;
	infoLinha.ignore(1000, ';');
	infoLinha >> freqBus;
	infoLinha.ignore(1000, ';');
	infoLinha.ignore();
	getline(infoLinha, paragens, ';');
	infoLinha.ignore();
	getline(infoLinha, tempos);

	// ---- SEGUNDA STRINGSTREAM -----

	// SEPARAR PARAGENS
	istringstream infoParagens(paragens);
	string paragem1;

	while (getline(infoParagens, paragem1, ','))
	{
		busStopList.push_back(paragem1);
		infoParagens.ignore();
	}

	// SEPARAR TEMPOS
	istringstream infoTempos(tempos);
	string tempo1;

	while (getline(infoTempos, tempo1, ','))
	{
		timesList.push_back(stoi(tempo1));
		infoTempos.ignore();
	}
}

////////////////
// set methods
////////////////
void Line::setId(unsigned int id)
{
	this->id = id;
}

void Line::setFreqBus(unsigned int freqBus)
{
	this->freqBus = freqBus;
}

void Line::setBusStopList(vector<string> busStopList)
{
	this->busStopList = busStopList;
}

void Line::setTimesList(vector<int> timesList)
{
	this->timesList = timesList;
}

////////////////
// get methods
////////////////
unsigned int Line::getId() const
{
  return id;
}

unsigned int Line::getFreqBus() const
{
	return freqBus;
}

vector<string> Line::getBusStops() const
{
  return busStopList;
}

vector<int> Line::getTimings() const
{
  return timesList;
}

// other methods
vector<string> Line::obterParagens(vector<string> busStopList)
{
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

	return busStopList;
}

vector<int> Line::obterTempos(vector<int> timesList)
{
	if (this->getBusStops().size() > 1) // se nParagens > 1
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

	return timesList;
}