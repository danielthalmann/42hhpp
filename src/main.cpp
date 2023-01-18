#include <iostream>

//#include <ErrorPage.hpp>

int main(int ac, char** av) {
	if (ac < 1 || ac > 2)
	{
		std::cout << "error arguments" << std::endl;
		return(1);
	}
	std::cout << "run HHPP" << std::endl;
//	ErrorPage ep;


//	(void)ep;
	(void)av;
	return (0);
}
