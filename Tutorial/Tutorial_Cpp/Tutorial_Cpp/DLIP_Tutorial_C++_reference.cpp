#include <iostream>

// case 1
//void swap(int a, int b);

// case 2, 3
//void swap(int *a, int *b);

//// case 4
void swap(int& a, int& b);

int main()
{
	int val1 = 10;
	int val2 = 20;

	printf("Before\n");
	printf("val1:: %d\n", val1);
	printf("val2:: %d\n", val2);

	// case 1, 3, 4
	swap(val1, val2);

	//casae 2
	//swap(&val1, &val2);

	printf("After\n");
	printf("val1:: %d\n", val1);
	printf("val2:: %d\n", val2);
	return 0;
}

// case 1
//void swap(int a, int b)
//{
//	int temp = a;
//	a = b;
//	b = temp;
//}

// case 2, 3
//void swap(int* a, int* b)
//{
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}

// case 4
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}