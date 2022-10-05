#pragma once

#include <string>

using namespace std;

class Input {
public:
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;


	Input();
	Input(string from);
	string toString();
};