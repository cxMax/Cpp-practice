// FirstCppProject.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>  
#include "Sales_data.h"
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
using std::cin;

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

void testConst1() {
	const double pi = 3.15;
	const double *ptr = &pi;  //ָ��ָ��һ��const����, ����Ҳ������const
}

void testConst() {
	int errNum = 9;
	int *const curErr = &errNum;  // curErr ��һֱָ�� errNum
	const double pi = 3.14;
	const double *const pip = &pi; // pip��һ��һֱָ��������ĳ���ָ��
}

void testConst() {
	int i = 0;
	int *const pl = &i; // ����һ������const , ���ܸı�p1��ֵ
	const int ci = 42; // ����һ������const , ���ܸı�ci��ֵ
	const int *p2 = &ci; // ����һ���ײ�const , ����ı�p2��ֵ
}

void testConst() {
	const int max_files = 20; //�������ʽ
	const int limit = max_files + 1; //�������ʽ
}

void testConst() {
	constexpr int mf = 20;
	constexpr int limit = mf + 1;
}

void testConst() {
	const int *p = nullptr; //p��һ��ָ�����ͳ�����ָ��
	constexpr int *q = nullptr; //q��һ��ָ��֤��ĳ���ָ��
}

void testAlias() {
	typedef double wages; //wages �� double ��ͬ���
	typedef wages bas, *p; // bas �� double ��ͬ��� , p �� double* ��ͬ���
	using SI = Sales_data;  // SI �� Sales_item ��ͬ���

	typedef char *pstring;
	const pstring cstr = 0; //cstr��ָ��char�ĳ���ָ��
	const pstring *ps; // ps��һ��ָ�� , ���Ķ�����ָ��char�ĳ���ָ��
}

void testAuto() {
	int i = 2; 
	float p = 1.3;
	auto sum = i + p; // auto �Զ��ƶϳ� i + p ������

	const int c1 = i, &cr = c1;
	auto b = c1; // b ��һ������
	auto c = cr; // c ��һ������
	auto d = &i; // d ��һ������ָ��
	auto e = &c1; // e ��һ��ָ������������ָ��
}

void testDecltype() {
	const int ci = 0, &cj = ci;
	decltype(ci) x = 0; // x �������� const int
	decltype(cj) y = x; // y �������� const int& , y �󶨵�����x

	int i = 42, *p = &i, &r = i;
	decltype(r + 0) b; // b����һ�� int����
	decltype(i) e; // e��һ�� int
}

struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

void testSales_data() {
	Sales_data data1, datda2;
	double price = 0;
	cin >> data1.bookNo >> data1.units_sold >> price;
	data1.revenue = data1.units_sold * price;
}

void testinitializeString() {
	string s1;
	string s2 = s1;
	string s3 = "hiya";
	string s4(10, 'c'); // s4 �������� cccccccccc
	string s5 = "hiya";
	string s6("hiya"); //ֱ�ӳ�ʼ��
}

void testReadString() {
	string word;
	while (cin >> word) {
		cout << word << endl
	}

	string line;
	while (getline(cin, line)) {
		if (!line.empty) {
			cout << line << endl
		}
	}
}

void testInitializeVector() {
	vector<string> v1{ "a","b","c","d","e" };
	vector<string> v1(10, "hi"); // �б�����10�� "hi"
}

void testIterator() {
	string s("hello world");
	for (auto it = s.begin; it != s.end && !isspace(*it); ++it) {
		//do something
	}
}

void testIterator() {
	vector<int>::iterator it; //�ɶ�дvector�����Ԫ��
	vector<int>::const_iterator it1; //ֻ�ܶ�

	string::iterator it2; //�ɶ�дstring�е��ַ�
	string::const_iterator it3; //ֻ�ܶ�
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
