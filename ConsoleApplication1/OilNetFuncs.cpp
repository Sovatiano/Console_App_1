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
		if (is_number(pipe_dtr) and stoi(pipe_dtr) > 0) {
			break;
		}
		else {
			cout << "Invalid input. Please enter a positive integer." << endl;
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

void makeTopSort(NetworkMap& networks) {
	string network_id;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "Enter network id: ";
		getline(cin, network_id);
		if (is_number(network_id)) {
			break;
		}
		else {
			cout << "Invalid input. Please enter an integer." << endl;
		}
	}

	auto it = networks.find(stoi(network_id));

	if (it != networks.end()) {
		networks.topSort(stoi(network_id));
	}
	else {
		std::cerr << "Pipe with id " << network_id << " not found." << std::endl;
		return;
	}
}

void deleteEdge(NetworkMap& networks) {
	string net_id;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "Enter network id: ";

		getline(cin, net_id);
		if (is_number(net_id)) {
			if (networks.find(stoi(net_id)) != networks.end()) {
				break;
			}
			else {
				cout << "Network with id " << net_id << " not found!" << endl;
			}
		}
		else {
			cout << "Invalid input. Please enter an integer." << endl;
		}
	}

	string id;
	while (true) {
		cout << "Enter pipe id: ";
		getline(cin, id);
		if (is_digit(id)) {
			break;
		}
		else {
			cout << "Invalid input. Please enter an integer." << endl;
		}
	}

	networks.delEdge(stoi(net_id), stoi(id));

}