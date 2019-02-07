#pragma once
#include <vector>
#include "Individual.hpp"
#include "Operators.h"
#include "Parameters.hpp"


typedef std::vector<std::vector<char>> tPizza;
typedef std::vector<Individual> tPopulation;


class Environment
{
public:
	static Environment* getInstance(void);

	static void freeInstance(void);

	virtual ~Environment(){ ; };

	unsigned int getR(){ return R; };
	unsigned int getC(){ return C; };
	unsigned int getL(){ return L; };
	unsigned int getH(){ return H; };

	const tPizza* getPizza(){ return &pizza; };

	Parameters getParameters(){ return parameters; };

	void setR(unsigned int r){ R = r; };
	void setC(unsigned int c){ C = c; };
	void setL(unsigned int l){ L = l; };
	void setH(unsigned int h){ H = h; };

	void setPizza(tPizza p){ pizza = p; };

	void setParameters(Parameters p){ parameters = p; };

private:

	unsigned int R;
	unsigned int C;
	unsigned int L;
	unsigned int H;

	tPizza pizza;

	Parameters parameters;

	static Environment*	m_theInstance;

	Environment()
	{

	};
};