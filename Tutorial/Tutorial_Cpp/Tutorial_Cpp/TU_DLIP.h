#ifndef _TU_DLIP_H		// same as "#if !define _TU_DLIP_H" (or #pragma once) 
#define _TU_DLIP_H

#include <iostream>

// =============================
// Exercise 1 :: Define Function
// =============================

int sum(int val1, int val2);


// ====================================
// Exercise 2 :: Create a Class ��myNum��
// ====================================


class MyNum
{
private:		// �ٸ� ������ ���� ���Ѵ�


public:					// �ٸ� ������ ���� �Ѵ�
	MyNum();			// ����Ʈ���� --> �ٷ� ����? �����ؾ߰ڴ�  �̸��� �׻� class�� ���ƾ� �Ѵ� �ƹ� ����� ����

	MyNum(int x);		// return type�� ����
	MyNum(int x1, int x2);
	int sum(void);
	void print(void);


	int num;
	int val1, val2;
	int sum_val;

};









#endif // !_TU_DLIP_H