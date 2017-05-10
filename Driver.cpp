#include <fstream>
#include <sstream>
#include <conio.h>

#include "Driver.h"

// construtores da classe
Driver::Driver(unsigned int id, string name, unsigned int maxHours, unsigned int maxWeekWorkingTime, unsigned int minRestTime, vector<Shift> shifts)
{
	this->id = id;
	this->name = name;
	this->maxHours = maxHours;
	this->maxWeekWorkingTime = maxWeekWorkingTime;
	this->minRestTime = minRestTime;
	this->shifts = shifts;
}

Driver::Driver(string textLine)
{
	istringstream infoCondutor(textLine);

	infoCondutor >> this->id;
	infoCondutor.ignore(1000, ';');
	infoCondutor.ignore();
	getline(infoCondutor, name, ';');
	// retirar ultimo espaco do nome
	name = name.substr(0, name.length() - 1);
	// ----------------------------
	infoCondutor >> this->maxHours;
	infoCondutor.ignore(1000, ';');
	infoCondutor >> this->maxWeekWorkingTime;
	infoCondutor.ignore(1000, ';');
	infoCondutor >> this->minRestTime;
}
// ------------------------

//////////////
// set methods
//////////////
void Driver::setId(unsigned int id)
{
	this->id = id;
}

void Driver::setName(string name)
{
	this->name = name;
}

void Driver::setMaxHours(unsigned int maxHours)
{
	this->maxHours = maxHours;
}

void Driver::setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime)
{
	this->maxWeekWorkingTime = maxWeekWorkingTime;
}

void Driver::setMinRestTime(unsigned int minRestTime)
{
	this->minRestTime = minRestTime;
}

//////////////
// get methods
//////////////
unsigned int Driver::getId() const
{
  return id;
}

string Driver::getName() const
{
  return name;
}

unsigned int Driver::getShiftMaxDuration() const
{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const
{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const
{
  return minRestTime;
}

vector<Shift> Driver::getShifts() const
{
  return shifts;
}
