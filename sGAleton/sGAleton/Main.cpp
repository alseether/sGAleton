#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include "Environment.hpp"
#include "GA.hpp"
#include "Test.hpp"


int loadProblem(std::string filepath){
	unsigned int R, C, L, H;
	tPizza pizza;
	std::ifstream in;
	in.open(filepath, std::ios::in);
	if (!in.is_open()){
		std::cerr << "Error al abrir el archivo de entrada" << std::endl;
		return -1;
	}

	in >> R; in >> C;
	in >> L; in >> H;

	Environment::getInstance()->setR(R);
	Environment::getInstance()->setC(C);
	Environment::getInstance()->setL(L);
	Environment::getInstance()->setH(H);

	for (unsigned int i = 0; i < R; ++i){
		std::vector<char> row;
		for (unsigned int j = 0; j < C; ++j){
			char c;
			in >> c;
			row.push_back(c);
		}
		pizza.push_back(row);
	}

	Environment::getInstance()->setPizza(pizza);

	in.close();
	return 0;
}

void saveSolution(const std::string type, Individual &best){
	std::ofstream out;
	std::string file = "Solutions\\Sol-" + type + "-" + std::to_string(time(NULL)) + ".txt";
	out.open(file, std::ios::out);
	if (!out.is_open()){
		std::cerr << "Error al abrir el archivo de salida" << std::endl;
		return;
	}

	out << best.getAdaptation() << std::endl;

	out << best.toString() << std::endl;
	
	out.close();
}

std::string pizzaToString(const tPizza &pizza){
	std::string ret = "";
	for (auto r : pizza){
		for (auto c : r){
			ret += c;
		}
		ret += "\n";
	}
	ret += "\n";
	return ret;
}

std::string pizzaToString(const tPizza &pizza, const Individual &best){
	std::string ret = "";
	auto cortesF = best.getChromosome().getCortesF();
	auto cortesC = best.getChromosome().getCortesC();
	auto itF = cortesF.begin();
	auto itC = cortesC.begin();
	for (unsigned int i = 0; i < pizza.size(); ++i){
		itC = cortesC.begin();
		if (itF != cortesF.end() && *itF == i){
			ret += "\n";
			itF++;
		}
		for (unsigned int j = 0; j < pizza[i].size(); ++j){
			if (itC != cortesC.end() && *itC == j){
				ret += " ";
				itC++;
			}
			ret += pizza[i][j];
		}
		ret += "\n";
	}
	ret += "\n";
	return ret;
}


int main(){
	GA ga;

	double bestScore;

	std::shared_ptr<SelectionOperator> sel = std::make_shared<SelectionTournament>();
	std::shared_ptr<CrossoverOperator> cro = std::make_shared<CrossoverShuffle>();
	Environment::getInstance()->setParameters(Parameters{ 100, 200, 0.6, 0.1, false, false, sel, cro, nullptr });
	Individual best;
	Individual bestOfAll;


	bestScore = -1;
	for (int i = 0; i < 100; ++i){
		if (loadProblem("DataSets\\small.in") == -1){
			return -1;
		}

		best = ga.run();

		if (best.getAdaptation() > bestScore){
			bestScore = best.getAdaptation();
			bestOfAll = best;
		}
	}
	saveSolution("small", bestOfAll);

	bestScore = -1;
	for (int i = 0; i < 100; ++i){
		if (loadProblem("DataSets\\medium.in") == -1){
			return -1;
		}

		Environment::getInstance()->setParameters(Parameters{ 50, 100, 0.3, 0.1, false, false, sel, cro, nullptr });

		best = ga.run();

		if (best.getAdaptation() > bestScore){
			bestScore = best.getAdaptation();
			bestOfAll = best;
		}
	}
	saveSolution("medium", bestOfAll);

	bestScore = -1;
	for (int i = 0; i < 50; ++i){
		if (loadProblem("DataSets\\big.in") == -1){
			return -1;
		}

		best = ga.run();

		if (best.getAdaptation() > bestScore){
			bestScore = best.getAdaptation();
			bestOfAll = best;
		}
	}
	saveSolution("big", bestOfAll);
	return 0;

}