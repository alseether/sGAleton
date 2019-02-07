#include "Chromosome.hpp"
#include "Environment.hpp"

Chromosome::Chromosome(std::vector<unsigned int> cF, std::vector<unsigned int> cC) :
	m_cortesF(cF),
	m_cortesC(cC),
	modifiedSinceLastFitness(true)
{

}

Chromosome::Chromosome() :
	modifiedSinceLastFitness(true)
{
	unsigned int R = Environment::getInstance()->getR();
	unsigned int C = Environment::getInstance()->getC();

	// Each row-cut can be equaly inserted or not
	for (unsigned int i = 1; i < R; ++i){
		if (rand() % 2){
			m_cortesF.push_back(i);
		}
	}
	// Same for column-cuts
	for (unsigned int i = 1; i < C; ++i){
		if (rand() % 2){
			m_cortesC.push_back(i);
		}
	}
}

Chromosome::~Chromosome()
{

}

double Chromosome::fitness(){
	if (!modifiedSinceLastFitness){
		return lastfitness;
	}

	unsigned int fitness = 0;
	unsigned int actualTop = 0;
	unsigned int actualBot = Environment::getInstance()->getR();
	unsigned int actualLeft = 0;
	unsigned int actualRight = Environment::getInstance()->getC();

	// Meto al final los bordes derecho y de abajo, para que se calculen los ultimos trozos,
	// luego estos se sacan de los arrays
	m_cortesF.push_back(Environment::getInstance()->getR());
	m_cortesC.push_back(Environment::getInstance()->getC());


	auto itF = m_cortesF.begin();
	auto itC = m_cortesC.begin();


	while (itF != m_cortesF.end()){
		actualBot = *itF;
		actualLeft = 0;
		itC = m_cortesC.begin();
		while (itC != m_cortesC.end()){
			actualRight = *itC;

			fitness += sliceScore(Slice{ actualTop, actualBot, actualLeft, actualRight });

			itC++;
			actualLeft = actualRight;
		}
		itF++;
		actualTop = actualBot;
	}

	modifiedSinceLastFitness = false;
	lastfitness = fitness;

	// Saco los bordes
	m_cortesF.pop_back();
	m_cortesC.pop_back();

	return fitness;
}

std::vector<unsigned int> Chromosome::getCortesF() const{
	return m_cortesF;
}

std::vector<unsigned int> Chromosome::getCortesC() const{
	return m_cortesC;
}

int Chromosome::sliceScore(Slice s) const{
	tPizza pizza = *(Environment::getInstance()->getPizza());
	unsigned int tom = 0, mush = 0;

	unsigned int L = Environment::getInstance()->getL();

	if (s.getArea() > Environment::getInstance()->getH()){
		return 0;
	}

	for (unsigned int i = s.top; i < s.bottom; ++i){
		for (unsigned int j = s.left; j < s.right; ++j){
			if (pizza[i][j] == 'T'){
				tom++;
			}
			else if (pizza[i][j] == 'M'){
				mush++;
			}
			if (tom >= L && mush >= L){
				return s.getArea();
			}
		}
	}

	return 0;
}