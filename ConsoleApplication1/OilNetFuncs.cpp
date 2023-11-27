#include "entities.h"

void Connect(CSMap& stations, PipeMap& pipes, NetworkMap& network) {
	string enter_cs_id;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "Type enter cs id: ";
		getline(cin, enter_cs_id);
		if (is_number(enter_cs_id)) {
			if (stations.find(stoi(enter_cs_id)) != stations.end()) {
				break;
			}
			else {
				cout << "CS with id " << enter_cs_id << " not found!" << endl;
			}
		}
		else {
			cout << "Invalid input. Please enter an integer." << endl;
		}
	}

	string exit_cs_id;
	while (true) {
		cout << "Type exit cs id: ";
		getline(cin, exit_cs_id);
		if (is_number(exit_cs_id)) {
			if (stations.find(stoi(exit_cs_id)) != stations.end()) {
				break;
			}
			else {
				cout << "CS with id " << exit_cs_id << " not found!" << endl;
			}
		}
		else {
			cout << "Invalid input. Please enter an integer." << endl;
		}
	}

	string pipe_dtr;
	while (true) {
		cout << "Type pipe diameter: ";
		getline(cin, pipe_dtr);
		if (is_number(pipe_dtr)) {
			break;
		}
		else {
			cout << "Invalid input. Please enter an integer." << endl;
		}
	}


	int pipe_id = pipes.SearchByDiameter(stoi(pipe_dtr), network);

	if (pipe_id == 0) {
		cout << "There is no free pipes with required diameter.\n";
		string decision;
		while (true) {
			cout << "Do you want to create new pipe of required diameter (y/n): ";
			getline(cin, decision);
			if (decision == "y" or decision == "n") {
				break;
			}

			else {
				cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
			}
		}

		if (decision == "y") {
			pipe_id = pipes.getLastId();
			Pipe new_pipe = CreatePipe(pipe_dtr);
			pipes.addElement(new_pipe);
			WriteLog("User created pipe", new_pipe.getName());
		}

		else {
			return;
		}


	}
	int network_id = network.searchVertex(stoi(enter_cs_id));
	if (network_id != 0) {
		network.addToMap(network_id, stoi(enter_cs_id), stoi(exit_cs_id), pipe_id);
	}
	else {
		network_id = network.getLastId();
		network.addToMap(network_id, stoi(enter_cs_id), stoi(exit_cs_id), pipe_id);
	}
}