#pragma once

#include <memory>
#include "Chromosome.hpp"

class Individual
{
public:
	Individual(std::vector<unsigned int> cF, std::vector<unsigned int> cC);

	Individual();

	~Individual();

	double fitness();

	Chromosome	getChromosome() const;
	void		setChromosome(Chromosome chromo);

	void	setScore(double score);

	void	setScoreAcum(double scoreAcum);

	void	setAdaptation(double adaptation);

	double	getScore() const;

	double	getScoreAcum() const;

	double	getAdaptation() const;

	std::string toString() const;

private:
	Chromosome m_chromosome;

	double m_score;
	double m_scoreAcum;
	double m_adaptation;
};

