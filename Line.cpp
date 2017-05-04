#include <fstream>
#include <sstream>
#include <conio.h>

#include "Company.h"
#include "Line.h"

// construtor da classe
Line::Line(unsigned int id, vector<string> busStopList, vector<int> timesList)
{
	this->id = id;
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

////////////////
// get methods
////////////////
unsigned int Line::getId() const
{
  return id;
}

vector<string> Line::getBusStops() const
{
  return busStopList;
}

vector<int> Line::getTimings() const
{
  return timesList;
}
