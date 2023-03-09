#include "Game.h"

Engine engine;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);



//int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main() 
{
	WNDCLASSEX wcex;
	HWND hwnd;
	MSG msg;
	HDC hDC;
	HGLRC hRC;
	BOOL bQuit = FALSE;
	float theta = 0.0f;

	WCHAR szTitle[100] = {'t','i','t','l','e'};                 
	WCHAR szWindowClass[100] = {'M'};							

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	//wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wcex.hbrBackground = CreateSolidBrush((COLORREF)RGB(200, 240, 255));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* create main window */
	hwnd = CreateWindowEx(0,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600,
		600,
		NULL,
		NULL,
		NULL,  //hInstance
		NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL); //nCmdShow



	/* enable OpenGL for the window */
	EnableOpenGL(hwnd, &hDC, &hRC);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);



	glClearColor(0.3, 0.3, 0.3, 0.0);

	// рассчет освещения

	glEnable(GL_LIGHTING);

	// двухсторонний расчет освещения

	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// автоматическое приведение нормалей к

	// единичной длине

	glEnable(GL_NORMALIZE);






	engine.Init(hwnd);

	char objectName[250] {};
	std::cout << "Enter <object.obj> name:\n";
	std::cin >> objectName;

	ModelLoader model;
	model.load(objectName);

	GLfloat light0_diffuse[] = { 255, 70, 70 };

			GLfloat light0_direction[] = { 50.0, 80.0, 0.0, 1.0 };
	/* program main loop */
	while (!bQuit)
	{
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/* OpenGL animation code goes here */
			
			glClearColor(0.78f, 0.94f, 1.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		




			GLfloat material_diffuse[] = { 1.0, 5.0, 1.0, 1.0 };

			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);





			// направленный источник света

			




			glPushMatrix();
			

			glEnable(GL_LIGHT0);

			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

			glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);

				engine.Play(hwnd);
				
			
			
				glColor3f(0.8, 0.8, 0.8);
				model.draw();
				glEndList();

				glBegin(GL_TRIANGLES);
				glColor3f(1.0, 0, 0);

				glVertex3f(0, 0, 0);
				glVertex3f(10, 0, 0);
				glVertex3f(0, 5, 0);


				glColor3f(0.0, 1.0, 0);

				glVertex3f(0, 0, 0.001);
				glVertex3f(0, 10, 0.001);
				glVertex3f(5, 0, 0.001);


				glColor3f(0.0, 0.0, 1.0);

				glVertex3f(0, 0, 0);
				glVertex3f(0, 0, 10);
				glVertex3f(3, 3, 0);


				glEnd();
				

				
			glPopMatrix();
			

			glDisable(GL_LIGHT0);

		

			SwapBuffers(hDC);

			//theta += 0.5f;
			Sleep(1);
		}
	}



	/* destroy the window explicitly */
	DestroyWindow(hwnd);

	return (WPARAM)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		engine.WndResize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}






void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
				  PFD_SUPPORT_OPENGL | 
			      PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}