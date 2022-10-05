#include "ThreadUtils.hpp"

void student(Client* c) {
	c->student();
}

void teacher(Client* c) {
	c->teacher();
}

void accepter(ThreadManager* tm) {
	tm->accepter();
}

void inisher(ThreadManager* tm) {
	tm->inisher();
}

void inputsReciever(World* world) {
	world->inputsReciever();
}

Client::Client(Socket* s, ThreadManager* b, int i) : mySock(s), myBoss(b), id(i) {

}

void Client::teacher() {
	while (myBoss->run && !dead) {
		myBoss->clientLock.lock();
		string temp = myInput.toString();
		myBoss->clientLock.unlock();
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}


// mqaqight cause mem leak
void Client::student() {
	while (myBoss->run && !dead) {
		string temp = mySock->ReceiveBytes();
		timeOut = chrono::steady_clock().now();
		if (temp == "\n") {
			break;
		}
		/*
		cout << temp;
		for (char c : temp) {
			cout << "char: " << (int) c << endl;
		}
		*/

		myInput = Input(temp);
	}
	cout << "client left\n";
	dead = true;
}

ThreadManager::ThreadManager() {
}

void ThreadManager::accepter() {
	cout << "accepter\n";
	while (run) {
		Socket* temp = server->Accept();
		if (temp != 0) {
			clientLock.lock();

			Client* c = new Client(temp, this, id);
			clients.push_back(c);
			temp->SendBytes(to_string(id));

			thread t1(teacher, clients.at(clients.size() - 1));
			c->myTeacherThread = move(t1);
			thread t2(student, clients.at(clients.size() - 1));
			c->myStudentThread = move(t2);
			id++;

			cout << "client aquired!\n";

			clientLock.unlock();
		}
	}
}

void ThreadManager::inisher() {
	while (run) {
		clientLock.lock();

		for (int x = 0; x < clients.size(); x++) {
			chrono::duration<double> tko = chrono::steady_clock().now() - clients.at(x)->timeOut;
			if (TIMEOUTSECONDS < tko.count()) {
				clients.at(x)->dead = true;
			}


			if (clients.at(x)->dead) {
				/*
				// They don't have a deleter operator so this doesn't work. Prolly causes a memleak
				~clients.at(x)->myTeacherThread;
				~clients.at(x)->myStudentThread;
				*/
				clients.at(x)->mySock->SendBytes(TIMEOUTMESSAGE);
				delete clients.at(x);
				clients.erase(clients.begin() + x);
				x--;
			}
		}

		clientLock.unlock();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void ThreadManager::main() {
	server = new SocketServer(2003, 20);

	acceptorThread = thread(accepter, this);
	inisherThread = thread(inisher, this);
	
	while (run) {
		string temp;
		cin >> temp;
		if (temp == "exit") {
			run = false;
			acceptorThread.join();
			inisherThread.join();
			while (!clients.empty()) {
				/*
				// Read above block
				~clients.at(0)->myTeacherThread;
				~clients.at(0)->myStudentThread;
				*/
				delete clients.at(0);
				clients.erase(clients.begin());
			}
		}
	}
	cout << "done!\n";
}