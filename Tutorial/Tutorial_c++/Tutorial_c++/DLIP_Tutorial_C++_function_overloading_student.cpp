
#include <iostream>

namespace proj_B 
{
	template<typename T>
	class myNum 
	{	
		public:
			T val1;
			T val2;
			T val3;
			T sumVal;

			myNum(T in1, T in2, T in3) 
			{
				val1 = in1;
				val2 = in2;
				val3 = in3;
			}

			// ADD CODE HERE

			T sum(T in1, T in2 = 0) {

				sumVal = val1 + val2 + val3 + in1;

				return sumVal;
			}

			T sum(T in1, T in2, T in3) {

				sumVal = val1 + val2 + val3 + in1 + in2 + in3;
				return sumVal;
			}

			void print(void) 
			{
				std::cout << "val1 = " << val1 << std::endl;
				std::cout << "val2 = " << val2 << std::endl;
				std::cout << "val3 = " << val3 << std::endl;
				std::cout << "sum  = " << sumVal << std::endl;
			}
	};
}

int main(void)
{
	proj_B::myNum<int> mynum1(10, 20, 30);
	proj_B::myNum<double> mynum2(0.1, 0.2, 0.3);

	// ADD CODE HERE
	// 1) SUMMATION
	
	mynum1.sum(1);
	mynum2.sum(1.0, 2.0, 3.0);
	
	// 2) PRINT RESULT
	mynum1.print();
	mynum2.print();
	return 0;
}