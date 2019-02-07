#pragma once
#include <type_traits>
#include <vector>
#include <memory>
#include <functional>
#include "Environment.hpp"

class GA
{
public:
	GA();
	~GA();

	Individual run();

private:
	void initializePopulation();

	double evaluatePopulation();

	void selection();
	void crossover();
	void mutation();

	void sortPopulation();

private:
	tPopulation m_population;
	Individual m_theBest;

	const double ELITE_PERCENTAGE = 0.02;

};

