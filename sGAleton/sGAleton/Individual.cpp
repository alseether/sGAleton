#include <string>
#include "Individual.hpp"
#include "Environment.hpp"


Individual::Individual(std::vector<unsigned int> cF, std::vector<unsigned int> cC) :
m_chromosome(cF, cC)
{

}
Individual::Individual() :
m_chromosome()
{

}

Individual::~Individual(){

}

void Individual::setScore(double score){
	m_score = score;
}

void Individual::setScoreAcum(double scoreAcum){
	m_scoreAcum = scoreAcum;
}

void Individual::setAdaptation(double adaptation){
	m_adaptation = adaptation;
}

double Individual::getScore() const{
	return m_score;
}

double Individual::getScoreAcum() const{
	return m_scoreAcum;
}

double Individual::getAdaptation() const{
	return m_adaptation;
}

double Individual::fitness(){
	m_adaptation = m_chromosome.fitness();
	return m_adaptation;
}

Chromosome	Individual::getChromosome() const { 
	return m_chromosome; 
};

void Individual::setChromosome(Chromosome chromo){ 
	m_chromosome = chromo; 
};

std::string Individual::toString() const{
	std::string ret = "";
	unsigned int actualTop = 0;
	unsigned int actualBot = 0;
	unsigned int actualLeft = 0;
	unsigned int actualRight = 0;
	auto cortesF = m_chromosome.getCortesF();
	auto cortesC = m_chromosome.getCortesC();
	unsigned int slices = (cortesF.size() + 1) * (cortesC.size() + 1);
	ret += std::to_string(slices) + "\n";
	
	cortesF.push_back(Environment::getInstance()->getR());
	cortesC.push_back(Environment::getInstance()->getC());


	auto itF = cortesF.begin();
	auto itC = cortesC.begin();


	while (itF != cortesF.end()){
		actualBot = *itF;
		actualLeft = 0;
		itC = cortesC.begin();
		while (itC != cortesC.end()){
			actualRight = *itC;

			ret += std::to_string(actualTop) + " " + std::to_string(actualLeft) + " " + std::to_string(actualBot-1) + " " + std::to_string(actualRight-1) + "\n";

			itC++;
			actualLeft = actualRight;
		}
		itF++;
		actualTop = actualBot;
	}


	return ret;
}