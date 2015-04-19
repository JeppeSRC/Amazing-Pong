#include "GameManager.h"
#include "AudioManager.h"
#include "Window.h"

#define LIGHT_LIFE 80


GameManager::GameManager(Pad* pad1, Pad* pad2, Ball* ball) : pad1(pad1), pad2(pad2), ball(ball) {
	hitLight = new Light(vec3(-1000, 1000), vec4(1, 1, 1, 1), 10, 1);
	lightTime = 0;
	AudioManager::ballHit_2->setPos(&ball->getPos());
}

void GameManager::update() {

	if (lightTime > 0) {
		lightTime--;
		hitLight->getDamper() += 0.03;
	}

	if (lightTime <= 0) {
		hitLight->getDamper() = 0.125;
		hitLight->getPos().x = 4000;
	}

	if (ball->getVel().x > 0) {
		if (ball->getPos().x + ball->getSize().x >= pad2->getPos().x && ball->getPos().x + ball->getSize().x <= pad2->getPos().x + pad2->getSize().x)
			if (ball->getPos().y >= pad2->getPos().y && ball->getPos().y <= pad2->getPos().y + pad2->getSize().y) {
				ball->getVel().x *= -1;
				hitLight->getPos() = ball->getPos() + ball->getSize() / 2;
				hitLight->getDamper() = 0.125;
				lightTime = LIGHT_LIFE;
				AudioManager::ballHit_2->play();
			}
	} else if (ball->getVel().x < 0) {
		if (ball->getPos().x >= pad1->getPos().x && ball->getPos().x <= pad1->getPos().x + pad1->getSize().x)
			if (ball->getPos().y >= pad1->getPos().y && ball->getPos().y <= pad1->getPos().y + pad1->getSize().y) {
				ball->getVel().x *= -1;
				hitLight->getPos() = ball->getPos() + ball->getSize() / 2;
				hitLight->getDamper() = 0.125;
				lightTime = LIGHT_LIFE;
				AudioManager::ballHit_2->play();
			}
	}


	if (ball->getPos().y <= 0) {
		ball->getVel().y *= -1;
		lightTime = LIGHT_LIFE;
		hitLight->getDamper() = 0.125;
		hitLight->getPos() = ball->getPos() + ball->getSize() / 2;
		AudioManager::ballHit_2->play();
	}

	if (ball->getPos().y + ball->getSize().y >= Window::INSTANCE->getHeight() - 45) {
		ball->getVel().y *= -1;
		lightTime = LIGHT_LIFE;
		hitLight->getDamper() = 0.125;
		hitLight->getPos() = ball->getPos() + ball->getSize() / 2;
		AudioManager::ballHit_2->play();
	}

	if (ball->getPos().x > Window::INSTANCE->getWidth()) {
		hitLight->getPos() = vec3(500, 300);
		ball->getVel() = vec3();
		hitLight->getDamper() = 1;
		hitLight->getRange() = 100;
	}

	if (ball->getPos().x < 0) {
		ball->getVel() = vec3();
		hitLight->getPos() = vec3(500, 300);
		hitLight->getDamper() = 1;
		hitLight->getRange() = 100;
	}

	hitLight->render();

}