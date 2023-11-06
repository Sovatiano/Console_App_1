#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
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


bool compareByPercentage(const Compress_station& a, const Compress_station& b) {
    return (a.busy_shops_num / a.shops_num) < (b.busy_shops_num / b.shops_num);
}

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
		<< "8. Search" << "\n"
		<< "9. Exit" << "\n";
}

void WriteLog(string action, string obj_name) {
	ofstream fout;
	fout.open("logs.txt", ios::app);
	time_t result = time(0);

	char cur_time[50];
	ctime_s(cur_time, sizeof cur_time, &result);

	fout << action << " " << obj_name << "   " << cur_time;
	fout.close();
}

void ChangePipeStatus(vector<Pipe>& pipes, string pipe_name, bool solo_edit)
{
	bool name_exists = false;
	int ind = -1;
	for (Pipe pipe : pipes) {
		ind++;
		if (pipe.name == pipe_name) {
			name_exists = true;
			pipe.is_repairing = !pipe.is_repairing;
			pipes[ind] = pipe;
			break;
		}
	}
	if (!name_exists) {
		cout << "Wrong name! Try again.\n";
		return;
	}

	if (solo_edit) {
		cout << "Status Changed!\n";
		return;
	}
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
					WriteLog("Пользователь изменил КС", cs_name);
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
					WriteLog("Пользователь изменил КС", cs_name);
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

template <typename T>
bool isNameUnique(const vector<T>& objects, const string& newName) {
	for (const T& obj : objects) {
		if (obj.name == newName) {
			cout << "Name already exists!\n";
			return false;
		}
	}
	return true; // Имя уникально
}

template <typename T>
void ShowAllObjects(const vector<T>& objects)
{
	for (const T& obj : objects) {
			cout << obj;
	}
}

void EditCS(vector<Compress_station> &stations) {
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
		cout << "Type correct acton: ";
		getline(cin, action);
	}
	cout << "Type amount of shops you want to edit: ";
	getline(cin, shops_num);
	while (!is_number(shops_num) || cin.fail() || stoi(shops_num) <= 0)
	{
		cin.clear();
		cout << "Type correct info: ";
		getline(cin, shops_num);
	}
	if (action == "activate") {
		EditShops(stations, cs_name, true, stoi(shops_num));
	}
	else {
		EditShops(stations, cs_name, false, stoi(shops_num));
	}
}

void SaveAll(vector<Compress_station>& stations, vector<Pipe>& pipes) {
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
}

void LoadAll(vector<Compress_station>& stations, vector<Pipe>& pipes) {
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
}

vector <Pipe> SearchPipes(vector<Pipe>& pipes) {
	string filter;
	vector <Pipe> result;
	cout << "Search by (name/status): ";
	getline(cin, filter);
	if (filter == "") {
		getline(cin, filter);
	}

	while (filter != "name" && filter != "status")
	{
		cin.clear();
		cout << "Type correct filter: ";
		getline(cin, filter);
	}

	if (filter == "name") {
		cout << "Type pipe name: ";
		string pipe_name;
		getline(cin, pipe_name);
		cout << "Search result:\n\n";
		bool found_sth = false;
		for (Pipe pipe : pipes) {
			if (pipe.name == pipe_name) {
				found_sth = true;
				cout << pipe;
				result.push_back(pipe);
			}
		}
		if (!found_sth) {
			cout << "Couldnt find anything by your filters.\n\n";
		}
	}

	if (filter == "status") {
		string status;
		cout << "Search is repairing (true/false): ";
		getline(cin, status);
		if (status == "") {
			getline(cin, status);
		}

		while (status != "true" && status != "false")
		{
			cin.clear();
			cout << "Type correct status: ";
			getline(cin, status);
		}

		bool search_by_status;
		if (status == "true") {
			search_by_status = true;
		}
		else {
			search_by_status = false;
		}
		cout << "Search result:\n\n";
		bool found_sth = false;
		for (Pipe pipe : pipes) {
			if (pipe.is_repairing == search_by_status) {
				found_sth = true;
				cout << pipe;
				result.push_back(pipe);
			}
		}
		if (!found_sth) {
			cout << "Couldnt find anything by your filters.\n\n";
		}
	}

	return result;
}

void Search(vector<Compress_station> stations, vector<Pipe>& pipes) {
	string object;
	cout << "What object do you want to find (pipe/cs): ";
	getline(cin, object);
	if (object == "") {
		getline(cin, object);
	}

	while (object != "pipe" && object != "cs")
	{
		cin.clear();
		cout << "Type correct object: ";
		getline(cin, object);
	}

	if (object == "pipe") {
		vector<Pipe> result = SearchPipes(pipes);
		if (result.size() != 0) {
			string answer;
			cout << "Change status (y/n): ";
			getline(cin, answer);
			while (answer != "y" && answer != "n")
			{
				cin.clear();
				cout << "Type correct filter: ";
				getline(cin, answer);
			}
			if (answer == "y") {
				for (Pipe pipe : result) {
					ChangePipeStatus(pipes, pipe.name, false);
				}
				cout << "Status Changed!\n";
				return;
			}
		}
	}

	if (object == "cs") {
		string filter;
		cout << "Search by (name/shops): ";
		getline(cin, filter);
		if (filter == "") {
			getline(cin, filter);
		}

		while (filter != "name" && filter != "shops")
		{
			cin.clear();
			cout << "Type correct filter: ";
			getline(cin, filter);
		}

		if (filter == "name") {
			cout << "Type cs name: ";
			string cs_name;
			getline(cin, cs_name);
			cout << "Search result:\n\n";
			bool found_sth = false;
			for (Compress_station cs : stations) {
				if (cs.name == cs_name) {
					found_sth = true;
					cout << cs;
				}
			}
			if (!found_sth) {
				cout << "Couldnt find anything by your filters.\n\n";
			}
		}
		else {
			sort(begin(stations), end(stations), compareByPercentage);
			cout << "Sorted by active shops precantage:\n\n";
			for (Compress_station cs: stations) {
				cout << cs;
			}
		}
	}
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
			if (isNameUnique(pipes, new_pipe.name)) {
				pipes.push_back(new_pipe);
			}
			WriteLog("Пользователь создал трубу", new_pipe.name);
			break;
		}
		case 2:
		{
			Compress_station new_cs;
			cin >> new_cs;
			if (isNameUnique(stations, new_cs.name)) {
				stations.push_back(new_cs);
			}
			WriteLog("Пользователь создал КС", new_cs.name);
			break;
		}
		case 3:
		{
			cout << "Pipes:\n\n";
			ShowAllObjects(pipes);
			cout << "Compress Stations:\n\n";
			ShowAllObjects(stations);
			cout << "\n";
			break;
		}
		case 4:
		{
			string pipe_name = "";
			cout << "Type pipe name: ";
			getline(cin, pipe_name);
			ChangePipeStatus(pipes, pipe_name, true);
			WriteLog("Пользователь изменил трубу", pipe_name);
			break;

		}
		case 5:
		{
			EditCS(stations);
			break;
		}
		case 6:
		{
			SaveAll(stations, pipes);
			break;
		}
		case 7:
		{
			LoadAll(stations, pipes);
			break;
		}
		case 8:
		{
			Search(stations, pipes);
			break; 
		}
		case 9:
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

