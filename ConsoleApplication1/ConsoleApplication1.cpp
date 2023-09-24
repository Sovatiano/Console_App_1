// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
	// Some code will be here soon)
}

struct Pipe
{
	string name;
	int length;
	int diametr;
	bool is_repairing = false;
};

struct Compress_station
{
	string name;
	int shops_num;
	int busy_shops_num;
	int efficiency;
};
