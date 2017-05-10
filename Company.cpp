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
	vectorDrivers = obterCondutores(fileDrivers);
	vectorLines = obterLinhas(fileLines);
}

// cria condutor
void Company::addDriver(Driver newDriver)
{
	vectorDrivers.push_back(newDriver);
}

// cria linha
void Company::addLine(Line newLine)
{
	vectorLines.push_back(newLine);
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

// percurso entre paragens
void Company::percursoEntreParagens()
{
	cout << endl;
	cin.ignore(); // para limpar o buffer do char anterior

	string nomeParagem1, nomeParagem2;
	cout << "Introduza o nome da paragem de partida: ";
	getline(cin, nomeParagem1);

	cout << "Introduza o nome da paragem de destino: ";
	getline(cin, nomeParagem2);

	// verificar se pertencem a mesma linha

	// vetor que contem as pos das linhas que contiverem a paragem1 e paragem2
	vector<int> LinhasParagem1 = procuraNomeVetorLinhas(nomeParagem1);
	vector<int> LinhasParagem2 = procuraNomeVetorLinhas(nomeParagem2);

	// verificar se existem linhas em comum e caso existam, guardar num vetor LinhasComum
	vector<int> LinhasComum;
	for (size_t i = 0; i < LinhasParagem1.size(); i++)
	{
		for (size_t j = 0; j < LinhasParagem2.size(); j++)
		{
			if (LinhasParagem1.at(i) == LinhasParagem2.at(j))
				LinhasComum.push_back(LinhasParagem1.at(i));
		}
	}

	if (LinhasComum.size() == 0)
		cout << endl << "Nao existem linhas constituidas por ambas as paragens!\n";
	else
	{
		// coloca o nomeParagem1 a minuscula
		string nomeParagem1Minuscula = nomeParagem1;
		for (size_t k = 0; k <= nomeParagem1.length(); k++)
			nomeParagem1Minuscula[k] = tolower(nomeParagem1[k]);

		// coloca o nomeParagem2 a minuscula
		string nomeParagem2Minuscula = nomeParagem2;
		for (size_t k = 0; k <= nomeParagem2.length(); k++)
			nomeParagem2Minuscula[k] = tolower(nomeParagem2[k]);


		// percorre vetor de posicoes das linhas que contêm ambas as paragens
		for (size_t i = 0; i < LinhasComum.size(); i++)
		{
			Line linhaEmComum = vectorLines.at(LinhasComum.at(i));

			// encontrar posicoes respetivas na linha
			int posParagem1, posParagem2;
			for (size_t j = 0; j < linhaEmComum.getBusStops().size(); j++)
			{
				// colocar cada elemento procurado no vetor em minuscula
				string paragemVetor = linhaEmComum.getBusStops().at(j);
				for (int p = 0; p < paragemVetor.length(); p++)
					paragemVetor[p] = tolower(linhaEmComum.getBusStops().at(j).at(p));

				if (paragemVetor == nomeParagem1Minuscula)
					posParagem1 = j;
				if (paragemVetor == nomeParagem2Minuscula)
					posParagem2 = j;
			}

			cout << endl;
			if (posParagem1 == posParagem2)
				cout << "Introduza diferentes paragens!\n";
			else
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

vector<Line> Company::obterLinhas(string fileLines)
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

vector<Driver> Company::obterCondutores(string fileDrivers)
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
/*
void Company::atualizaFicheiroCondutores(string fileDrivers)
{
	char escolha;
	cout << "Deseja atualizar o ficheiro de condutores ? (S para \"sim\", N para \"nao\"): ";
	cin >> escolha;

	while (cin.fail() || escolha != 'S' && escolha != 'N')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "Deseja atualizar o ficheiro de condutores ? (S para \"sim\", N para \"nao\"): ";
		cin >> escolha;
	}

	if (escolha == 'S')
	{
		// escrever no ficheiro (opcional)
		ofstream ficheiroSaida(fileDrivers);
		for (size_t i = 0; i < vectorDrivers.size(); i++)
		{
			ficheiroSaida << vectorDrivers.at(i).getId() << " ; " << vectorDrivers.at(i).getName() << " ; " <<
				vectorDrivers.at(i).getShiftMaxDuration() << " ; " << vectorDrivers.at(i).getMaxWeekWorkingTime()
				<< " ; " << vectorDrivers.at(i).getMinRestTime() << endl;
		}
	}
}

void Company::atualizaFicheiroLinhas(string fileLines)
{
	char escolha;
	cout << "Deseja atualizar o ficheiro de linhas ? (S para \"sim\", N para \"nao\"): ";
	cin >> escolha;

	while (cin.fail() || escolha != 'S' && escolha != 'N')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Introduza uma opcao valida!\n";
		cout << "Deseja atualizar o ficheiro de linhas ? (S para \"sim\", N para \"nao\"): ";
		cin >> escolha;
	}

	if (escolha == 'S')
	{
		// escrever no ficheiro (opcional)
		ofstream ficheiroSaida(fileLines);
		for (size_t i = 0; i < vectorLines.size(); i++)
		{
			ficheiroSaida << vectorLines.at(i).getId() << " ; " << vectorLines.at(i).getFreqBus() << " ; ";
			for (size_t j = 0; j < vectorLines.at(i).getBusStops().size(); j++)
			{
				if (j == vectorLines.at(i).getBusStops().size() - 1)
					ficheiroSaida << vectorLines.at(i).getBusStops().at(j) << "; ";
				else ficheiroSaida << vectorLines.at(i).getBusStops().at(j) << ", ";
			}
			for (size_t k = 0; k < vectorLines.at(i).getTimings().size(); k++)
			{
				if (k == vectorLines.at(i).getTimings().size() - 1)
					ficheiroSaida << vectorLines.at(i).getTimings().at(k) << endl;
				else ficheiroSaida << vectorLines.at(i).getTimings().at(k) << ", ";
			}
		}
	}
}
*/

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