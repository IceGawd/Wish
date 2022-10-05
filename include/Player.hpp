#pragma once

#include "GameObject.hpp"
#include "Input.hpp"

#include "Socket.h"

class Player : public GameObject {
public:
	int id;
	Input myInput;
	
	Player();
};