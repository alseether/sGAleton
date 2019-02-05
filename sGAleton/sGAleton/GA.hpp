#pragma once
#include <type_traits>
#include <vector>
#include <memory>
#include <functional>
#include "Individual.hpp"
#include "Parameters.hpp"

class GA
{
public:
	typedef std::vector<Individual::Ptr> tPopulation;

public:
	GA();
	~GA();

	Individual::Ptr run(Parameters param);

private:
	void initializePopulation(Parameters param);

	tPopulation defaultSelection(tPopulation pop, Parameters param);
	Individual::Ptr defaultCrossover(Individual::Ptr dad, Individual::Ptr mom, Parameters param);
	Individual::Ptr defaultMutation(Individual::Ptr child, Parameters param);

private:
	tPopulation m_population;
	std::function<tPopulation(tPopulation, Parameters)> m_selection;
	std::function<Individual::Ptr(Individual::Ptr, Individual::Ptr, Parameters)> m_crossover;
	std::function<Individual::Ptr(Individual::Ptr, Parameters)> m_mutation;


};

