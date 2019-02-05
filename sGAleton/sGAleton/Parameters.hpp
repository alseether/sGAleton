#pragma once

struct Parameters{
	unsigned int populationSize;
	unsigned int generations;
	double crossoverProb;
	double mutationProb;
	bool elitism;
	bool contractivity;
};