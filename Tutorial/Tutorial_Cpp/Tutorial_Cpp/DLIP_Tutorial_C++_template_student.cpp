/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* Cpp Tutorial: Template
* Created: 2021-Spring
------------------------------------------------------*/

#include <iostream>

namespace proj_B
{
	//template <typename T1, typename T2, typename T3>
	template <typename T>

	class myNum
	{
	public:
		T val1;
		T val2;
		T val3;

		myNum(T in1, T in2, T in3)
		{
			val1 = in1;
			val2 = in2;
			val3 = in3;
		}
		T sum()
		{
			return val1 + val2 + val3;
		}
		void print()
		{
			//printf("val1 = %d\n", val1); // 이건 무조건 int만 가능하기 때문에 

			std::cout << "val1 = " << val1 << std::endl;
			std::cout << "val2 = " << val2 << std::endl;
			std::cout << "val3 = " << val3 << std::endl;
			std::cout << "sum  = " << sum() << std::endl;
			//std::cout << "dsize= " << sizeof(sum()) << std::endl;
		}
	};
}

using namespace proj_B;


int main(void) {
	
	// ADD CODE HERE
	
	
	// 1) TEMPLATE AS INT 
	myNum<int> mynum1(1, 2, 3);
	// 2) TEMPLATE AS DOUBLE

	myNum<double> mynum2(4.0, 5.0, 6.0);
	// 3) PRINT RESULT


	mynum1.print();
	mynum2.print();


	return 0;
}