#pragma once

#include <memory>

class Gen
{
public:
	typedef std::shared_ptr<Gen> Ptr;
public:
	Gen();
	~Gen();

private:
	unsigned int a;
};

