#include <algorithm>
#include "GA.hpp"
#include "Parameters.hpp"
#include "Environment.hpp"
#include "Individual.hpp"

using namespace std::placeholders;

GA::GA()
{
	
}

GA::~GA()
{

}

Individual GA::run(){
	Parameters param = Environment::getInstance()->getParameters();

	std::vector<Individual> elite;
	bool localContractivity = param.contractivity;
	unsigned int discardedGenerations = 0;
	int generation = 0;
	double currentAvg, lastAvg;
	int nElite = param.populationSize * ELITE_PERCENTAGE;
	int pizzaArea = Environment::getInstance()->getR() * Environment::getInstance()->getC();
	initializePopulation();
	lastAvg = evaluatePopulation();
	
	while (generation < param.generations && m_theBest.getAdaptation() < pizzaArea){
		if (param.elitism){
			elite.clear();
			sortPopulation();
			for (unsigned int i = 0; i < nElite; ++i){
				elite.push_back(m_population[i]);
			}
		}

		selection();

		crossover();

		mutation();

		currentAvg = evaluatePopulation();
		if (param.elitism){
			sortPopulation();
			for (unsigned int i = 0; i < nElite; ++i){
				m_population.pop_back();
			}
			for (unsigned int i = 0; i < nElite; ++i){
				m_population.push_back(elite[i]);
			}
			currentAvg = evaluatePopulation();
		}

		if (localContractivity){
			if (lastAvg < currentAvg){
				lastAvg = currentAvg;
				generation++;
			}
			else{
				discardedGenerations++;
			}
			if (discardedGenerations > (0.5 * param.generations)){
				localContractivity = false;
			}

		}
		else{
			generation++;
		}
	}

	return m_theBest;
}

void GA::initializePopulation(){
	Parameters param = Environment::getInstance()->getParameters();
	m_population.clear();
	for (int i = 0; i < param.populationSize; ++i){
		m_population.push_back(Individual{});
	}
	return;
}

double GA::evaluatePopulation(){
	Parameters param = Environment::getInstance()->getParameters();
	double maximo = -50000;
	double aux = 0;
	double sumaAptitud = 0;
	double puntAcum = 0;
	double media = 0;

	unsigned int indexOfTheBest;

	// Busqueda del mejor
	for (std::size_t i = 0; i < m_population.size(); ++i){
		aux = m_population[i].fitness();
		sumaAptitud += aux;
		if (maximo < aux){
			maximo = aux;
			indexOfTheBest = i;
		}
	}

	// Ajuste de las puntuaciones (normal y acumulada)
	for (std::size_t i = 0; i < m_population.size(); ++i){
		m_population[i].setScore(m_population[i].getAdaptation() / sumaAptitud);
		m_population[i].setScoreAcum(m_population[i].getScore() + puntAcum);
		puntAcum += m_population[i].getScore();
	}

	// Se determina si hay alguno mejor que el que ya se tiene
	double evElMejor = m_theBest.getAdaptation();
	double evMejorActual = m_population[indexOfTheBest].getAdaptation();
	if (evMejorActual > evElMejor){
		m_theBest = m_population[indexOfTheBest];
	}

	return (sumaAptitud / m_population.size());
}

void GA::selection(){
	Parameters param = Environment::getInstance()->getParameters();
	if (param.selection){
		m_population = param.selection->select(m_population);
	}
}

void GA::crossover(){
	Parameters param = Environment::getInstance()->getParameters();
	if (param.crossover){
		std::vector<unsigned int> seleccionados;
		double prob;
		for (int i = 0; i <m_population.size(); ++i){
			prob = MyRandom::getRandom(0.f, 1.f);
			if (prob < param.crossoverProb){
				seleccionados.push_back(i);
			}
		}

		if (seleccionados.size() % 2 == 1){
			seleccionados.pop_back();
		}
		for (int i = 0; i < seleccionados.size(); i += 2){
			Individual child1 = param.crossover->crossover(m_population[seleccionados[i]], m_population[seleccionados[i + 1]]);
			Individual child2 = param.crossover->crossover(m_population[seleccionados[i]], m_population[seleccionados[i + 1]]);
			m_population[seleccionados[i]] = child1;
			m_population[seleccionados[i + 1]] = child2;
		}
	}
}

void GA::mutation(){
	Parameters param = Environment::getInstance()->getParameters();
	if (param.mutation){
		std::vector<unsigned int> seleccionados;
		double prob;
		for (int i = 0; i < m_population.size(); ++i){
			prob = MyRandom::getRandom(0.f, 1.f);
			if (prob < param.mutationProb){
				seleccionados.push_back(i);
			}
		}

		for (int i = 0; i < seleccionados.size(); ++i){
			param.mutation->mutate(m_population[seleccionados[i]]);
		}
	}
}

void GA::sortPopulation(){
	std::sort(m_population.begin(), m_population.end(), [](Individual a, Individual b){
		return a.getAdaptation() > b.getAdaptation();
	});
}