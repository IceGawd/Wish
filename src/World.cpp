#include "World.hpp"

World::World() {
}

World::World(SocketClient* sc) {
	inputClient = sc;
}


void World::inputsReciever() {
	while (true) {
		string bytes = inputClient->ReceiveBytes();
		if (bytes == TIMEOUTMESSAGE) {
			break;
		}

	}
}