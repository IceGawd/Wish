#include <iostream>

#include "GameObject.hpp"

using namespace std;

GameObject::GameObject() {
	
}

GameObject::GameObject(float px, float py, SDL_Texture* ptexture, int pw, int ph) : Entity(px, py, ptexture, pw, ph) {

}

bool GameObject::draw(RenderWindow* window, World* world, vector<GameObject*>& entities) {
	x += xvel;
	y += yvel;

	return false;
}

GameObject* GameObject::createObject() {
	return new GameObject(*this);
}