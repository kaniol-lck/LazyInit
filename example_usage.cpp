#include "LazyInit/LazyInit.hpp"

#include <iostream>

class WantLazy{
public:
	WantLazy(const int& value) : 
		value_(value)
	{
		std::cout<<"Here the class initialized with value:"<<value_<<std::endl;
	}

	getValue() const
	{
		return value_;
	}

private:
	int value_;
};

int generateValue()
{
	std::cout<<"Here the function generating argument value is invoked."<<std::endl;
	return 7;
}

int main()
{
	std::cout<<"--------Program Start--------"<<std::endl;
	
	std::cout<<"Initialize lazyman with type lazyInit<WantLazy>."<<std::endl;
	LazyInit<WantLazy> lazyman(generateValue());

	std::cout<<"Get value inside WantLazy class."<<std::endl;
	auto lazy = *lazyman;
	auto value = lazy.getValue();
	std::cout<<"The value is:"<<value<<std::endl;
}
