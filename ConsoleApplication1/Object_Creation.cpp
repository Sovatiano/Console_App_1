#include "entities.h"

Pipe CreatePipe(string diameter)
{
	string name;
	string length;
	string u_diameter;

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

	if (diameter == "0") {
		while (true) {
			cout << "Enter pipe diameter: ";
			getline(cin, u_diameter);
			if (is_number(u_diameter) && stoi(u_diameter) > 0) {
				break;
			}
			else {
				cout << "Invalid input. Please enter a natural integer." << endl;
			}
		}
	}

	Pipe newPipe;
	newPipe.setName(name);
	newPipe.setLength(stod(length));
	if (diameter == "0") {
		newPipe.setDiameter(stoi(u_diameter));
	}
	else {
		newPipe.setDiameter(stoi(diameter));
	}
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