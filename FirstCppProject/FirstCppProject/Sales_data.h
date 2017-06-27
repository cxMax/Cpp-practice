#pragma once
class Sales_data
{
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
	struct Sales_item
	{
		std::string bookNo;
		unsigned units_sold = 0;
		double revenue = 0.0;
	};
#endif // !SALES_DATA_H


public:
	Sales_data();
	~Sales_data();
};

