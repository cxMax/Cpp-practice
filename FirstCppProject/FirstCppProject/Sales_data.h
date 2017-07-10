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


	Sales_data add() {
		return Sales_data();
	}

	class Screen
	{
	public:
		typedef std::string::size_type pos;
	private:
		pos cursor = 0;
		pos height = 0 , width = 0;
		std::string contents;
	};


public:
	Sales_data();
	~Sales_data();
};

