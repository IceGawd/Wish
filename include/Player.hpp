#include "GameObject.hpp"

#include "Socket.h"

class Player : public GameObject {
public:
	Socket* connection;
	Player(Socket* s);
};