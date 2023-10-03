#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Pipe
{
	string name;
	double length = 0;
	int diameter = 0;
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
	cin.ignore(1, '\n');
	string name;
	getline(cin, name);
	new_pipe.name = name;
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
			break;
		}
	}
	if (!name_exists) {
		cout << "Wrong name! Try again.\n";
		return;
	}
	cout << "Status Changed!\n";
}

void EditShops(vector<Compress_station>& stations, string cs_name, bool action, int shops_num)
{
	bool name_exists = false;
	bool num_correct = false;
	int ind = -1;
	for (Compress_station cs : stations) {
		ind++;
		if (cs.name == cs_name) {
			name_exists = true;
			if (action) {
				if (shops_num <= cs.shops_num - cs.busy_shops_num)
				{
					cs.busy_shops_num += shops_num;
					num_correct = true;
					stations[ind] = cs;
					cout << "Status Changed!\n";
				}
				break;
			}
			else {
				if (shops_num <= cs.busy_shops_num)
				{
					cs.busy_shops_num -= shops_num;
					num_correct = true;
					stations[ind] = cs;
					cout << "Status Changed!\n";
				}
				break;
			}
		}
	}
	if (!name_exists) {
		cout << "Wrong name! Try again.\n";
		return;
	}

	if (!num_correct) {
		cout << "Invalid shops amount! Try again. \n";
	}
}

void SavePipe(ofstream& fout, const Pipe& pipe)
{
	fout << pipe.name << "\n"
		<< pipe.length << "\n"
		<< pipe.diameter << "\n"
		<< pipe.is_repairing << "\n";
}

void SaveCS(ofstream& fout, const Compress_station& cs)
{
	fout << cs.name << "\n"
		<< cs.shops_num << "\n"
		<< cs.busy_shops_num << "\n"
		<< cs.efficiency << "\n";
}

bool is_digit(const std::string& s)
{
	for (int ind = 0; ind < s.length(); ind++)
	{
		if (ind == 0) {
			if (!isdigit(s[ind])) {
				return false;
			}

		}
		else {
			if (!isdigit(s[ind]) && s[ind] != '.') {
				return false;
			}
		}
	}
	return true;
}

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

Pipe LoadPipe(ifstream& fin, string name) {
	Pipe pipe;
	pipe.name = name;
	string pipe_length;
	getline(fin, pipe_length);
	pipe.length = stof(pipe_length);
	string pipe_diameter;
	getline(fin, pipe_diameter);
	pipe.diameter = stoi(pipe_diameter);
	string pipe_status;
	getline(fin, pipe_status);
	pipe.is_repairing = stoi(pipe_status);
	return pipe;
}

Compress_station LoadStation(ifstream& fin, string name) {
	Compress_station station;
	station.name = name;
	string shops;
	getline(fin, shops);
	station.shops_num = stoi(shops);
	string busy_shops;
	getline(fin, busy_shops);
	station.busy_shops_num = stoi(busy_shops);
	string efficiency;
	getline(fin, efficiency);
	station.efficiency = stoi(efficiency);
	return station;
}

istream& operator >> (istream& in, Compress_station& new_cs)
{
	cout << "Type name: ";
	//cin.ignore(1, '\n');
	string name;
	getline(cin, name);
	new_cs.name = name;
	cout << "Type shops amount: ";
	string shops_num;
	getline(cin, shops_num);
	while (!is_number(shops_num) || stoi(shops_num) <= 0)
	{
		cin.clear();
		//cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		cin >> shops_num;
	}
	new_cs.shops_num = stoi(shops_num);
	cout << "Type efficiency: ";
	string efficiency;
	getline(cin, efficiency);
	if (efficiency == "") {
		getline(cin, efficiency);
	}
	while (!is_number(efficiency) || stoi(efficiency) <= 0)
	{
		cin.clear();
		//cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		getline(cin, efficiency);
	}
	new_cs.efficiency = stoi(efficiency);
	return in;
}

ostream& operator << (ostream& out, const Compress_station& cs)
{
	out
		<< "CS Name: " << cs.name << "\n"
		<< "Overall shops: " << cs.shops_num << "\n"
		<< "Busy shops: " << cs.busy_shops_num << "\n"
		<< "Efficiency: " << cs.efficiency << "\n"
		<< "--------" << "\n";
	return out;
}

istream& operator >> (istream& in, Pipe& new_pipe)
{
	cout << "Type name: ";
	//cin.ignore(1, '\n');
	string name;
	getline(cin, name);
	new_pipe.name = name;
	cout << "Type length: ";
	string length;
	getline(cin, length);
	while (!is_digit(length) || stof(length) <= 0)
	{
		cin.clear();
		//cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		getline(cin, length);
	}
	new_pipe.length = stof(length);
	cout << "Type diameter: ";
	string diameter;
	getline(cin, diameter);
	while (!is_number(diameter) || stoi(diameter) <= 0)
	{
		cin.clear();
		//cin.ignore(int(pow(10, 6)), '\n');
		cout << "Type correct info (>0): ";
		getline(cin, diameter);
	}
	new_pipe.diameter = stoi(diameter);
	return in;
}

ostream& operator << (ostream& out, const Pipe& pipe)
{
	string repair_status = "False";
	if (pipe.is_repairing)
	{
		repair_status = "True";
	}
	out
		<< "Pipe Name: " << pipe.name << "\n"
		<< "Pipe length: " << pipe.length << "\n"
		<< "Pipe diameter: " << pipe.diameter << "\n"
		<< "Is Reapairing: " << repair_status << "\n"
		<< "--------" << "\n";
	return out;
}

int main()
{
	vector <Pipe> pipes;
	vector <Compress_station> stations;
	while (1) {
		ShowMenu();
		string action = "";
		cout << "Type number (1-8): ";
		getline(cin, action);
		while (!is_number(action) && action != "") {
			cout << "Wrong action, type again: ";
			getline(cin, action);
		}
		switch (stoi(action))
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
			cout << "Pipes:\n\n";
				for (Pipe pipe : pipes) {
					cout << pipe;
				}
				cout << "Compress Stations:\n\n";
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
			getline(cin, pipe_name);
			ChangePipeStatus(pipes, pipe_name);
			break;

		}
		case 5:
		{
			string cs_name = "";
			string action = "";
			string shops_num = "";
			cout << "Type station name: ";
			getline(cin, cs_name);
			cout << "Type action (activate/disable): ";
			getline(cin, action);
			if (action == "") {
				getline(cin, action);
			}
			while (action != "activate" && action != "disable")
			{
				cin.clear();
				//cin.ignore(int(pow(10, 6)), '\n');
				cout << "Type correct acton: ";
				getline(cin, action);
			}
			cout << "Type amount of shops you want to edit: ";
			getline(cin, shops_num);
			while (!is_number(shops_num) || cin.fail() || stoi(shops_num) <= 0)
			{
				cin.clear();
				//cin.ignore(int(pow(10, 6)), '\n');
				cout << "Type correct info: ";
				getline(cin, shops_num);
			}
			if (action == "activate") {
				EditShops(stations, cs_name, true, stoi(shops_num));
				break;
			}
			EditShops(stations, cs_name, false, stoi(shops_num));
			break;
		}
		case 6:
		{
			ofstream fout;
			fout.open("data.txt", ios::out);
			fout << "Pipes:\n";
			if (fout.is_open())
			{
				for (Pipe pipe : pipes)
				{
					SavePipe(fout, pipe);
				}
			}
			fout << "CompressStations:\n";
			if (fout.is_open())
			{
				for (Compress_station cs : stations)
				{
					SaveCS(fout, cs);
				}
			}
			fout.close();
			break;
		}
		case 7:
		{
			ifstream fin;
			fin.open("data.txt", ios::in);
			bool stations_part = false;
			bool pipes_part = false;
			pipes.clear();
			stations.clear();
			if (fin.is_open()) {
				while (1) {
					string str;
					getline(fin, str);
					if (str == "Pipes:") {
						pipes_part = true;
					}
					else if (str == "CompressStations:") {
						stations_part = true;
						pipes_part = false;
					}
					else if (pipes_part && str != "") {
						pipes.push_back(LoadPipe(fin, str));
					}
					else if (stations_part && str != "") {
						stations.push_back(LoadStation(fin, str));
					}
					else if (str == "") {
						break;
					}
				}
			}
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

