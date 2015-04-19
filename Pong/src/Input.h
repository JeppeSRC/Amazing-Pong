#pragma once


#define ESCAPE 27
#define LEFT 37
#define RIGHT 39
#define UP 38
#define DOWN 40
#define SHIFT 16
#define RETURN 13
#define BACKSPACE 8
#define SPACE 32
#define CAPSLOCK 20
#define TAB 9
#define CTRL 17
#define DELETE 46
#define WINDOWS_KEY 91
#define INSERT 45

#define KEY(key) Input::isKeyDown(key)

class Input {
private:
	Input() {}
	~Input() {}

	static bool keys[655350];
	static int mx, my;

public:

	static bool isKeyDown(char key);
	static void KeyDown(char key);
	static void KeyUp(char key);
	static int getMX();
	static int getMY();
	static int getMXPos();
	static int getMYPos();
	static void setMX(int x);
	static void setMY(int y);
};
