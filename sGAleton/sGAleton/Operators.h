#pragma once

#include <set>
#include <algorithm>

#include "Individual.hpp"
#include "MyRandom.hpp"

typedef std::vector<Individual> tPopulation;

class SelectionOperator{
public:

	virtual tPopulation select(const tPopulation &pop) = 0;

	virtual std::string toString() = 0;
};

class CrossoverOperator{
public:

	virtual Individual crossover(const Individual &dad, const Individual &mom) = 0;

	virtual std::string toString() = 0;
};

class MutationOperator{
public:

	virtual void mutate(Individual &child) = 0;

	virtual std::string toString() = 0;
};

class SelectionRulette : public SelectionOperator {
public:
	tPopulation select(const tPopulation &pop){
		std::vector<unsigned int> seleccionados;
		double prob;
		unsigned int posSuper;
		for (unsigned int i = 0; i < pop.size(); ++i){
			prob = MyRandom::getRandom(0.f, 1.f);
			posSuper = 0;
			while ((posSuper < pop.size()) && (prob > pop[posSuper].getScoreAcum()))
				posSuper++;
			seleccionados.push_back(posSuper);
		}
		tPopulation newPop;
		for (unsigned int i = 0; i < pop.size(); ++i){
			newPop.push_back(pop[seleccionados[i]]);
		}

		return newPop;
	}

	std::string toString(){
		return "Selection Rulette";
	}

};

class SelectionTournament : public SelectionOperator {
public:
	tPopulation select(const tPopulation &pop){
		std::vector<unsigned int> seleccionados;
		unsigned int posMejor;
		unsigned int indexA, indexB, indexC;
		for (unsigned int i = 0; i < pop.size(); ++i){
			// Torneo con muestreo diferenciado (cada elemento solo una vez)
			indexA = MyRandom::getRandom(0u, pop.size() - 1);
			do{
				indexB = MyRandom::getRandom(0u, pop.size() - 1);
			} while (indexB == indexA);
			do{
				indexC = MyRandom::getRandom(0u, pop.size() - 1);
			} while (indexB == indexC || indexA == indexC);

			if (pop[indexA].getAdaptation() > pop[indexB].getAdaptation()){
				if (pop[indexA].getAdaptation() > pop[indexC].getAdaptation()){
					posMejor = indexA;
				}
				else{
					posMejor = indexC;
				}
			}
			else{
				if (pop[indexC].getAdaptation() > pop[indexB].getAdaptation()){
					posMejor = indexC;
				}
				else{
					posMejor = indexB;
				}
			}

			seleccionados.push_back(posMejor);
		}

		tPopulation newPop;
		for (unsigned int i = 0; i < pop.size(); ++i){
			newPop.push_back(pop[seleccionados[i]]);
		}

		return newPop;
	}

	std::string toString(){
		return "Selection Tournament";
	}
};

class CrossoverShuffle : public CrossoverOperator{
public:
	Individual crossover(const Individual &dad, const Individual &mom){
		Chromosome dadChromo = dad.getChromosome();
		Chromosome momChromo = mom.getChromosome();
		double dadAdapt = dad.getAdaptation();
		double momAdapt = mom.getAdaptation();


		// Cortes por FILA
		auto dadCortesF = dadChromo.getCortesF();
		auto momCortesF = momChromo.getCortesF();

		std::set<unsigned int> bothCutsF;

		auto dadItF = dadCortesF.begin();
		while (dadItF != dadCortesF.end()){
			bothCutsF.insert(*dadItF);
			dadItF++;
		}

		auto momItF = momCortesF.begin();
		while (momItF != momCortesF.end()){
			bothCutsF.insert(*momItF);
			momItF++;
		}

		std::vector<unsigned int> childCortesF;

		auto bothItF = bothCutsF.begin();
		while (bothItF != bothCutsF.end()){
			if (rand() % 2){
				childCortesF.push_back(*bothItF);
			}
			bothItF++;
		}

		// Cortes por COLUMNA
		auto dadCortesC = dadChromo.getCortesC();
		auto momCortesC = momChromo.getCortesC();

		std::set<unsigned int> bothCutsC;

		auto dadItC = dadCortesC.begin();
		while (dadItC != dadCortesC.end()){
			bothCutsC.insert(*dadItC);
			dadItC++;
		}

		auto momItC = momCortesC.begin();
		while (momItC != momCortesC.end()){
			bothCutsC.insert(*momItC);
			momItC++;
		}

		std::vector<unsigned int> childCortesC;

		auto bothItC = bothCutsC.begin();
		while (bothItC != bothCutsC.end()){
			if (rand() % 2){
				childCortesC.push_back(*bothItC);
			}
			bothItC++;
		}

		std::sort(childCortesF.begin(), childCortesF.end());
		std::sort(childCortesC.begin(), childCortesC.end());

		Individual child(childCortesF, childCortesC);

		return child;

	}

	std::string toString(){
		return "Crossover Shuffle";
	}

private:
};