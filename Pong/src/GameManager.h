#pragma once
#include "Ball.h"
#include "Pad.h"
#include "Indicator.h"

class GameManager {
private:
	Ball* ball;
	Pad* pad1;
	Pad* pad2;
	Light* hitLight;
	unsigned int lightTime;

public:
	GameManager(Pad* pad1, Pad* pad2, Ball* ball);

	void update();
	float CalcInterpolation(Pad* pad, Ball* ball);

	inline Pad* getPad1() const { return pad1; }
	inline Pad* getPad2() const { return pad2; }
	inline Ball* getBall() const { return ball; }
};