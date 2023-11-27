#include "entities.h"

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