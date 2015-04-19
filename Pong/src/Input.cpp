#include "Input.h"
#include "Window.h"


bool Input::keys[655350];
int Input::mx;
int Input::my;

bool Input::isKeyDown(char key){
	if (key > 655350) return false;
	return keys[(unsigned long)key];
}

void Input::KeyDown(char key){
	if (key > 655350) return;
	keys[(unsigned long)key] = true;
}

void Input::KeyUp(char key){
	if (key > 655350) return;
	keys[(unsigned long)key] = false;
}

void Input::setMX(int x) { mx = x; }
void Input::setMY(int y) { my = y; }

int Input::getMX() { return mx - Window::INSTANCE->getWidth() / 2; }
int Input::getMY() { return my - Window::INSTANCE->getHeight() / 2; }
int Input::getMXPos() { return mx; }
int Input::getMYPos() { return my; }