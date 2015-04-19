#pragma once

#include <Windows.h>

struct WindowInfo {
	HWND hwnd;
	HDC hdc;
	HGLRC glrc;
	HINSTANCE instance;
};

	class Window {
	public:
		Window(unsigned int width, unsigned int height, LPCWSTR title);
		~Window();

		void update();
		void clear();
		void centerMouse();

		inline unsigned int getWidth() { return width; }
		inline unsigned int getHeight() { return height; }
		inline bool isClosed() { return closed; }

	public:
		static Window* INSTANCE;

	private:
		bool closed;
		unsigned int width, height;
		WindowInfo wi;

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	};
