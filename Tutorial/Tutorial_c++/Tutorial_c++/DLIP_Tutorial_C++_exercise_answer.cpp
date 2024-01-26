#include <iostream>

// Function Overloading

double adder(double numln1, double numln2);
double adder(double numln1, double numln2, double numln3);
void add(double numln1, double numln2, double & numOut);

int main()
{
	double num1 = 10.0;
	double num2 = 20.0;
	double num3 = 30.0;

	double numOut1 = adder(num1, num2);
	double numOut2 = adder(num1, num2, num3);
	
	double numOut3;
	add(num1, num2, numOut3);

	std::cout << numOut1 << std::endl;
	std::cout << numOut2 << std::endl;
	std::cout << numOut3 << std::endl;
}

double adder(double numln1, double numln2)
{
	return numln1 + numln2;
}

double adder(double numln1, double numln2, double numln3)
{
	return numln1 + numln2 + numln3;
}

void add(double numln1, double numln2, double & numOut)
{
	numOut = numln1 + numln2;
}