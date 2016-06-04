#include <stdio.h>
#include <glew.h>
#include <wglew.h>
#include <vector>
#include <ctime>
#include "src/Shader.h"
#include "src/vec3.h"
#include "src/mat4.h"
#include "src/Window.h"
#include "src/Ball.h"
#include "src/Light.h"
#include "src/Input.h"
#include "src/BackGround.h"
#include "src/Pad.h"
#include "src/GameManager.h"
#include "src/Audio.h"
#include "src/AudioManager.h"


#define SPEED 1.25
#define TEX 0

int main() {

	Window window(1000, 600, L"Amazing");
	AudioManager::Init();
	wglSwapIntervalEXT(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("./res/shader.vs", "./res/shader.fs");
	shader.bind();
	shader.setMat4("projection", mat4::ortho(0, window.getWidth()-20, window.getHeight()-45, 0, 0.001f, 100));

	std::vector<Renderable*> bg;

	for (int x = 0; x < window.getWidth(); x += 100) {
		for (int y = 0; y < window.getHeight(); y += 100) {
			bg.push_back(new BGObject(vec3(x % window.getWidth(), y % window.getHeight(), 1), vec3(100, 100), vec4((float)(x % 256) / 255, (float)(y % 256) / 255, (float)((x * y) % 256) / 255, 1)));
		}
	}
	Ball ball(vec3(500, 300, 0.1), vec3(15.5, 15.5), vec4(1, 1, 1, 1), new Texture("./res/Ball.png"));
	Pad pad1(vec3(15, 200, 0.1), vec3(25, 200), vec4(1, 1, 1, 1));
	Pad pad2(vec3(window.getWidth() - 25 - 20 - 15, 200, 0.1), vec3(25, 200), vec4(1, 1, 1, 1));

	GameManager manager(&pad1, &pad2, &ball);

	float x = 0, y = 0;

	int lastTime = clock();
	int time = clock();
	double delta = 0;
	const double ms = 1000.0 / 300.0;
	int fps = 0;

	while (!window.isClosed()) {
		long now = clock();

		delta = (now - lastTime); // ms;

		lastTime = now;

		if (true) {
			shader.setInt("totalLights", Light::getTotalLights());
			x += 0.020f;
			y += 0.020f;

			if (KEY('S'))
				pad1.getPos().y += SPEED * delta;


			if (KEY('W'))
				pad1.getPos().y -= SPEED * delta;


			if (KEY(DOWN))
				pad2.getPos().y += SPEED * delta;

			if (KEY(UP))
				pad2.getPos().y -= SPEED * delta;
	
			manager.update();

			pad1.update(0.0f);
			pad2.update(0.0f);
			ball.update(delta);
		
		}

		glClear(GL_COLOR_BUFFER_BIT);


		for (Renderable* bgo : bg) {
			bgo->render();
		}

		pad1.render();
		pad2.render();

		ball.render();
		
		window.update();
		fps++;

		if (clock() - time >= 1000) {
			time += 1000;
			printf("FPS: %d\n", fps);
			fps = 0;
		}
	}

	AudioManager::Destroy();
}

