// FirstCppProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>  
#include "Sales_item.h"
#include <string>
#include <cstdlib>
using namespace std;

bool isTrue;
char squence;
wchar_t widthSquence;
char16_t str;
char32_t str1;
unsigned short count;
unsigned int sum;
unsigned long sum1;
unsigned long long sum2;
float sum3;
double sum4;
long double sum5;
unsigned char char1;
signed char char2;

int units_sold = 0;
int units_sold = { 0 };
int units_sold{ 0 };
int units_sold( 0 );

extern int i; // 声明i
int j;  //声明并定义j
extern double pi = 3.1416; //定义pi

int ival = 24;
int &refVal = ival; //refVal 指向ival

int *ip1, *ip2; //指针ip1 , ip2 ;
int ival = 24;
int *p = &ival; //p是指向变量ival的指针

int *p1 = nullptr;
int *p2 = 0;
int *p3 = NULL; //必须 #include <cstdlib>

int i = 42;
int *pi1 = 0;
int *pi2 = &i;
int *pi3 = pi2; // 现在指针pi3 和 pi2 都指向i

double obj = 3.14 , *pd = &obj;
void *pv = &obj;

int foo() {
	int ival = 1024;
	int *pi = &ival; // 指针pi 指向 引用ival
	int **ppi = &pi; // 指针ppi 指向 指针pi
	int ***pppi = &ppi; // 指针pppi 指向 指针ppi
	return 0;
}

int test() {
	int i = 42;
	int *p;
	int *&r = p;  //r是一个对p指针的引用

	r = &i;  
	r = 0; //可以直接赋值,  表示p指针指向的引用i , i赋值为0
}
 
void testConst() {
	const int ci = 1024;
	const int &ri = ci; // 引用及其对应的对象都是常量
}

int main()
{
	cout << "hello\n";
	string book;
	cin >> book;
	cout << book << endl;
	return 0;
    return 0;
}
