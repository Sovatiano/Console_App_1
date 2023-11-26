#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <map>
using namespace std;

class Pipe {
public:
	Pipe()
		: name("Pipe"), length(0.0), diameter(0), is_repairing(false) {}

	string getName() const {
		return name;
	}

	double getLength() const {
		return length;
	}

	int getDiameter() const {
		return diameter;
	}

	bool isRepairing() const {
		return is_repairing;
	}

	void setName(string newName) {
		name = newName;
	}

	void setLength(double newLength) {
		length = newLength;
	}

	void setDiameter(int newDiam) {
		diameter = newDiam;
	}

	void setStatus(bool value) {
		is_repairing = value;
	}


private:
	string name;
	double length;
	int diameter;
	bool is_repairing;
};

class Compress_station {
public:
	Compress_station()
		: name("CS"), shops_num(0), busy_shops_num(0), efficiency(0) {}

	std::string getName() const {
		return name;
	}

	int getShops_num() const {
		return shops_num;
	}

	int getBusy_shops_num() const {
		return busy_shops_num;
	}

	int getEfficiency() const {
		return efficiency;
	}

	double getBusy() const {
		return  float(busy_shops_num) / float(shops_num) * 100;
	}

	void setName(string newName) {
		name = newName;
	}

	void setShopsNum(int newNum) {
		shops_num = newNum;
	}

	void setBusyShopNum(int newBusy) {
		busy_shops_num = newBusy;
	}

	void setEfficiency(int newEfficiency) {
		efficiency = newEfficiency;
	}

	void EditShops(string action, int shops) {
		if (action == "activate") {
			if (shops <= (shops_num - busy_shops_num)) {
				busy_shops_num += shops;
			}
			else {
				cout << "Invalid shops amount, try again.\n";
			}
		}

		else {
			if (shops <= busy_shops_num) {
				busy_shops_num -= shops;
			}
			else {
				cout << "Invalid shops amount, try again.\n";
			}
		}
	}

private:
	string name;
	int shops_num;
	int busy_shops_num;
	int efficiency;
};

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

class PipeMap {
public:
	void addElement(const Pipe& value) {
		int newKey = getNextKey();
		myMap[newKey] = value;
	}

	void removeElement(int key) {
		myMap.erase(key);
	}

	void clear() {
		myMap.clear();
		int currentKey = 1;
	}
	
	void addDirectly(int key, Pipe& pipe) {
		myMap[key] = pipe;
	}

	int getLastId() {
		return currentKey;
	}

	void setLastId(int id) {
		currentKey = id;
	}

	void printOneElement(int id) {
		auto it = myMap.find(id);

		if (it != myMap.end()) {
			Pipe pair = it->second;
			cout << "Pipe id: " << it->first << "\n"
				<< "Pipe name: " << pair.getName() << "\n"
				<< "Pipe length: " << pair.getLength() << "\n"
				<< "Pipe diameter: " << pair.getDiameter() << "\n"
				<< std::boolalpha
				<< "Pipe repairing: " << pair.isRepairing() << "\n"
				<< std::noboolalpha
				<< "----------------\n";
		}
		else {
			std::cerr << "Pipe with id " << id << " not found." << std::endl;
			return;
		}
	}

	void printElements() const {
		cout << "Pipes:\n";
		for (const auto& pair : myMap) {
			cout << "Pipe id: " << pair.first << "\n"
				<< "Pipe name: " << pair.second.getName() << "\n"
				<< "Pipe length: " << pair.second.getLength() << "\n"
				<< "Pipe diameter: " << pair.second.getDiameter() << "\n"
				<< std::boolalpha
				<< "Pipe repairing: " << pair.second.isRepairing() << "\n"
				<< std::noboolalpha
				<< "----------------\n";
		}
	}

	void saveElements(ofstream& fout) const {
		for (const auto& pair : myMap) {
			fout << pair.first << "\n"
				<< pair.second.getName() << "\n"
				<< pair.second.getLength() << "\n"
				<< pair.second.getDiameter() << "\n"
				<< pair.second.isRepairing() << "\n";
		}
	}

	void loadElements(ifstream& fin, PipeMap& pipes) const {
		string str;
		getline(fin, str);
		if (str == "Pipes:")
		{
			getline(fin, str);
			if (str == "CompressStations:")
			{
				return;
			}
			pipes.setLastId(stoi(str));
			while (true)
			{
				getline(fin, str);
				if (str == "CompressStations:")
				{
					break;
				}
				else {
					string name;
					getline(fin, name);
					string length;
					getline(fin, length);
					string diameter;
					getline(fin, diameter);
					string status;
					getline(fin, status);
					Pipe new_pipe;
					new_pipe.setName(name);
					new_pipe.setLength(stod(length));
					new_pipe.setDiameter(stoi(diameter));
					new_pipe.setStatus(stoi(status));
					pipes.addDirectly(stoi(str), new_pipe);
					continue;
				}
			}
		}

	}

	vector<int> searchElements(string filter) {
		vector<int> result;
		if (filter == "name") {
			string name;
			cout << "Type pipe name to search: ";
			getline(cin, name);
			for (auto& pair : myMap) {
				if (pair.second.getName().find(name) != string::npos) {
					result.push_back(pair.first);
				}
			}
		}

		else {

			string status;
			while (true) {
				cout << "Type filter for search (true/false): ";
				getline(cin, status);
				if (status == "true" or status == "false") {
					break;
				}

				else {
					cout << "Invalid input. Please enter 'true' or 'false'." << std::endl;
				}
			}
			bool bstatus;
			if (status == "true") {
				bstatus = true;
			}
			else {
				bstatus = false;
			}
			for (auto& pair : myMap) {
				if (pair.second.isRepairing() == bstatus) {
					result.push_back(pair.first);
				}
				
			}
		}

		return result;
	}

	map<int, Pipe>::iterator find(int key) {
		return myMap.find(key);
	}

	map<int, Pipe>::iterator end() {
		return myMap.end();
	}

private:
	map<int, Pipe> myMap;
	int currentKey = 1;

	int getNextKey() {
		return currentKey++;
	}
};

class CSMap {
public:
	void addElement(const Compress_station& value) {
		int newKey = getNextKey();
		myMap[newKey] = value;
	}

	void removeElement(int key) {
		myMap.erase(key);
	}

	void clear() {
		myMap.clear();
		currentKey = 1;
	}

	void addDirectly(int key, Compress_station& cs) {
		myMap[key] = cs;
	}

	int getLastId() {
		return currentKey + 1;
	}

	void setLastId(int id) {
		currentKey = id;
	}

	vector<int> searchElements(string filter) {
		vector<int> result;
		if (filter == "name") {
			string name;
			cout << "Type cs name to search: ";
			getline(cin, name);
			for (auto& pair : myMap) {
				if (pair.second.getName().find(name) != string::npos) {
					result.push_back(pair.first);
				}
			}
		}

		else {
			string percent;
			cout << "Type percent (integer) for search: ";
			getline(cin, percent);
			while (true) {
				if (is_digit(percent) && stoi(percent) >= 0) {
					break;
				}
				else {
					cout << "Invalid input. Please enter a positive integer." << endl;
				}
			}

			string parameter;
			while (true) {
				cout << "Type parameter to search (lower/higher): ";
				getline(cin, parameter);
				if (parameter == "lower" or parameter == "higher") {
					break;
				}

				else {
					cout << "Invalid input. Please enter 'higher' or 'lower'." << endl;
				}
			}

			for (auto& pair : myMap)
			{
				if (parameter == "lower") {
					if (pair.second.getBusy() < stoi(percent)) {
						result.push_back(pair.first);
					}
				}
				else {
					if (pair.second.getBusy() > stoi(percent)) {
						result.push_back(pair.first);
					}
				}
			}

		}

		return result;
	}

	void printElements() const {
		cout << "Compress Stations:\n";
		for (const auto& pair : myMap) {
			cout << "CS id: " << pair.first << "\n"
				<< "CS name: " << pair.second.getName() << "\n"
				<< "CS shops amount: " << pair.second.getShops_num() << "\n"
				<< "CS busy shops amount: " << pair.second.getBusy_shops_num() << "\n"
				<< "CS efficiency: " << pair.second.getEfficiency() << "\n"
				<< "----------------\n";
		}
	}

	void printOneElement(int id) {
		auto it = myMap.find(id);

		if (it != myMap.end()) {
			Compress_station pair = it->second;
			cout << "CS id: " << it->first << "\n"
				<< "CS name: " << pair.getName() << "\n"
				<< "CS shops amount: " << pair.getShops_num() << "\n"
				<< "CS busy shops amount: " << pair.getBusy_shops_num() << "\n"
				<< "CS effciency: " << pair.getEfficiency() << "\n"
				<< "----------------\n";
		}
		else {
			std::cerr << "CS with id " << id << " not found." << std::endl;
			return;
		}
	}

	void saveElements(ofstream& fout) const {
		for (const auto& pair : myMap) {
			fout << pair.first << "\n"
				<< pair.second.getName() << "\n"
				<< pair.second.getShops_num() << "\n"
				<< pair.second.getBusy_shops_num() << "\n"
				<< pair.second.getEfficiency() << "\n";
		}
	}

	void loadElements(ifstream& fin, CSMap& stations) const {
		string str;
		getline(fin, str);
		if (str != "")
		{
			stations.setLastId(stoi(str));
			while (true)
			{
				getline(fin, str);
				if (str == "") {
					break;
				}
				Compress_station new_cs;
				string name;
				getline(fin, name);
				new_cs.setName(name);
				string shops_num;
				getline(fin, shops_num);
				new_cs.setShopsNum(stoi(shops_num));
				string busy_shops_num;
				getline(fin, busy_shops_num);
				new_cs.setBusyShopNum(stoi(busy_shops_num));
				string efficiency;
				getline(fin, efficiency);
				new_cs.setEfficiency(stoi(efficiency));
				stations.addDirectly(stoi(str), new_cs);
			}
		}

	}

	map<int, Compress_station>::iterator find(int key) {
		return myMap.find(key);
	}

	map<int, Compress_station>::iterator end() {
		return myMap.end();
	}

private:
	map<int, Compress_station> myMap;
	int currentKey = 1;

	int getNextKey() {
		return currentKey++;
	}
};

Pipe CreatePipe()
{
	string name;
	string length;
	string diameter;

	cout << "Enter pipe name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name);

	while (true) {
		cout << "Enter pipe length: ";
		getline(cin, length);
		if (is_digit(length) && stoi(length) > 0) {
			break;
		}
		else {
			cout << "Invalid input. Please enter a positive integer." << endl;
		}
	}

	while (true) {
		cout << "Enter pipe diameter: ";
		getline(cin, diameter);
		if (is_number(diameter) && stoi(diameter) > 0) {
			break;
		}
		else {
			cout << "Invalid input. Please enter a natural integer." << endl;
		}
	}

	Pipe newPipe;
	newPipe.setName(name);
	newPipe.setLength(stod(length));
	newPipe.setDiameter(stoi(diameter));
	return newPipe;
}

Compress_station CreateCS()
{
	string name;
	int shops_num;
	int busy_shops_num;
	int efficiency;

	cout << "Enter station name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name);

	while (true) {
		cout << "Enter amount of shops: ";
		if (cin >> shops_num && shops_num > 0) {
			break;
		}
		else {
			cout << "Invalid input. Please enter a natural integer." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	while (true) {
		cout << "Enter busy shops amount: ";
		if (cin >> busy_shops_num && busy_shops_num > 0 && busy_shops_num <= shops_num) {
			break;
		}
		else {
			cout << "Invalid input. Please enter a natural integer not higher than the first." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	while (true) {
		cout << "Enter efficiency: ";
		if (cin >> efficiency && efficiency > 0) {
			break;
		}
		else {
			cout << "Invalid input. Please enter a natural integer." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	Compress_station new_cs;
	new_cs.setName(name);
	new_cs.setShopsNum(shops_num);
	new_cs.setBusyShopNum(busy_shops_num);
	new_cs.setEfficiency(efficiency);
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
		<< "9. Delete object" << "\n"
		<< "10. Exit" << "\n";
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

void ChangePipeStatus(PipeMap& pipes, int pipe_id, bool solo_edit)
{
	auto it = pipes.find(pipe_id);

	if (it != pipes.end()) {
		bool current_status = it->second.isRepairing();
		it->second.setStatus(!(current_status));
	}
	else {
		std::cerr << "Pipe with id " << pipe_id << " not found." << std::endl;
		return;
	}

	if (solo_edit) {
		cout << "Status Changed!\n";
		return;
	}
}

void EditCS(CSMap& stations) {
	string action, cs_id, shops;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "Type station id: ";
		getline(cin, cs_id);
		if (is_number(cs_id)) {
			break;
		}
		else {
			cout << "Invalid input. Please enter a valid integer." << endl;
			continue;
		}
	}
	auto it = stations.find(stoi(cs_id));

	if (it != stations.end()) {
		Compress_station& cs = it->second;
		while (true) {
			cout << "Type action (activate/disable): ";
			getline(cin, action);
			if (action == "activate" or action == "disable") {
				break;
				}

			else {
				cout << "Invalid input. Please enter 'activate' or 'disable'." << endl;
			}
		}

		while (true) {
			cout << "Type number of shops to edit: ";
			getline(cin, shops);
			if (is_number(shops) and stoi(shops) > 0) {
				cs.EditShops(action, stoi(shops));
				break;
			}
			else {
				cout << "Invalid input. Please enter a valid integer." << endl;
				continue;
			}
		}
	}
	else {
		std::cerr << "CS with id " << cs_id << " not found." << std::endl;
	}
}

void SaveAll(PipeMap& pipes, CSMap& stations) {
	string file_name;
	cout << "Type save file name:";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();
	getline(cin, file_name);
	while (file_name == "")
	{
		cin.clear();
		cout << "Type correct name: ";
		getline(cin, file_name);
	}
	ofstream fout;
	fout.open(file_name, ios::out);
	fout << "Pipes:\n";
	if (pipes.getLastId() != 1) {
		fout << to_string(pipes.getLastId()) + "\n";
	}
	if (fout.is_open())
	{
		pipes.saveElements(fout);
	}
	fout << "CompressStations:\n";
	if (stations.getLastId() != 1) {
		fout << to_string(stations.getLastId()) + "\n";
	}
	if (fout.is_open())
	{
		stations.saveElements(fout);
	}
	fout.close();
	WriteLog("User saved to file", file_name);
}

void LoadAll(PipeMap& pipes, CSMap& stations) {
	string file_name;
	ifstream fin;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();
	cout << "Type load file name: ";
	getline(cin, file_name);
	fin.open(file_name, ios::in);
	while (!fin.is_open())
	{
		cin.clear();
		cout << "File not found, try again: ";
		getline(cin, file_name);
		fin.open(file_name, ios::in);
	}
	if (fin.is_open()) {
		pipes.loadElements(fin, pipes);
		stations.loadElements(fin, stations);
	}
	fin.close();
	WriteLog("User loaded from file", file_name);
}

void Delete(PipeMap& pipes, CSMap& stations) {
	string object;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "Type object to delete (pipe/cs): ";
		getline(cin, object);
		if (object == "pipe" or object == "cs") {
			break;
		}

		else {
			cout << "Invalid input. Please enter 'pipe' or 'cs'." << std::endl;
		}
	}

	if (object == "pipe") {
		string pipe_id;
		while (true) {
			cout << "Type pipe id: ";
			getline(cin, pipe_id);
			if (is_number(pipe_id)) {
				break;
			}
			else {
				cout << "Invalid input. Please enter a valid integer." << endl;
				continue;
			}
		}
		auto it = pipes.find(stoi(pipe_id));

		if (it != pipes.end()) {
			pipes.removeElement(stoi(pipe_id));
		}

		else {
			cerr << "Pipe with id " << pipe_id << " not found." << endl;
		}
	}

	else {
		string cs_id;
		while (true) {
			cout << "Type cs id: ";
			getline(cin, cs_id);
			if (is_number(cs_id)) {
				break;
			}
			else {
				cout << "Invalid input. Please enter a valid integer." << endl;
				continue;
			}
		}
		auto it = stations.find(stoi(cs_id));

		if (it != stations.end()) {
			stations.removeElement(stoi(cs_id));
		}

		else {
			cerr << "CS with id " << cs_id << " not found." << endl;
		}
	}
}

void SearchPipes(PipeMap& pipes) {
	string filter;
	while (true) {
		cout << "Type filter for search (name/status): ";
		getline(cin, filter);
		if (filter == "name" or filter == "status") {
			break;
		}

		else {
			cout << "Invalid input. Please enter 'name' or 'status'." << std::endl;
		}
	}

	vector<int> result = pipes.searchElements(filter);

	if (size(result) > 0) {

		for (int id : result) {
			cout << "\n";
			pipes.printOneElement(id);
			cout << "\n";
		}
	}
	else {
		cout << "\n Nothing found! \n\n";
		return;
	}

	string decision;
	while (true) {
		cout << "Do you want to change status of found pipes (y/n)?: ";
		getline(cin, decision);
		if (decision == "y" or decision == "n") {
			break;
		}

		else {
			cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
		}
	}

	if (decision == "y") {
		for (int id : result) {
			ChangePipeStatus(pipes, id, false);
		}
		cout << "Status changed!\n";
	}
	return;

}

void SearchCS(CSMap& stations) {
	string filter;
	while (true) {
		cout << "Type filter for search (name/percent): ";
		getline(cin, filter);
		if (filter == "name" or filter == "percent") {
			break;
		}

		else {
			cout << "Invalid input. Please enter 'name' or 'percent'." << std::endl;
		}
	}

	vector<int> result = stations.searchElements(filter);

	if (size(result) > 0) {

		for (int id : result) {
			cout << "\n";
			stations.printOneElement(id);
			cout << "\n";
		}
	}
	else {
		cout << "\n Nothing found! \n\n";
		return;
	}


}

void Search(PipeMap& pipes, CSMap& stations) {
	string object;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "Type object to search (pipe/cs): ";
		getline(cin, object);
		if (object == "pipe" or object == "cs") {
			break;
		}

		else {
			cout << "Invalid input. Please enter 'pipe' or 'cs'." << std::endl;
		}
	}

	if (object == "pipe") {
		SearchPipes(pipes);
		return;
	}

	else {
		SearchCS(stations);
		return;
	}
}

int main()
{
	PipeMap pipes;
	CSMap stations;
	while (1) {
		ShowMenu();
		int action;
		cout << "Type number (1-8): ";
		if (!(cin >> action) or action <= 0 or action >= 10) {
			cerr << "Invalid input. Please enter a valid integer." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (action)
		{
		case 1:
		{
			Pipe new_pipe = CreatePipe();
			pipes.addElement(new_pipe);

			WriteLog("User created pipe", new_pipe.getName());
			break;
		}
		case 2:
		{
			Compress_station new_cs = CreateCS();
			stations.addElement(new_cs);
			WriteLog("User created CS", new_cs.getName());
			break;
		}
		case 3:
		{
			cout << "\n";
			pipes.printElements();
			stations.printElements();
			cout << "\n";
			break;
		}
		case 4:
		{
			string pipe_id;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			while (true) {
				cout << "Enter pipe id: ";
				getline(cin, pipe_id);
				if (is_number(pipe_id)) {
					break;
				}
				else {
					cout << "Invalid input. Please enter an integer." << endl;
				}
			}
			ChangePipeStatus(pipes, stoi(pipe_id), true);
			WriteLog("User edited pipe with id", pipe_id);
			break;

		}
		case 5:
		{
			EditCS(stations);
			break;
		}
		case 6:
		{
			SaveAll(pipes, stations);
			break;
		}
		case 7:
		{
			pipes.clear();
			stations.clear();
			LoadAll(pipes, stations);
			break;
		}
		case 8:
		{
			Search(pipes, stations);
			break; 
		}

		case 9: {
			Delete(pipes, stations);
			break;
		}
		case 10:
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

