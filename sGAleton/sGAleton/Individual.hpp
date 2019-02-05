#pragma once

#include <memory>
#include "Chromosome.hpp"

class Individual
{
public:
	typedef std::shared_ptr<Individual> Ptr;

public:
	Individual();
	~Individual();

	virtual double fitness() = 0;

	Chromosome::Ptr	getChromosome(){ return m_chromosome; };
	void			setChromosome(Chromosome::Ptr chromo){ m_chromosome = chromo; };

private:
	Chromosome::Ptr m_chromosome;
};

