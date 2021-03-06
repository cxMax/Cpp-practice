// FirstCppProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>  
#include "Sales_data.h"
#include <string>
#include <cstdlib>
#include <vector>
#include<list>
#include <memory>
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

void testConst1() {
	const double pi = 3.15;
	const double *ptr = &pi;  //指针指向一个const常量, 自身也必须是const
}

void testConst() {
	int errNum = 9;
	int *const curErr = &errNum;  // curErr 将一直指向 errNum
	const double pi = 3.14;
	const double *const pip = &pi; // pip是一个一直指向常量对象的常量指针
}

void testConst() {
	int i = 0;
	int *const pl = &i; // 这是一个顶层const , 不能改变p1的值
	const int ci = 42; // 这是一个顶层const , 不能改变ci的值
	const int *p2 = &ci; // 这是一个底层const , 允许改变p2的值
}

void testConst() {
	const int max_files = 20; //常量表达式
	const int limit = max_files + 1; //常量表达式
}

void testConst() {
	constexpr int mf = 20;
	constexpr int limit = mf + 1;
}

void testConst() {
	const int *p = nullptr; //p是一个指向整型常量的指针
	constexpr int *q = nullptr; //q是一个指向证书的常量指针
}

void testAlias() {
	typedef double wages; //wages 是 double 的同义词
	typedef wages bas, *p; // bas 是 double 的同义词 , p 是 double* 的同义词
	using SI = Sales_data;  // SI 是 Sales_item 的同义词

	typedef char *pstring;
	const pstring cstr = 0; //cstr是指向char的常量指针
	const pstring *ps; // ps是一个指针 , 它的对象是指向char的常量指针
}

void testAuto() {
	int i = 2; 
	float p = 1.3;
	auto sum = i + p; // auto 自动推断出 i + p 的类型

	const int c1 = i, &cr = c1;
	auto b = c1; // b 是一个整数
	auto c = cr; // c 是一个整数
	auto d = &i; // d 是一个整型指针
	auto e = &c1; // e 是一个指向整数常量的指针
}

void testDecltype() {
	const int ci = 0, &cj = ci;
	decltype(ci) x = 0; // x 的类型是 const int
	decltype(cj) y = x; // y 的类型是 const int& , y 绑定到变量x

	int i = 42, *p = &i, &r = i;
	decltype(r + 0) b; // b代表一个 int类型
	decltype(i) e; // e是一个 int
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
	string s4(10, 'c'); // s4 的内容是 cccccccccc
	string s5 = "hiya";
	string s6("hiya"); //直接初始化
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
	vector<string> v1(10, "hi"); // 列表里面10个 "hi"
}

void testIterator() {
	string s("hello world");
	for (auto it = s.begin; it != s.end && !isspace(*it); ++it) {
		//do something
	}
}

void testIterator() {
	vector<int>::iterator it; //可读写vector里面的元素
	vector<int>::const_iterator it1; //只能读

	string::iterator it2; //可读写string中的字符
	string::const_iterator it3; //只能读
}

void testExpression() {
	string s1 = "a string", *p = &s1;
	auto n = s1.size();
	n = (*p).size();
	n = p->size();
}

void testSharedPtr() {
	shared_ptr<string> p1; //指向string
	shared_ptr<list<int>> p2; //指向<list> String
	shared_ptr<int> p3 = make_shared<int>(42); //指向42
	shared_ptr<string> p4 = make_shared<string>(10, "9"); //指向10个9的string
	shared_ptr<int> p5 = make_shared<int>(); // 指向0
	auto p6 = make_shared<vector<string>>(); // p6指向一个动态分配的空vector<string>

	auto p = make_shared<int>(42); // p指向的对象只有一个引用者
	auto q(p); // p 和 q指向相同对象 , 此对象有两个引用者
}

void testManageMemory() {
	int *pi = new int; //pi 指向一个未初始化\动态分配的无名对象
	const int *pci = new const int(1024); //分配并初始化一个const int
	const string *pcs = new const string; // 初始化一个空的string

	int i, *pi1 = &i, *pi2 = nullptr;
	double *pd = new double(32), *pd2 = pd;
	delete pd;  // 操作delete 必须为已初始化的对象
	delete pd2;
	const int *pci = new const int(1024);
	delete pci;
	pci = nullptr; //delete后, 须将nullptr赋予指针, 避免空悬指针

	shared_ptr<int> p2(new int(42)); //初始化shared_ptr
}

void testUniquePtr() {
	unique_ptr<double> p1; // 指向一个double的unique_ptr
	unique_ptr<int> p2(new int(42)); // p2指向一个值为42的int

	unique_ptr<string> p3(new string("haha"));
	unique_ptr<string> p4(p3.release); // release 将p3置为空 ,将所有权从p3转移给p4

	unique_ptr<string> p5(new string("haha"));
	p4.reset(p3.release); // 将所有权从p5转移给p4 , reset 同时释放了p4的资源
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
