// FirstCppProject.cpp : �������̨Ӧ�ó������ڵ㡣
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

extern int i; // ����i
int j;  //����������j
extern double pi = 3.1416; //����pi

int ival = 24;
int &refVal = ival; //refVal ָ��ival

int *ip1, *ip2; //ָ��ip1 , ip2 ;
int ival = 24;
int *p = &ival; //p��ָ�����ival��ָ��

int *p1 = nullptr;
int *p2 = 0;
int *p3 = NULL; //���� #include <cstdlib>

int i = 42;
int *pi1 = 0;
int *pi2 = &i;
int *pi3 = pi2; // ����ָ��pi3 �� pi2 ��ָ��i

double obj = 3.14 , *pd = &obj;
void *pv = &obj;

int foo() {
	int ival = 1024;
	int *pi = &ival; // ָ��pi ָ�� ����ival
	int **ppi = &pi; // ָ��ppi ָ�� ָ��pi
	int ***pppi = &ppi; // ָ��pppi ָ�� ָ��ppi
	return 0;
}

int test() {
	int i = 42;
	int *p;
	int *&r = p;  //r��һ����pָ�������

	r = &i;  
	r = 0; //����ֱ�Ӹ�ֵ,  ��ʾpָ��ָ�������i , i��ֵΪ0
}
 
void testConst() {
	const int ci = 1024;
	const int &ri = ci; // ���ü����Ӧ�Ķ����ǳ���
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
