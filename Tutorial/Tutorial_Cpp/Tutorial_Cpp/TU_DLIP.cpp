#include "TU_DLIP.h"

#include <iostream>

// =============================
// Exercise 1 :: Define Function
// =============================

int sum(int val1, int val2)
{
	return val1 + val2;
}

// ====================================
// Exercise 2 :: Create a Class ��myNum��
// ====================================


// �������� ���� ������ ���ش�
MyNum::MyNum() {}

MyNum::MyNum(int x) {
	num = x;
}


MyNum::MyNum(int x1, int x2)
{
	val1 = x1;
	val2 = x2;
}

//MyNum::MyNum(int val1, int val2, int val3) {





//}

int MyNum::sum(void)
{
	return val1 + val2;
}

// ???????????????
void MyNum::print(void)
{
	std::cout << "num: \t" << num << std::endl;
	std::cout << "val1: \t" << val1 << std::endl;
	std::cout << "val2: \t" << val2 << std::endl;
	std::cout << "sum: \t " << sum() << std::endl; // ���� Ŭ���� �ȿ� �ִ� return�� �ٷ� ����� �����ϴ�
		
}










