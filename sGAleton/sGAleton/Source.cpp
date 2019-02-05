#include <iostream>
#include "Test.hpp"

int otherFun(double p){
	return std::ceil(p);
}

class MyTest{
public:
	MyTest(unsigned int count) :
		m_count(count)
	{

	}

	int superCeil(double p){
		return std::ceil(p+1) + m_count;
	}

private:
	unsigned int m_count;
};
/*
int main(){
	Test test1(1);
	std::cout << test1.exec(5.4) << std::endl;

	Test test2(2);
	using namespace std::placeholders;
	test2.setFun(&otherFun);
	std::cout << test2.exec(5.4) << std::endl;

	MyTest myTest(9);
	Test test3(3);
	std::function<int(double)> f = std::bind(&MyTest::superCeil, myTest, _1);
	test3.setFun(f);
	std::cout << test3.exec(5.4) << std::endl;

	return 0;

}
*/