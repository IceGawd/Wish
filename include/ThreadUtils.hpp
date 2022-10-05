#pragma once

#include "mingw.mutex.h"
#include "mingw.thread.h"
#include "Socket.h"

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

#include "Input.hpp"
#include "World.hpp"

using namespace std;

class ThreadManager;

// Constants in World.hpp

class Client {
public:
	Socket* mySock;
	ThreadManager* myBoss;
	thread myTeacherThread;
	thread myStudentThread;
	Input myInput;
	chrono::time_point<chrono::_V2::steady_clock, chrono::duration<long long int, ratio<1, 1000000000>>> timeOut;
	bool dead = false;
	int id;

	Client(Socket* s, ThreadManager* b, int i);
	void student();
	void teacher();
};

class ThreadManager {
public:
	mutex clientLock;
	vector<Client*> clients;
	World world;

	SocketServer* server;
	thread acceptorThread;
	thread inisherThread;

	int id = 0;
	bool run = true;

	ThreadManager();
	void inisher();
	void accepter();
	void main();
};

void inisher(ThreadManager* tm);
void accepter(ThreadManager* tm);
void teacher(Client* c);
void student(Client* c);
void inputsReciever(World* world);