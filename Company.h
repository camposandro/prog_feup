#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"

using namespace std;

class Company
{
 private:
  string name;
  vector<Driver> vectorDrivers;
  vector<Line> vectorLines;
 public:
  Company(string name, string fileDrivers, string fileLines);
  void createDriver();
  void removeDriver();
  void createLine();
  void removeLine();
  // metodos get
  string getName() const;
  // metodos set
  void setName(string name);
  vector<Line> obterLinhas(string fileLines);
  vector<Driver> obterCondutores(string fileDrivers);
  // outros metodos
  void obterParametrosDriver(unsigned int &id, string &name, unsigned int &maxHours, unsigned int &maxWeekWorkingTime, unsigned int &minRestTime, vector<Shift> &shifts);
  void obterParametrosLinha(unsigned int &id, vector<string> &busStopList, vector<int> &timesList);
  unsigned int obterPosCondutorRemover();
  unsigned int obterPosLinhaRemover();
  unsigned int procuraIdVetorCondutores(unsigned int idCondutor);
  unsigned int procuraIdVetorLinhas(int idLinha);
  void serviceDistribution(); // funcao que implementa a afectacao de servico
};