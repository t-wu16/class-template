#include"Table.h"

//初始化
Table::Table(int my_number, State my_state) {
	number = my_number;
	state = my_state;

}

//设置结账，初始化餐桌
void Table::setCheckOut() {
	checkOut = 1;
	state = unoccupied;
}