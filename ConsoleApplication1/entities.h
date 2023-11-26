#pragma once
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

bool is_digit(const std::string& s);

bool is_number(const std::string& s);

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

Pipe CreatePipe();

Compress_station CreateCS();

void EditCS(CSMap& stations);

void Delete(PipeMap& pipes, CSMap& stations);

void ChangePipeStatus(PipeMap& pipes, int pipe_id, bool solo_edit);

void SearchPipes(PipeMap& pipes);

void SearchCS(CSMap& stations);

void Search(PipeMap& pipes, CSMap& stations);

void WriteLog(string action, string obj_name);

void SaveAll(PipeMap& pipes, CSMap& stations);

void LoadAll(PipeMap& pipes, CSMap& stations);