#include "D:\cpp_projects\ConsoleApplication1\ConsoleApplication1\entities.h"

void WriteLog(string action, string obj_name) {
	ofstream fout;
	fout.open("logs.txt", ios::app);
	time_t result = time(0);

	char cur_time[50];
	ctime_s(cur_time, sizeof cur_time, &result);

	fout << action << " " << obj_name << "   " << cur_time;
	fout.close();
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