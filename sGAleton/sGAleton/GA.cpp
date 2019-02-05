#include "GA.hpp"

using namespace std::placeholders;

GA::GA() :
m_selection(std::bind(&GA::defaultSelection, this, _1, _2)),
m_crossover(std::bind(&GA::defaultCrossover, this, _1, _2, _3)),
m_mutation(std::bind(&GA::defaultMutation, this, _1, _2))
{
	
}

GA::~GA()
{

}

Individual::Ptr GA::run(Parameters param){
	return nullptr;
}

void GA::initializePopulation(Parameters param){

}

GA::tPopulation GA::defaultSelection(GA::tPopulation pop, Parameters param){
	return std::vector<Individual::Ptr>();
}

Individual::Ptr GA::defaultCrossover(Individual::Ptr dad, Individual::Ptr mom, Parameters param){
	return nullptr;
}

Individual::Ptr GA::defaultMutation(Individual::Ptr child, Parameters param){
	return nullptr;
}
