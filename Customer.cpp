#include"Customer.h"

//注册账号（手机号）
void Customer::setId(string my_id) {
	Id = my_id;
}

/*顾客选择餐桌号，设置餐桌对象*/
void Customer::setTable(int my_table_number) {
	table.setNumber(my_table_number);
	table.setState(order);			//选好餐桌后，该餐桌便进入点菜状态
}


//点菜与下单
void Customer::orderDishes() {
	
}

//选择结账
void Customer::checkOut() {
	table.setCheckOut();
}