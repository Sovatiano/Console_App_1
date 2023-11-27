#include "entities.h"

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
		<< "10. Connect stations" << "\n"
		<< "11. Make topological sort" << "\n"
		<< "12. Delete connection" << "\n"
		<< "13. Exit" << "\n";
}

int main()
{
	PipeMap pipes;
	CSMap stations;
	NetworkMap network;
	while (1) {
		ShowMenu();
		int action;
		cout << "Type number (1-8): ";
		if (!(cin >> action) or action <= 0 or action > 13) {
			cerr << "Invalid input. Please enter a valid integer." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (action)
		{
		case 1:
		{
			Pipe new_pipe = CreatePipe("0");
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
			network.printElems();
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
			break;

		}

		case 5:
		{
			EditCS(stations);
			break;
		}

		case 6:
		{
			SaveAll(pipes, stations, network);
			break;
		}

		case 7:
		{
			pipes.clear();
			stations.clear();
			network.clear();
			LoadAll(pipes, stations, network);
			break;
		}

		case 8:
		{
			Search(pipes, stations);
			break; 
		}

		case 9: {
			Delete(pipes, stations, network);
			break;
		}

		case 10:
		{
			Connect(stations, pipes, network);
			break;
		}

		case 11: {
			makeTopSort(network);
			break;
		}

		case 12: {
			deleteEdge(network);
			break;
		}

		case 13: {
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

