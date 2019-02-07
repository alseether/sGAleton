#include <iostream>
#include <thread>
#include <vector>

class A{
public:
	A(int n) :
		m_n(n)
	{

	}

	int method() const{
		std::cout << "Enter method: " << m_n << std::endl;
		return m_n;
	}

private:
	int m_n;
};


int main(){
	std::vector<std::thread> v;

	for (int i = 0; i < 10; ++i){
		//std::thread t(foo);
		A a(rand());
		v.emplace_back(&A::method, a);
	}

	for (int i = 0; i < 10; ++i){
		v[i].join();
	}


	return 0;

}