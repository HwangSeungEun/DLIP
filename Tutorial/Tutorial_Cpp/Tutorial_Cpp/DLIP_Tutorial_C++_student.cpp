#include "TU_DLIP.h"

#include <iostream>

int main()
{

	// =============================
	// Exercise 1 :: Define Function
	// =============================

	MyNum mynum; 
	mynum.num = 10;
	

	MyNum mynum2(20); // 컨스트럭터 재정의는 안된다

	std::cout << mynum.num << std::endl;
	std::cout << mynum.num << std::endl;

	MyNum mynum3(20, 30);

	mynum3.num = 10;
	mynum3.sum_val = mynum3.sum();
	mynum3.print();
		
	// ====================================
	// Exercise 2 :: Create a Class 'myNum'
	// ====================================





	system("pause");
	return 0;
}
