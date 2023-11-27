#include "entities.h"

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

void ChangePipeStatus(PipeMap& pipes, int pipe_id, bool solo_edit)

{
	auto it = pipes.find(pipe_id);

	if (it != pipes.end()) {
		bool current_status = it->second.isRepairing();
		it->second.setStatus(!(current_status));
		WriteLog("User edited pipe with id", to_string(pipe_id));
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
