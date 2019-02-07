#include "Environment.hpp"

Environment* Environment::m_theInstance = 0;

Environment* Environment::getInstance(void)
{
	if (!m_theInstance){

		m_theInstance = new Environment();
	}
	return m_theInstance;
}

void Environment::freeInstance(void)
{
	if (m_theInstance){

		delete m_theInstance;
		m_theInstance = 0;
	}
}