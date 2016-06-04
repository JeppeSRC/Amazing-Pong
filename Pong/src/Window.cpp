#include "Window.h"
#include <stdio.h>
#include <glew.h>
#include <Windowsx.h>
#include "Input.h"
#include "Shader.h"
#include "mat4.h"


	Window* Window::INSTANCE;

	Window::~Window(){
		wglDeleteContext(wi.glrc);
		DeleteDC(wi.hdc);
		DestroyWindow(wi.hwnd);
	}

	Window::Window(unsigned int width, unsigned int height, LPCWSTR title){

		this->width = width;
		this->height = height;

		closed = true;

		wi.instance = GetModuleHandle(NULL);

		WNDCLASS ws;
		ws.cbClsExtra = 0;
		ws.cbWndExtra = 0;
		ws.hbrBackground = NULL;
		ws.hCursor = LoadCursor(NULL, IDC_ARROW);
		ws.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		ws.hInstance = wi.instance;
		ws.lpfnWndProc = (WNDPROC)WndProc;
		ws.lpszClassName = L"Window_Class";
		ws.lpszMenuName = NULL;
		ws.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

		if (!RegisterClass(&ws)){
			printf("Failed To Register Class\n");
			return;
		}

		wi.hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_CLIENTEDGE,
								 L"Window_Class", title,
								 WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
								 0, 0, width, height, NULL, NULL, wi.instance, NULL);

		if (!wi.hwnd){
			printf("Failed To Create Window\n");
			return;
		}

		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW,
			PFD_TYPE_RGBA, 32,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0, 0, 0, 0
		};

		if (!(wi.hdc = GetDC(wi.hwnd))){
			printf("Faild TO Create Deivce Context\n");
			return;
		}

		int pfdFormat;

		if (!(pfdFormat = ChoosePixelFormat(wi.hdc, &pfd))){
			printf("Invalid PixelFormat\n");
			return;
		}

		if (!SetPixelFormat(wi.hdc, pfdFormat, &pfd)){
			printf("Could Not Ser PixelFormat\n");
			return;
		}

		if (!(wi.glrc = wglCreateContext(wi.hdc))){
			printf("Faild To Create OpenGL Context\n");
			return;
		}

		if (!wglMakeCurrent(wi.hdc, wi.glrc)){
			printf("Could Nor Make OpenGL Context Current\n");
			return;
		}

		if (glewInit() != GLEW_OK){
			printf("Faild To Initialize GLEW\n");
			return;
		}

		printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
		printf("Graphics Card: %s\n", glGetString(GL_RENDERER));
		printf("Graphics Card Vendor: %s\n", glGetString(GL_VENDOR));

		ShowWindow(wi.hwnd, SW_SHOW);

		closed = false;

		INSTANCE = this;
	}

	void Window::centerMouse(){
		POINT pt;
		pt.x = width / 2;
		pt.y = height / 2;
		ClientToScreen(wi.hwnd, &pt);
		SetCursorPos(pt.x, pt.y);
	}

	void Window::update(){

		MSG msg;

		if (PeekMessage(&msg, wi.hwnd, 0, 0, PM_REMOVE)){
			switch (msg.message){
			case WM_CLOSE:
				closed = true;
				break;
			
			case WM_KEYDOWN:
				Input::KeyDown(msg.wParam);
				break;

			case WM_KEYUP:
				Input::KeyUp(msg.wParam);
				break;

			case WM_MOUSEMOVE:
				Input::setMX(GET_X_LPARAM(msg.lParam));
				Input::setMY(GET_Y_LPARAM(msg.lParam));
				break;

		

			default:
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
		}

		SwapBuffers(wi.hdc);
	}

	LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){

		switch (msg){
		case WM_CLOSE:
			INSTANCE->closed = true;
			break;

		case WM_SIZE:
			if (INSTANCE) {
				INSTANCE->width = LOWORD(lparam);
				INSTANCE->height = HIWORD(lparam);
				glViewport(0, 0, INSTANCE->width, INSTANCE->height);
				Shader::active->setMat4("projection", mat4::ortho(0, float(INSTANCE->getWidth() - 20), float(INSTANCE->getHeight() - 45), 0, 0.001f, 100));
			}
			break;
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
