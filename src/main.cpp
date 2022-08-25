#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>

#include "Socket.h"
#include "ThreadUtils.hpp"

using namespace std;

const int FPS = 60;

void Client() {
	SocketClient* client = new SocketClient("137.184.229.190", 7777);
	cout << "client\n";
	while (true) {

	}
}

void Server() {
	cout << "server\n";

	SocketServer* server = new SocketServer(7777, 20);

	vector<Socket*> clients;
	while (true) {
		Socket* temp = server->Accept();
		if (temp != 0) {
			clients.push_back(temp);
			cout << "client aquired!\n";
		}
		for (Socket* s : clients) {
			cout << s << endl;
			string temp = s->ReceiveBytes();
			cout << temp << endl;
		}
		cout << "frame\n";
	}
}

int main(int argc, char *argv[])
{
	/*
	cout << argc << endl;
	for (int x = 0; x < argc; x++) {
		cout << argv[x] << endl;
	}
	*/

	if (argc == 2) {
		Server();	
	}
	else {
		Client();
	}
	return 0;
}