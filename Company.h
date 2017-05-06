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
  // métodos de tratamento de linhas e condutores
  void addDriver();
  void removeDriver();
  void addLine();
  void removeLine();
  void pesquisaParagem();
  // metodos get
  string getName() const;
  void visualizaCondutores();
  void visualizaLinhas();
  // metodos set
  void setName(string name);
  vector<Line> obterLinhas(string fileLines);
  vector<Driver> obterCondutores(string fileDrivers);
  // funções auxiliares
  void obterParametrosDriver(unsigned int &id, string &name, unsigned int &maxHours, unsigned int &maxWeekWorkingTime, unsigned int &minRestTime, vector<Shift> &shifts);
  void obterParametrosLinha(unsigned int &id, vector<string> &busStopList, vector<int> &timesList);
  unsigned int obterPosCondutorRemover();
  unsigned int obterPosLinhaRemover();
  unsigned int procuraIdVetorCondutores(unsigned int idCondutor);
  unsigned int procuraIdVetorLinhas(int idLinha);
  vector<int> procuraNomeVetorLinhas(string nomeParagem);
  void obterNomeParagem(string &nomeParagem);
  // outros métodos
  void driversBubblesort();
  void linesBubblesort();
  void serviceDistribution(); // funcao que implementa a afectacao de servico
};