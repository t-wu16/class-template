#ifndef CUSTOMER_H
#define CUSTOMER_H
#include"Table.h"
#include<iostream>
using namespace std;
class Customer {
public:
	void setId(string my_id);				//注册账号
	void setTable(int my_table_number);		//选择餐桌
	void orderDishes();			//点菜与下单：餐桌的点菜列表，
								//顾客查看菜单，选择菜品添加到点菜列表
	void checkOut();			//结账：顾客可以选择是否结账
private:
	string Id;
	int Table_number;
	Table table;
};
#endif // !CUSTOMER_H

