#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>

#include "Bus.h"
#include "Company.h"

ostream& operator<<(ostream& out, const Bus &bus);
ostream& operator<<(ostream& out, const Shift &shift);
void mostraTurnosAtribuidos();

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
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar ID? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
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
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar frequencia? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
		{
			unsigned int newFreq;
			cout << "Insira a nova frequencia: ";
			cin >> newFreq;
			vectorLines.at(posLine).setFreqBus(newFreq);
		}

		cout << "Alterar paragens? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar paragens? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
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
		else if (option == 'n')
		{
			cout << "Alterar tempos de viagem? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
			while (option != 's' && option != 'n')
			{
				cout << "Insira uma opcao valida!\n";
				cout << "Alterar tempos de viagem? (S para \"sim\", N para \"nao\") ";
				cin >> option;
				option = tolower(option);
			}
			if (option == 's')
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
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar ID? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
		{
			unsigned int newId;
			cout << "Insira o novo ID: ";
			cin >> newId;
			vectorDrivers.at(posDriver).setId(newId);
		}

		cout << "Alterar nome? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar nome? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
		{
			string newName;
			cout << "Insira o novo nome: ";
			cin >> newName;
			vectorDrivers.at(posDriver).setName(newName);
		}

		cout << "Alterar o numero de horas consecutivas de turno diario? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar o numero de horas consecutivas de turno diario? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
		{
			unsigned int newMaxHours;
			cout << "Insira o novo numero de horas consecutivas de turno diario: ";
			cin >> newMaxHours;
			vectorDrivers.at(posDriver).setMaxHours(newMaxHours);
		}

		cout << "Alterar o numero maximo de horas de trabalho por semana? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar o numero maximo de horas de trabalho por semana? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
		{
			unsigned int newMaxWeekHours;
			cout << "Insira o novo numero maximo de horas de trabalho por semana: ";
			cin >> newMaxWeekHours;
			vectorDrivers.at(posDriver).setMaxWeekWorkingTime(newMaxWeekHours);
		}

		cout << "Alterar o numero minimo de horas de descanso entre turnos? (S para \"sim\", N para \"nao\") ";
		cin >> option;
		option = tolower(option);
		while (option != 's' && option != 'n')
		{
			cout << "Insira uma opcao valida!\n";
			cout << "Alterar o numero minimo de horas de descanso entre turnos? (S para \"sim\", N para \"nao\") ";
			cin >> option;
			option = tolower(option);
		}
		if (option == 's')
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
		unsigned int tempoFinal = 0;
		for (size_t k = posParagem1; k > posParagem2; k--)
		{
			// imprime os trajetos entre as paragens entre "-->"
			cout << left << setw(linhaEmComum.getBusStops().at(k).length() + 1) << linhaEmComum.getBusStops().at(k) << "-->"
				<< right << setw(linhaEmComum.getBusStops().at(k - 1).length() + 1) << linhaEmComum.getBusStops().at(k - 1);
			// imprime os tempos de cada trajeto 
			cout << " " << linhaEmComum.getTimings().at(k - 1) << "min" << endl;
			tempoFinal += linhaEmComum.getTimings().at(k - 1);
		}
		if (tempoFinal > 60)
		{
			unsigned int nHoras = tempoFinal / 60, nMin = tempoFinal % 60;
			cout << "Tempo total da viagem: " << nHoras << " hora(s) e " << nMin << " min" << endl;
		}
		else cout << "Tempo total da viagem: " << tempoFinal << "min" << endl;
	}
	// caso se introduza no sentido inverso
	else if (posParagem2 > posParagem1)
	{
		unsigned int tempoFinal = 0;
		for (size_t k = posParagem1; k < posParagem2; k++)
		{
			// imprime os trajetos entre as paragens entre "-->"
			cout << left << setw(linhaEmComum.getBusStops().at(k).length() + 1) << linhaEmComum.getBusStops().at(k) << "-->"
				<< right << setw(linhaEmComum.getBusStops().at(k + 1).length() + 1) << linhaEmComum.getBusStops().at(k + 1);
			// imprime os tempos de cada trajeto 
			cout << " " << linhaEmComum.getTimings().at(k) << "min" << endl;
			tempoFinal += linhaEmComum.getTimings().at(k);
		}
		if (tempoFinal > 60)
		{
			unsigned int nHoras = tempoFinal / 60, nMin = tempoFinal % 60;
			cout << "Tempo total da viagem: " << nHoras << " hora(s) e " << nMin << " min" << endl;
		}
		else cout << "Tempo total da viagem: " << tempoFinal << "min" << endl;
	}
}

// percurso entre paragens sem linha em comum
vector<string> nomeParagemComum;
void Company::percursoEntreParagensSemLinhaComum(vector<int> linhasParagem1, vector<int> linhasParagem2, string paragemInicial, string paragemFinal)
{
	for (size_t i = 0; i < linhasParagem1.size(); i++)
	{
		for (size_t j = 0; j < linhasParagem2.size(); j++)
		{
			Line linhai = vectorLines.at(linhasParagem1.at(i));
			Line linhaj = vectorLines.at(linhasParagem2.at(j));
			vector<string> busStopsi = linhai.getBusStops();
			vector<string> busStopsj = linhaj.getBusStops();

			int posParagemFinal = -1, posParagemInicial = -1;
			for (size_t k = 0; k < busStopsi.size(); k++)
			{
				if (busStopsi.at(k) == paragemInicial)
					posParagemInicial = k;

				for (size_t p = 0; p < busStopsj.size(); p++)
				{
					if (busStopsj.at(p) == paragemFinal)
						posParagemFinal = p;

					if (busStopsi.at(k) == busStopsj.at(p))
					{
						unsigned int posLinhai = k;
						unsigned int posLinhaj = p;
						nomeParagemComum.push_back(busStopsi.at(k));
						imprimePercursoParagens2(linhai, linhaj , posParagemInicial, posParagemFinal, posLinhai, posLinhaj);
					}
				}
			}
		}
	}

	if (nomeParagemComum.size() == 0)
	{
		cout << "Nao existem linhas com paragem em comum com as dadas para fazer o transbordo ...\n\n";
		return;
	}
}

void Company::imprimePercursoParagens2(Line linhai, Line linhaj, int posInicial, int posFinal, unsigned int posLinhai, unsigned int posLinhaj)
{
	cout << endl << "PERCURSO " << "NA LINHA " << linhai.getId() << ":" << endl;

	if (posInicial == -1 || posFinal == -1) return;

	// caso se introduza no sentido original
	if (posInicial < posLinhai)
	{
		unsigned int tempoFinal = 0;
		for (size_t k = posInicial; k < posLinhai; k++)
		{
			// imprime os trajetos entre as paragens entre "-->"
			cout << left << setw(linhai.getBusStops().at(k).length() + 1) << linhai.getBusStops().at(k) << "-->"
				<< right << setw(linhai.getBusStops().at(k + 1).length() + 1) << linhai.getBusStops().at(k + 1);
			// imprime os tempos de cada trajeto 
			cout << " " << linhai.getTimings().at(k) << "min" << endl;
			tempoFinal += linhai.getTimings().at(k);
		}

		if (posFinal < posLinhaj)
		{
			for (size_t k = posLinhaj; k > posFinal; k--)
			{
				// imprime os trajetos entre as paragens entre "-->"
				cout << left << setw(linhaj.getBusStops().at(k).length() + 1) << linhaj.getBusStops().at(k) << "-->"
					<< right << setw(linhaj.getBusStops().at(k - 1).length() + 1) << linhaj.getBusStops().at(k - 1);
				// imprime os tempos de cada trajeto 
				cout << " " << linhaj.getTimings().at(k - 1) << "min" << endl;
				tempoFinal += linhaj.getTimings().at(k - 1);
			}
		}
		else if (posFinal > posLinhaj)
		{
			for (size_t k = posLinhaj; k < posFinal; k++)
			{
				// imprime os trajetos entre as paragens entre "-->"
				cout << left << setw(linhaj.getBusStops().at(k).length() + 1) << linhaj.getBusStops().at(k) << "-->"
					<< right << setw(linhaj.getBusStops().at(k + 1).length() + 1) << linhaj.getBusStops().at(k + 1);
				// imprime os tempos de cada trajeto 
				cout << " " << linhaj.getTimings().at(k) << "min" << endl;
				tempoFinal += linhaj.getTimings().at(k);
			}
		}

		if (tempoFinal > 60)
		{
			unsigned int nHoras = tempoFinal / 60, nMin = tempoFinal % 60;
			cout << "Tempo total da viagem: " << nHoras << " hora(s) e " << nMin << " min" << endl;
		}
		else cout << "Tempo total da viagem: " << tempoFinal << "min" << endl;
	}
	// caso se introduza no sentido inverso
	else if (posInicial > posLinhai)
	{
		unsigned int tempoFinal = 0;
		for (size_t k = posLinhai; k < posInicial; k--)
		{
			// imprime os trajetos entre as paragens entre "-->"
			cout << left << setw(linhai.getBusStops().at(k).length() + 1) << linhai.getBusStops().at(k) << "-->"
				<< right << setw(linhai.getBusStops().at(k - 1).length() + 1) << linhai.getBusStops().at(k - 1);
			// imprime os tempos de cada trajeto 
			cout << " " << linhai.getTimings().at(k - 1) << "min" << endl;
			tempoFinal += linhai.getTimings().at(k - 1);
		}

		if (posFinal < posLinhaj)
		{
			for (size_t k = posLinhaj; k > posFinal; k--)
			{
				// imprime os trajetos entre as paragens entre "-->"
				cout << left << setw(linhaj.getBusStops().at(k).length() + 1) << linhaj.getBusStops().at(k) << "-->"
					<< right << setw(linhaj.getBusStops().at(k - 1).length() + 1) << linhaj.getBusStops().at(k - 1);
				// imprime os tempos de cada trajeto 
				cout << " " << linhaj.getTimings().at(k - 1) << "min" << endl;
				tempoFinal += linhaj.getTimings().at(k - 1);
			}
		}
		else if (posFinal > posLinhaj)
		{
			for (size_t k = posLinhaj; k < posFinal; k++)
			{
				// imprime os trajetos entre as paragens entre "-->"
				cout << left << setw(linhaj.getBusStops().at(k).length() + 1) << linhaj.getBusStops().at(k) << "-->"
					<< right << setw(linhaj.getBusStops().at(k + 1).length() + 1) << linhaj.getBusStops().at(k + 1);
				// imprime os tempos de cada trajeto 
				cout << " " << linhaj.getTimings().at(k) << "min" << endl;
				tempoFinal += linhaj.getTimings().at(k);
			}
		}

		if (tempoFinal > 60)
		{
			unsigned int nHoras = tempoFinal / 60, nMin = tempoFinal % 60;
			cout << "Tempo total da viagem: " << nHoras << " hora(s) e " << nMin << " min" << endl;
		}
		else cout << "Tempo total da viagem: " << tempoFinal << "min" << endl;
	}
}

// horário de linha
void Company::horarioLinha(unsigned int lineId, unsigned int posLine, unsigned int horaInicio, unsigned int horaFim)
{
	const int HORA_INICIO = horaInicio, HORA_FIM = horaFim;

	Line LinhaMostrar = vectorLines.at(posLine);

	cout << endl << "Linha " << lineId << endl;
	// impressao dos nomes das paragens na primeira linha
	for (size_t i = 0; i < LinhaMostrar.getBusStops().size(); i++)
	{
		// tamanho do nome da paragem
		int tamanhoNomeParagem = LinhaMostrar.getBusStops().at(i).length();

		if (i == LinhaMostrar.getBusStops().size() - 1)
			cout << left << setw(tamanhoNomeParagem + 2) << LinhaMostrar.getBusStops().at(i) << endl;
		else
			cout << left << setw(tamanhoNomeParagem + 2) << LinhaMostrar.getBusStops().at(i);
	}

	// percorrem-se as linhas uma a uma para introduzir os tempos
	int horaLin = HORA_INICIO, horaCol = HORA_INICIO, minLin = 0, minCol = 0;

	// caso haja o problema de o horario ser noturno
	int nHoras;
	if (HORA_FIM - HORA_INICIO < 0)
		nHoras = 24 - HORA_INICIO + HORA_FIM;
	else nHoras = HORA_FIM - HORA_INICIO;

	// numero de linhas de horario a imprimir
	int nLinhas = (60 / LinhaMostrar.getFreqBus()) * nHoras;

	for (int linhas = 0; linhas < nLinhas; linhas++)
	{
		for (int colunas = 0; colunas < LinhaMostrar.getBusStops().size(); colunas++)
		{
			int tamanhoImpressao = LinhaMostrar.getBusStops().at(colunas).length() + 2;

			ostringstream streamHoras;
			if (horaCol < 10 && minCol < 10)
			{
				streamHoras << setw(2) << setfill('0') << horaCol << ":" << setw(2) << setfill('0') << minCol;
				string horas = streamHoras.str();
				cout << left << setw(tamanhoImpressao) << horas;
			}
			else if (horaCol < 10 && minCol >= 10)
			{
				streamHoras << setw(2) << setfill('0') << horaCol << ":" << setw(2) << minCol;
				string horas = streamHoras.str();
				cout << left << setw(tamanhoImpressao) << horas;
			}
			else if (minCol < 10 && horaCol >= 10)
			{
				streamHoras << setw(2) << horaCol << ":" << setw(2) << setfill('0') << minCol;
				string horas = streamHoras.str();
				cout << left << setw(tamanhoImpressao) << horas;
			}
			else
			{
				streamHoras << setw(2) << horaCol << ":" << setw(2) << minCol;
				string horas = streamHoras.str();
				cout << left << setw(tamanhoImpressao) << horas;
			}

			if (colunas < LinhaMostrar.getBusStops().size() - 1)
				minCol += LinhaMostrar.getTimings().at(colunas);

			if (minCol / 60 == 1)
			{
				horaCol++;
				minCol = minCol % 60;
			}

			if (horaCol == 24)
				horaCol = 0;

			if (colunas == LinhaMostrar.getTimings().size()) cout << endl;
		}

		minLin += LinhaMostrar.getFreqBus();

		if (minLin / 60 == 1)
		{
			horaLin++;
			minLin = minLin % 60;
		}

		if (horaLin == 24)
			horaLin = 0;

		horaCol = horaLin;
		minCol = minLin;

	}
}

// horario de paragem
void Company::horarioParagem(string nomeParagem, vector<int> linhasComAParagem, unsigned int horaInicio, unsigned int horaFim)
{
	const int HORA_INICIO = horaInicio, HORA_FIM = horaFim;

	cout << endl;
	for (size_t j = 0; j < linhasComAParagem.size(); j++)
	{
		Line LinhaMostrar = vectorLines.at(linhasComAParagem.at(j));
		cout << "Linha " << LinhaMostrar.getId() << endl;

		// retrieve the pos of the stop inside its own line
		int posOfStop;
		for (size_t k = 0; k < LinhaMostrar.getBusStops().size(); k++)
		{
			if (LinhaMostrar.getBusStops().at(k) == nomeParagem)
				posOfStop = k;
		}

		// caso haja o problema de o horario ser noturno
		int nHoras;
		if (HORA_FIM - HORA_INICIO < 0)
			nHoras = 24 - HORA_INICIO + HORA_FIM;
		else nHoras = HORA_FIM - HORA_INICIO;

		int nImpressoes = (((60 / LinhaMostrar.getFreqBus()) * nHoras + 1) / 6) + 1;
		int hora = HORA_INICIO, min = 0;

		// calculo dos minutos iniciais
		for (size_t i = 1; i <= posOfStop; i++)
			min += LinhaMostrar.getTimings().at(i - 1);

		// calculo da hora final da paragem
		int horaFinalParagem = HORA_INICIO;
		int minFinalParagem = min + ((60 / LinhaMostrar.getFreqBus()) * nHoras + 1) * LinhaMostrar.getFreqBus();
		if (minFinalParagem > 60)
		{
			horaFinalParagem += minFinalParagem / 60;
			minFinalParagem = minFinalParagem % 60;
		}
		if (horaFinalParagem > 24) horaFinalParagem -= 24;

		if (min / 60 == 1)
		{
			hora++;
			min = min % 60;
		}

		for (int linhas = 0; linhas < nImpressoes; linhas++)
		{
			for (int colunas = 0; colunas < 6; colunas++)
			{
				int tamanhoImpressao = 7;

				ostringstream streamHoras;
				if (hora < 10 && min < 10)
				{
					streamHoras << setw(2) << setfill('0') << hora << ":" << setw(2) << setfill('0') << min;
					string horas = streamHoras.str();
					cout << left << setw(tamanhoImpressao) << horas;
				}
				else if (hora < 10 && min >= 10)
				{
					streamHoras << setw(2) << setfill('0') << hora << ":" << setw(2) << min;
					string horas = streamHoras.str();
					cout << left << setw(tamanhoImpressao) << horas;
				}
				else if (min < 10 && hora >= 10)
				{
					streamHoras << setw(2) << hora << ":" << setw(2) << setfill('0') << min;
					string horas = streamHoras.str();
					cout << left << setw(tamanhoImpressao) << horas;
				}
				else
				{
					streamHoras << setw(2) << hora << ":" << setw(2) << min;
					string horas = streamHoras.str();
					cout << left << setw(tamanhoImpressao) << horas;
				}

				min += LinhaMostrar.getFreqBus();

				if (min / 60 == 1)
				{
					hora++;
					min = min % 60;
				}

				if (hora == 24)
					hora = 0;

				if (hora == horaFinalParagem) break;
				if (colunas == 5 && linhas != nImpressoes - 1) cout << endl;
			}
			if (hora == horaFinalParagem) break;
		}

		if (j != linhasComAParagem.size() - 1) cout << endl << endl;
		else cout << endl;
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
unsigned int Company::numBusesNeededLine(unsigned int posLine)
{
	// tempo de ida e volta numa viagem da linha
	unsigned int tempo_ida_e_volta = 0;
	vector<int> vetorTempos = vectorLines.at(posLine).getTimings();
	for (size_t j = 0; j < vetorTempos.size(); j++)
		tempo_ida_e_volta += vetorTempos.at(j);

	// freq. dos autocarros na linha
	unsigned int freqBusLinha = vectorLines.at(posLine).getFreqBus();

	// numero de autocarros necessarios para o percurso
	unsigned int numberBusesLine = (int)((double)tempo_ida_e_volta / freqBusLinha + 1.0);

	return numberBusesLine;
}

vector<Bus> vetorBuses;
void Company::createBuses(unsigned int horaInicio, unsigned int horaFim)
{
	unsigned int HORA_INICIO = horaInicio, HORA_FIM = horaFim;

	/* criação de um vetor com todos os autocarros de todas as linhas*/
	vector<Bus> vectorBuses;
	for (size_t i = 0; i < vectorLines.size(); i++)
	{
		HORA_INICIO = horaInicio, HORA_FIM = horaFim;

		unsigned int lineId = vectorLines.at(i).getId();
		vector<Shift> vectorSchedule;

		unsigned int numBuses = numBusesNeededLine(i);
		for (size_t j = 1; j <= numBuses; j++)
		{
			HORA_INICIO = horaInicio, HORA_FIM = horaFim;

			// assumindo turnos de 1 hora
			unsigned int nShiftsPerBus = HORA_FIM - HORA_INICIO;
			for (size_t k = 0; k < nShiftsPerBus; k++)
			{
				Shift newShift(lineId, 0, j, HORA_INICIO, HORA_INICIO++);
				vectorSchedule.push_back(newShift);
			}

			Bus newBus(j, 0, lineId);
			newBus.setSchedule(vectorSchedule);
			vectorBuses.push_back(newBus);
		}
	}

	vetorBuses = vectorBuses;
}

void Company::printBusInfo(unsigned int lineId, unsigned int busId)
{
	for (size_t i = 0; i < vetorBuses.size(); i++)
	{
		Bus bus = vetorBuses.at(i);
		if (bus.getBusOrderInLine() == busId && bus.getLineId() == lineId)
			cout << bus;
	}
}

vector<Shift> vetorTurnosAtribuidos;
void Company::serviceDistribution(unsigned int driverId, unsigned int lineId, unsigned int busId, unsigned int startTime, unsigned int endTime)
{
	for (size_t i = 0; i < vetorBuses.size(); i++)
	{
		Bus bus = vetorBuses.at(i);

		if (bus.getLineId() == lineId && bus.getBusOrderInLine() == busId)
		{
			unsigned int posBus = i;
			for (size_t j = 0; j < bus.getSchedule().size(); j++)
			{
				if (bus.getSchedule().at(j).getStartTime() == startTime && bus.getSchedule().at(j).getEndTime() == endTime)
				{
					unsigned int posShift = j;
					unsigned int somaHorasCondutor = 0;
					for (size_t k = 0; k < vetorTurnosAtribuidos.size(); k++)
					{
						if (vetorTurnosAtribuidos.at(k).getDriverId() == driverId)
						{
							somaHorasCondutor++;
						}
					}

					unsigned int posVetorCondutores = procuraIdVetorCondutores(driverId);

					if (somaHorasCondutor >= vectorDrivers.at(posVetorCondutores).getMaxWeekWorkingTime())
					{
						cout << "O condutor introduzido ja nao pode realizar mais horas de trabalho\n";
					}
					else
					{
						vetorBuses.at(posBus).getSchedule().at(posShift).setDriverId(driverId);
						vetorTurnosAtribuidos.push_back(bus.getSchedule().at(j));
						vetorBuses.at(posBus).getSchedule().erase(vetorBuses.at(posBus).getSchedule().begin() + posShift);
					}
				}
			}
		}
	}
}

// mostra turnos atribuidos
void mostraTurnosAtribuidos()
{
	for (size_t i = 0; i < vetorTurnosAtribuidos.size(); i++)
	{
		cout << vetorTurnosAtribuidos.at(i) << endl;
	}
}

// --- efetuar gravação das alterações nos ficheiros ---
void Company::atualizaFicheiros(string fileDrivers, string fileLines)
{
	cout << endl;

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
			ficheiroSaida << vectorDrivers.at(i).getId() << " ; " <<
				vectorDrivers.at(i).getName() << " ; " <<
				vectorDrivers.at(i).getShiftMaxDuration() << " ; " <<
				vectorDrivers.at(i).getMaxWeekWorkingTime() << " ; " <<
				vectorDrivers.at(i).getMinRestTime() << endl;
		}
	}

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
			ficheiroSaida << vectorLines.at(i).getId() <<
				" ; " << vectorLines.at(i).getFreqBus() << " ; ";
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

// --- funções auxiliares ---

// obter o numero de shifts conforme o tempo de servico
unsigned int intervaloServico;
void intervaloTempoServico(unsigned int horaInicio, unsigned int horaFim)
{
	intervaloServico = horaFim - horaInicio;
}

// overloading do operador << para bus
ostream& operator<<(ostream& out, const Bus &bus)
{
	out << endl;
	out << "BUS ID: " << bus.getBusOrderInLine() << endl;
	out << "LINE ID: " << bus.getLineId() << endl;
	out << "SHIFTS: " << endl;
	for (size_t i = 0; i < intervaloServico; i++)
	{
		Shift shift = bus.getSchedule().at(i);
		string horas = to_string(shift.getEndTime()) + 'h' + '-' + to_string(shift.getStartTime()) + 'h';
		out << "->" << left << setw(10) << horas << "DRIVER ID: " << shift.getDriverId() << endl;
	}

	return out;
}

ostream& operator<<(ostream& out, const Shift &shift)
{
	string horas = to_string(shift.getEndTime()) + 'h' + '-' + to_string(shift.getStartTime()) + 'h';
	out << "->" << left << setw(10) << horas << "DRIVER ID: " << shift.getDriverId() << endl;

	return out;
}

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