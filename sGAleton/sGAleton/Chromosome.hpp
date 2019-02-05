#pragma once

#include <vector>
#include <memory>
#include "Gen.hpp"

class Chromosome
{
public:
	typedef std::shared_ptr<Chromosome> Ptr;

public:
	Chromosome();
	~Chromosome();

private:
	std::vector<Gen::Ptr> m_genes;
};

