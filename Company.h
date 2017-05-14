#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Line.h"
#include "Driver.h"
#include "Bus.h"

using namespace std;

void intervaloTempoServico(unsigned int horaInicio, unsigned int horaFim);

class Company
{
 private:
  string name;
  vector<Driver> vectorDrivers;
  vector<Line> vectorLines;
 public:
  Company(string name, string fileDrivers, string fileLines);
  // métodos de tratamento de linhas e condutores
  void addLine(Line newLine);
  void changeLine(unsigned int lineId);
  void removeLine(unsigned int posLine);
  void addDriver(Driver newDriver);
  void changeDriver(unsigned int driverId);
  void removeDriver(int posDriver);
  // métodos de tratamento de paragens e percursos
  void pesquisaParagem(string nomeParagem, vector<int> idLinhasComParagem);
  void percursoEntreParagens(Line linhaEmComum, unsigned int posParagem1, unsigned int posParagem2);
  // métodos dos horários de linha e paragem
  void horarioLinha(unsigned int lineId, unsigned int posLine, unsigned int horaInicio, unsigned int horaFim);
  void horarioParagem(string nomeParagem, vector<int> linhasComAParagem, unsigned int horaInicio, unsigned int horaFim);
  // metodos get
  string getName() const;
  vector<Driver> getDriversVector() const;
  vector<Line> getLinesVector() const;
  void visualizaCondutores() const;
  void visualizaLinhas() const;
  // metodos set
  void setName(string name);
  vector<Line> obterLinhasFicheiro(string fileLines);
  vector<Driver> obterCondutoresFicheiro(string fileDrivers);
  // outros métodos
  void driversBubblesort();
  void linesBubblesort();
  void atualizaFicheiros(string fileDrivers, string fileLines);
  unsigned int numBusesNeededLine(unsigned int posLine);
  void createBuses(unsigned int horaInicio, unsigned int horaFim);
  void printBusInfo(unsigned int lineId, unsigned int busId);
  void serviceDistribution(unsigned int driverId, unsigned int lineId, unsigned int busId, unsigned int startTime, unsigned int endTime);
  // funções auxiliares
  unsigned int procuraIdVetorCondutores(unsigned int idCondutor);
  unsigned int procuraIdVetorLinhas(unsigned int idLinha);
  vector<int> procuraNomeVetorLinhas(string nomeParagem);
};