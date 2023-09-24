#include <iostream>
#include <fstream>
#include <vector>
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
		<< "8. Exit" << "\n";
}

void ChangePipeStatus(vector<Pipe>& pipes, string pipe_name)
{
	bool name_exists = false;
	int ind = -1;
	for (Pipe pipe : pipes) {
		ind++;
		if (pipe.name == pipe_name) {
			name_exists = true;
			if (pipe.is_repairing) {
				pipe.is_repairing = false;
				break;
			}
			pipe.is_repairing = true;
			pipes[ind] = pipe;
		}
	}
	if (!name_exists) {
		cout << "Wrong name! Try again.\n";
	}
	cout << "Status Changed!\n";
}

istream& operator >> (istream& in, Compress_station& new_cs)
{
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
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info: ";
		cin >> new_cs.efficiency;
	}
	return in;
}

ostream& operator << (ostream& out, const Compress_station& cs)
{
	out << "--------" << "\n"
		<< "CS Name: " << cs.name << "\n"
		<< "Overall shops: " << cs.shops_num << "\n"
		<< "Busy shops: " << cs.busy_shops_num << "\n"
		<< "Efficiency: " << cs.efficiency << "\n";
	return out;
}

istream& operator >> (istream& in, Pipe& new_pipe)
{
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
	cout << "Type diameter: ";
	cin >> new_pipe.diameter;
	while (cin.fail() || new_pipe.diameter <= 0)
	{
		cin.clear();
		cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		cin >> new_pipe.diameter;
	}
	return in;
}

ostream& operator << (ostream& out, const Pipe& pipe)
{
	string repair_status = "False";
	if (pipe.is_repairing)
	{
		repair_status = "True";
	}
	out << "--------" << "\n"
		<< "Pipe Name: " << pipe.name << "\n"
		<< "Pipe length: " << pipe.length << "\n"
		<< "Pipe diameter: " << pipe.diameter << "\n"
		<< "Is Reapairing: " << repair_status << "\n";
	return out;
}

int main()
{
	vector <Pipe> pipes;
	vector <Compress_station> stations;
	while (1) {
		ShowMenu();
		int action = 0;
		cout << "Type number (1-8): ";
		cin >> action;
		switch (action)
		{
		case 1:
		{
			Pipe new_pipe;
			cin >> new_pipe;
			bool name_exists = false;
			for (Pipe pipe : pipes) {
				if (pipe.name == new_pipe.name) {
					cout << "Name already exists!\n";
					name_exists = true;
					break;
				}
			}
			if (!name_exists) {
				pipes.push_back(new_pipe);
			}
			break;
		}
		case 2:
		{
			Compress_station new_cs;
			cin >> new_cs;
			bool name_exists = false;
			for (Compress_station cs : stations) {
				if (cs.name == new_cs.name) {
					cout << "Name already exists!\n";
					name_exists = true;
					break;
				}
			}
			if (!name_exists) {
				stations.push_back(new_cs);
			}
			break;
		}
		case 3:
		{
			cout << "Pipes:\n";
				for (Pipe pipe : pipes) {
					cout << pipe;
				}
				cout << "----------\n"
				<< "Compress Stations:\n";
				for (Compress_station cs : stations) {
					cout << cs;
				}
				cout << "\n";
				break;
		}
		case 4:
		{
			string pipe_name = "";
			cout << "Type pipe name: ";
			cin >> pipe_name;
			ChangePipeStatus(pipes, pipe_name);
			break;

		}
		case 8:
		{
			return 0;
		}
		default:
		{
			cout << "Wrong action!\n";
			cin.clear();
			cin.ignore(int(pow(10, 6)), '\n');
		}
		}

	}
}

