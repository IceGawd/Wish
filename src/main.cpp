#include "ThreadUtils.hpp"


using namespace std;

const int FPS = 60;

void client() {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		cout << "SDL Video Failure: " << SDL_GetError() << "\n";
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		cout << "IMG PNG Failure: " << SDL_GetError() << "\n";
	}
	if(TTF_Init() == -1) {
	    cout << "TTF_Init: " << TTF_GetError() << endl;
	}

	// SocketClient* inputClient = new SocketClient("137.184.229.190", 2003);
	// SocketClient* stateClient = new SocketClient("127.0.0.1", 9001);
	SocketClient* inputClient = new SocketClient("127.0.0.1", 2003);
	// SocketClient* stateClient = new SocketClient("127.0.0.1", 9001);

	RenderWindow window("Wish");
	bool gameRunning = true;
	bool gameplaying = true;
	SDL_Event event;

	Player myPlayer;
	World* world = new World(inputClient);
	myPlayer.id = atoi(inputClient->ReceiveBytes().c_str());

	thread t1(inputsReciever, world);

	cout << "client\n";
	while (gameRunning) {
		auto start = chrono::steady_clock().now();

		// RUN GAME
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}

			SDL_Keycode kc = event.key.keysym.sym;
			if (event.type == SDL_KEYDOWN){
				if (kc == SDLK_w) {
					myPlayer.myInput.up = true;
				}
				if (kc == SDLK_s) {
					myPlayer.myInput.down = true;
				}
				if (kc == SDLK_a) {
					myPlayer.myInput.left = true;
				}
				if (kc == SDLK_d) {
					myPlayer.myInput.right = true;
				}
			}
			if (event.type == SDL_KEYUP){
				if (kc == SDLK_w) {
					myPlayer.myInput.up = false;
				}
				if (kc == SDLK_s) {
					myPlayer.myInput.down = false;
				}
				if (kc == SDLK_a) {
					myPlayer.myInput.left = false;
				}
				if (kc == SDLK_d) {
					myPlayer.myInput.right = false;
				}
			}
		}

		// SEND INFO
		inputClient->SendBytes(myPlayer.myInput.toString());

		// RUN AT CORRECT FPS
		auto end = chrono::steady_clock().now();
		chrono::duration<double> frameDone = end - start;
		double delay = 1000 * ((1.0 / FPS) - frameDone.count());
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}
}

void server() {
	cout << "server\n";

	ThreadManager tm;

	tm.main();
}

int main(int argc, char *argv[])
{
//	Version v

	/*
	cout << argc << endl;
	for (int x = 0; x < argc; x++) {
		cout << argv[x] << endl;
	}
	*/

	if (argc == 2) {
		server();	
	}
	else {
		client();
	}
	return 0;
}