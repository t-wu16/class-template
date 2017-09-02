//餐桌类
#ifndef TABLE_H
#define TABLE_H
#include<vector>
#include<iostream>
using namespace std;
typedef vector<string> Dishes;
enum State {unoccupied,order,ready};//餐桌的状态：空闲，点菜中，已下单

class Table {
public:
	Table() {}
	Table(int my_number, State my_state);					//初始化
	void setNumber(int my_number) { number = my_number; }	//设置餐桌号
	void setState(State my_state) { state = my_state; }		//设置餐桌状态
	void setCheckOut();										//设置结账
private:
	int number;		    //餐桌号
	State state;		//餐桌状态
	Dishes dishes;		//点菜列表
	int checkOut=0;		//是否结账
};
#endif

