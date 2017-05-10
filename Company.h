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
  void addDriver(Driver newDriver);
  void addLine(Line newLine);
  void pesquisaParagem();
  void percursoEntreParagens();
  // metodos get
  string getName() const;
  vector<Driver> getDriversVector() const;
  vector<Line> getLinesVector() const;
  void visualizaCondutores() const;
  void visualizaLinhas() const;
  // metodos set
  void setName(string name);
  vector<Line> obterLinhas(string fileLines);
  vector<Driver> obterCondutores(string fileDrivers);
  // funções auxiliares
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