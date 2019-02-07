#pragma once
#include "Operators.h"

struct Parameters{
	unsigned int populationSize;
	unsigned int generations;
	double crossoverProb;
	double mutationProb;
	bool elitism;
	bool contractivity;
	std::shared_ptr<SelectionOperator> selection;
	std::shared_ptr<CrossoverOperator> crossover;
	std::shared_ptr<MutationOperator> mutation;
};