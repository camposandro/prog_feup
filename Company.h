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
  void changeDriver();
  void removeDriver();
  void addLine();
  void changeLine();
  void removeLine();
  void pesquisaParagem();
  // metodos get
  string getName() const;
  void visualizaCondutores() const;
  void visualizaLinhas() const;
  // metodos set
  void setName(string name);
  vector<Line> obterLinhas(string fileLines);
  vector<Driver> obterCondutores(string fileDrivers);
  // funções auxiliares
  void obterParametrosDriver(unsigned int &id, string &name, unsigned int &maxHours, unsigned int &maxWeekWorkingTime, unsigned int &minRestTime, vector<Shift> &shifts);
  void obterParametrosLinha(unsigned int &id, unsigned int &freqBus, vector<string> &busStopList, vector<int> &timesList);
  void obterParamAlterarDriver(unsigned int &newID, string &newName, unsigned int &newMaxHours, unsigned int &newMaxWeekHours, unsigned int &newMinRestTime);
  void obterParamAlterarLinha(unsigned int& newID, unsigned int &newFreqBus, vector<string>& newBusStopList, vector<int>& newTimesList);
  unsigned int obterPosCondutorAlterar();
  unsigned int obterPosCondutorRemover();
  unsigned int obterPosLinhaAlterar();
  unsigned int obterPosLinhaRemover();
  unsigned int procuraIdVetorCondutores(unsigned int idCondutor);
  unsigned int procuraIdVetorLinhas(unsigned int idLinha);
  vector<int> procuraNomeVetorLinhas(string nomeParagem);
  void obterNomeParagem(string &nomeParagem);
  // outros métodos
  void atualizaFicheiroCondutores(string fileDrivers);
  void atualizaFicheiroLinhas(string fileLines);
  void driversBubblesort();
  void linesBubblesort();
  void serviceDistribution(); // funcao que implementa a afectacao de servico
};