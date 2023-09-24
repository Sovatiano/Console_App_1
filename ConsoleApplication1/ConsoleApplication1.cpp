#include <iostream>
#include <fstream>
using namespace std;

struct Pipe
{
	string name;
	double length = 0;
	double diameter = 0;
	bool is_repairing = false;
};

struct Compress_station
{
	string name;
	int shops_num = 0;
	int busy_shops_num = 0;
	int efficiency = 0;
};

Pipe CreatePipe()
{
	Pipe new_pipe;
	cout << "Type name: ";
	cin >> new_pipe.name;
	cout << "Type length: ";
	cin >> new_pipe.length;
	while (cin.fail() || new_pipe.length <= 0)
	{
		cin.clear();
		cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		cin >> new_pipe.length;
	}
	cout << "Type diameter:";
	cin >> new_pipe.diameter;
	while (cin.fail() || new_pipe.diameter <= 0)
	{
		cin.clear();
		cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		cin >> new_pipe.diameter;
	}
	return new_pipe;
}

Compress_station CreateCS()
{
	Compress_station new_cs;
	cout << "Type name: ";
	cin >> new_cs.name;
	cout << "Type shops amount: ";
	cin >> new_cs.shops_num;
	while (cin.fail() || new_cs.shops_num <= 0)
	{
		cin.clear();
		cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		cin >> new_cs.shops_num;
	}
	cout << "Type efficiency: ";
	cin >> new_cs.efficiency;
	return new_cs;
}

void ShowMenu()
{
	cout << "1. Add pipe" << "\n"
		<< "2. Add CS" << "\n"
		<< "3. Show all objects" << "\n"
		<< "4. Edit Pipe" << "\n"
		<< "5. Edit CS" << "\n"
		<< "6. Save" << "\n"
		<< "7. Load" << "\n"
		<< "0. Exit" << "\n";
}

void PrintPipeInfo(const Pipe& pipe)
{
	string repair_status = "False";
	if (pipe.is_repairing)
	{
		repair_status = "True";
	}
	cout << "--------" << "\n"
		<< "Pipe Name: " << pipe.name << "\n"
		<< "Pipe length: " << pipe.length << "\n"
		<< "Pipe diameter: " << pipe.diameter << "\n"
		<< "Is Reapairing: " << repair_status << "\n";
}

int main()
{
	while (1) {
		ShowMenu();
		int action = 0;
		cin >> action;
		switch (action)
		{
		case 1:
		{
			CreatePipe();
			break;
		}
		case 2:
		{
			CreateCS();
			break;
		}
		}

	}
}

