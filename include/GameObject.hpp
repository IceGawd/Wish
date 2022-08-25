#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Entity.hpp"
#include "RenderWindow.hpp"

class World;

using namespace std;

class GameObject : public Entity {
public:
	GameObject();
	GameObject(float px, float py, SDL_Texture* ptexture, int pw, int ph);
	
	float xvel = 0;
	float yvel = 0;

	virtual bool draw(RenderWindow* window, World* world, vector<GameObject*>& entities);
	virtual GameObject* createObject();
};