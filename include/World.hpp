#pragma once

#include <vector>

#include "Player.hpp"

const string TIMEOUTMESSAGE = "ERR:TIMEOUT\0";
const int TIMEOUTSECONDS = 60;

class World {
public:
	vector<Player> players;
	vector<GameObject> objects;

	SocketClient* inputClient = nullptr;

	World();
	World(SocketClient* sc);
	void inputsReciever();
};