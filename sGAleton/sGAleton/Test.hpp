#pragma once

#include <functional>

class Test{
public:
	Test(unsigned int count) 
		: m_fun(std::bind(&Test::defaultFun, this, std::placeholders::_1)),
		m_count(count)
	{
		
	}

public:

	int exec(double n){
		return m_fun(n);
	}

	void setFun(std::function<int(double)> f){
		m_fun = f;
	}

private:

	int defaultFun(double p){
		return std::floor(p) + m_count;
	}

private:
	std::function<int(double)> m_fun;
	unsigned int m_count;
};