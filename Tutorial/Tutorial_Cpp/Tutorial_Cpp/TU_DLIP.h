#ifndef _TU_DLIP_H		// same as "#if !define _TU_DLIP_H" (or #pragma once) 
#define _TU_DLIP_H

#include <iostream>

// =============================
// Exercise 1 :: Define Function
// =============================

int sum(int val1, int val2);


// ====================================
// Exercise 2 :: Create a Class ‘myNum’
// ====================================


class MyNum
{
private:		// 다른 곳에서 참조 못한다


public:					// 다른 곳에서 참조 한다
	MyNum();			// 컨스트럭터 --> 바로 실행? 공부해야겠다  이름이 항상 class와 같아야 한다 아무 기능이 없다

	MyNum(int x);		// return type이 없다
	MyNum(int x1, int x2);
	int sum(void);
	void print(void);


	int num;
	int val1, val2;
	int sum_val;

};









#endif // !_TU_DLIP_H