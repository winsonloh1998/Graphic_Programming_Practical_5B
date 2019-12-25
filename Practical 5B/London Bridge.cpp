#include <Windows.h>
#include <stdio.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

int bridgeStatus = 0;
float speed = 0.0;
boolean resetView = false;
boolean goPerspective = false;
boolean goOrtho = false;
boolean goBackOrigin = false;
boolean goViewport = false;
float zoomValue = 0.0;

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//sprintf_s(buffer, "test=%f\n", test);
		//OutputDebugString(buffer);
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == VK_LEFT)
			glRotatef(1, 0, 1, 0);
		else if (wParam == VK_RIGHT)
			glRotatef(-1, 0, 1, 0);
		else if (wParam == VK_UP)
			glRotatef(-1, 1, 0, 0);
		else if (wParam == VK_DOWN)
			glRotatef(1, 1, 0, 0);
		else if (wParam == VK_SPACE)
			resetView = true;
		else if (wParam == 'U')
			bridgeStatus = 1;
		else if (wParam == 'D')
			bridgeStatus = 2;
		else if (wParam == 'P')
			goPerspective = true;
		else if (wParam == 'O')
			goOrtho = true;
		else if (wParam == 'B')
			goBackOrigin = true;
		else if (wParam == '1') 
		{
			zoomValue = 1;
			goViewport = true;
		}
		else if (wParam == '2')
		{
			zoomValue = 0.5;
			goViewport = true;
		}
		else if (wParam == '3')
		{
			zoomValue = 0.2;
			goViewport = true;
		}

			
			
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void middle() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"middle.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 0.8, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.45, 0.8, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.45, -0.1, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, -0.1, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, -0.1, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, -0.1, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 0.8, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 0.8, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 0.8, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, 0.8, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.45, 0.8, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.45, 0.8, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.45, 0.8, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.45, 0.8, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.45, -0.1, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.45, -0.1, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.45, -0.1, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, -0.1, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, -0.1, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.45, -0.1, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);
	glVertex3f(-0.45, -0.1, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, -0.1, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, 0.8, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.45, 0.8, 0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void tunnel() {

	// 1
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"middle.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, -0.1, -0.5);
	glTexCoord2f(0.13, 1);
	glVertex3f(-0.75, -0.1, -0.3);
	glTexCoord2f(0.13, 0);
	glVertex3f(-0.75, -0.5, -0.3);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, -0.5, -0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	// 2
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"middle.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0,1);
	glVertex3f(-0.75, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.45, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.45, -0.1, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, -0.1, -0.5);
	glEnd();

	// 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.75, -0.1, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.45, -0.1, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.45, -0.1, -0.3);
	glTexCoord2f(0, 0);
	glVertex3f(-0.75, -0.1, -0.3);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	// 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"middle.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);
	glVertex3f(-0.75, -0.1, -0.3);
	glTexCoord2f(0, 0);
	glVertex3f(-0.45, -0.1, -0.3);
	glTexCoord2f(0, 1);
	glVertex3f(-0.45, -0.5, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.75, -0.5, -0.3);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	// 5
	glBegin(GL_POLYGON);
	glVertex3f(-0.75, -0.5, -0.3);
	glVertex3f(-0.75, -0.5, -0.5);
	glVertex3f(-0.45, -0.5, -0.5);
	glVertex3f(-0.45, -0.5, -0.3);
	glEnd();

	// 6
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"middle.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.45, -0.5, -0.3);
	glTexCoord2f(0.13, 1);
	glVertex3f(-0.45, -0.5, -0.5);
	glTexCoord2f(0.13, 0);
	glVertex3f(-0.45, -0.1, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.45, -0.1, -0.3);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void lowerPart() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"basement.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	glBegin(GL_POLYGON);
	glTexCoord2f(1,1);
	glVertex3f(-0.8, -0.5, -0.7);
	glTexCoord2f(1, 0);
	glVertex3f(-0.4, -0.5, -0.7);
	glTexCoord2f(0, 0);
	glVertex3f(-0.4, -1.0, -0.7);
	glTexCoord2f(0, 1);
	glVertex3f(-0.8, -1.0, -0.7);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.8, -1.0, -0.7);
	glTexCoord2f(0, 1);
	glVertex3f(-0.8, -1.0, 0.7);
	glTexCoord2f(1, 1);
	glVertex3f(-0.8, -0.5, 0.7);
	glTexCoord2f(1, 0);
	glVertex3f(-0.8, -0.5, -0.7);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	///--------------------------------ONLY HERE SPECIAL
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"roof_color.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.8, -0.5, -0.7);
	glTexCoord2f(1, 1);
	glVertex3f(-0.8, -0.5, 0.7);
	glTexCoord2f(1, 0);
	glVertex3f(-0.4, -0.5, 0.7);
	glTexCoord2f(0, 0);
	glVertex3f(-0.4, -0.5, -0.7);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	///--------------------------------ONLY HERE SPECIAL

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"basement.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(1, 1);
	glVertex3f(-0.4, -0.5, -0.7);
	glTexCoord2f(1, 0);
	glVertex3f(-0.4, -0.5, 0.7);
	glTexCoord2f(0, 0);
	glVertex3f(-0.4, -1.0, 0.7);
	glTexCoord2f(0, 1);
	glVertex3f(-0.4, -1.0, -0.7);
	glEnd();

	glColor3f(0, 0, 0.2);
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, -1.0, -0.7);
	glVertex3f(-0.8, -1.0, -0.7);
	glVertex3f(-0.8, -1.0, 0.7);
	glVertex3f(-0.4, -1.0, 0.7);
	glEnd();
	glColor3f(1, 1, 1);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.4, -1.0, 0.7);
	glTexCoord2f(0, 1);
	glVertex3f(-0.8, -1.0, 0.7);
	glTexCoord2f(1, 1);
	glVertex3f(-0.8, -0.5, 0.7);
	glTexCoord2f(1, 0);
	glVertex3f(-0.4, -0.5, 0.7);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void innerBridge() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"road_color.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.4, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.6, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.4, -0.6, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.4, -0.6, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.4, -0.6, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.4, -0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.4, -0.5, -0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"road.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.4, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.4, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.5, -0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"road_color.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.6, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.6, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.6, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.4, -0.6, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.4, -0.6, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.6, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.6, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.4, -0.6, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.4, -0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.5, 0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void outerBridge() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"road_color.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-1.8, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.8, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.8, -0.6, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-1.8, -0.6, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-1.8, -0.6, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.8, -0.6, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.8, -0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-1.8, -0.5, -0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"road.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); 
	glVertex3f(-1.8, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.8, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.8, -0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.8, -0.5, -0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"road_color.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.8, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.8, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.8, -0.6, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.8, -0.6, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.8, -0.6, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.8, -0.6, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.8, -0.6, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.8, -0.6, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.8, -0.6, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-1.8, -0.6, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1.8, -0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.8, -0.5, 0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void innerFence() {

	glColor3f(0.11, 0.56, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-0.38, -0.45, -0.5);
	glVertex3f(-0.02, -0.45, -0.5);
	glVertex3f(-0.02, -0.50, -0.5);
	glVertex3f(-0.38, -0.50, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.38, -0.50, -0.5);
	glVertex3f(-0.38, -0.50, -0.45);
	glVertex3f(-0.38, -0.45, -0.45);
	glVertex3f(-0.38, -0.45, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.38, -0.45, -0.5);
	glVertex3f(-0.38, -0.45, -0.45);
	glVertex3f(-0.02, -0.45, -0.45);
	glVertex3f(-0.02, -0.45, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.02, -0.45, -0.5);
	glVertex3f(-0.02, -0.45, -0.45);
	glVertex3f(-0.02, -0.50, -0.45);
	glVertex3f(-0.02, -0.50, -0.50);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.02, -0.50, -0.50);
	glVertex3f(-0.38, -0.50, -0.50);
	glVertex3f(-0.38, -0.50, -0.45);
	glVertex3f(-0.02, -0.50, -0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.02, -0.50, -0.45);
	glVertex3f(-0.02, -0.45, -0.45);
	glVertex3f(-0.38, -0.45, -0.45);
	glVertex3f(-0.38, -0.50, -0.45);
	glEnd();

	//Other Part
	glBegin(GL_POLYGON);
	glVertex3f(-0.38, -0.45, 0.5);
	glVertex3f(-0.02, -0.45, 0.5);
	glVertex3f(-0.02, -0.50, 0.5);
	glVertex3f(-0.38, -0.50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.38, -0.50, 0.5);
	glVertex3f(-0.38, -0.50, 0.45);
	glVertex3f(-0.38, -0.45, 0.45);
	glVertex3f(-0.38, -0.45, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.38, -0.45, 0.5);
	glVertex3f(-0.38, -0.45, 0.45);
	glVertex3f(-0.02, -0.45, 0.45);
	glVertex3f(-0.02, -0.45, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.02, -0.45, 0.5);
	glVertex3f(-0.02, -0.45, 0.45);
	glVertex3f(-0.02, -0.50, 0.45);
	glVertex3f(-0.02, -0.50, 0.50);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.02, -0.50, 0.50);
	glVertex3f(-0.38, -0.50, 0.50);
	glVertex3f(-0.38, -0.50, 0.45);
	glVertex3f(-0.02, -0.50, 0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.02, -0.50, 0.45);
	glVertex3f(-0.02, -0.45, 0.45);
	glVertex3f(-0.38, -0.45, 0.45);
	glVertex3f(-0.38, -0.50, 0.45);
	glEnd();

	glColor3f(1, 1, 1);
}

void outerFence() {
	glColor3f(0.11, 0.56, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-1.78, -0.45, -0.5);
	glVertex3f(-0.82, -0.45, -0.5);
	glVertex3f(-0.82, -0.50, -0.5);
	glVertex3f(-1.78, -0.50, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.78, -0.50, -0.5);
	glVertex3f(-1.78, -0.50, -0.45);
	glVertex3f(-1.78, -0.45, -0.45);
	glVertex3f(-1.78, -0.45, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.78, -0.45, -0.5);
	glVertex3f(-1.78, -0.45, -0.45);
	glVertex3f(-0.82, -0.45, -0.45);
	glVertex3f(-0.82, -0.45, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.82, -0.45, -0.5);
	glVertex3f(-0.82, -0.45, -0.45);
	glVertex3f(-0.82, -0.50, -0.45);
	glVertex3f(-0.82, -0.50, -0.50);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.82, -0.50, -0.50);
	glVertex3f(-1.78, -0.50, -0.50);
	glVertex3f(-1.78, -0.50, -0.45);
	glVertex3f(-0.82, -0.50, -0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.82, -0.50, -0.45);
	glVertex3f(-0.82, -0.45, -0.45);
	glVertex3f(-1.78, -0.45, -0.45);
	glVertex3f(-1.78, -0.50, -0.45);
	glEnd();

	//Other Part
	glBegin(GL_POLYGON);
	glVertex3f(-1.78, -0.45, 0.5);
	glVertex3f(-0.82, -0.45, 0.5);
	glVertex3f(-0.82, -0.50, 0.5);
	glVertex3f(-1.78, -0.50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.78, -0.50, 0.5);
	glVertex3f(-1.78, -0.50, 0.45);
	glVertex3f(-1.78, -0.45, 0.45);
	glVertex3f(-1.78, -0.45, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.78, -0.45, 0.5);
	glVertex3f(-1.78, -0.45, 0.45);
	glVertex3f(-0.82, -0.45, 0.45);
	glVertex3f(-0.82, -0.45, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.82, -0.45, 0.5);
	glVertex3f(-0.82, -0.45, 0.45);
	glVertex3f(-0.82, -0.50, 0.45);
	glVertex3f(-0.82, -0.50, 0.50);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.82, -0.50, 0.50);
	glVertex3f(-1.78, -0.50, 0.50);
	glVertex3f(-1.78, -0.50, 0.45);
	glVertex3f(-0.82, -0.50, 0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.82, -0.50, 0.45);
	glVertex3f(-0.82, -0.45, 0.45);
	glVertex3f(-1.78, -0.45, 0.45);
	glVertex3f(-1.78, -0.50, 0.45);
	glEnd();

	glColor3f(1, 1, 1);
}

void upperPart() {
	/* Note: Sequence in here is front, left, back, right, up, down*/

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"upperPart.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	glBegin(GL_POLYGON);
	glTexCoord2f(0.34, 1);
	glVertex3f(-0.65, 1.3, -0.2);
	glTexCoord2f(0.66, 1);
	glVertex3f(-0.55, 1.3, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0.8, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(-0.7, 0.8, -0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.66, 0.8, -0.45);
	glTexCoord2f(0.34, 1);
	glVertex3f(-0.65, 1.3, -0.2);
	glTexCoord2f(0.66, 1);
	glVertex3f(-0.65, 1.3, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.7, 0.8, 0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.7, 0.8, 0.45);
	glTexCoord2f(0.34, 1);
	glVertex3f(-0.65, 1.3, 0.2);
	glTexCoord2f(0.66, 1);
	glVertex3f(-0.55, 1.3, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0.8, 0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.8, 0.45);
	glTexCoord2f(0.34, 1);
	glVertex3f(-0.55, 1.3, 0.2);
	glTexCoord2f(0.66, 1);
	glVertex3f(-0.55, 1.3, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0.8, -0.45);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"roof_color.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.8, -0.45);
	glTexCoord2f(1, 1);
	glVertex3f(-0.7, 0.8, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(-0.7, 0.8, 0.45);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.8, 0.45);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.65, 1.3, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.55, 1.3, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.55, 1.3, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.65, 1.3, 0.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void roof() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"roof_color.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.63, 1.3, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.57, 1.3, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.57, 1.3, -0.18);
	glTexCoord2f(0, 0);
	glVertex3f(-0.63, 1.3, -0.18);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.63, 1.3, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, 1.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.63, 1.3, -0.18);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.63, 1.3, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, 1.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.57, 1.3, -0.18);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.57, 1.3, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, 1.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.57, 1.3, 0.18);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.57, 1.3, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, 1.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.63, 1.3, 0.18);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void bridgeHanger() {
	glColor3f(0.11, 0.56, 1);

	glBegin(GL_LINE_STRIP);
	for (int i = 360; i > 200; i--)
	{
		float degInRad = i * 3.14159 / 180;
		glVertex3f((cos(degInRad) * 0.55) - 1.3, (sin(degInRad) * 0.55) + 0.7, -0.5);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 360; i > 200; i--)
	{
		float degInRad = i * 3.14159 / 180;
		glVertex3f((cos(degInRad) * 0.55) - 1.3, (sin(degInRad) * 0.55) + 0.7, -0.45);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.75, 0.7, -0.5);
	glVertex3f(-0.75, 0.7, -0.45);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.81, 0.5, -0.45);
	glVertex3f(-1.81, 0.5, -0.5);
	glEnd();


	//Other Side
	glBegin(GL_LINE_STRIP);
	for (int i = 360; i > 200; i--)
	{
		float degInRad = i * 3.14159 / 180;
		glVertex3f((cos(degInRad) * 0.55) - 1.3, (sin(degInRad) * 0.55) + 0.7, 0.5);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 360; i > 200; i--)
	{
		float degInRad = i * 3.14159 / 180;
		glVertex3f((cos(degInRad) * 0.55) - 1.3, (sin(degInRad) * 0.55) + 0.7, 0.45);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.75, 0.7, 0.5);
	glVertex3f(-0.75, 0.7, 0.45);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.81, 0.5, 0.45);
	glVertex3f(-1.81, 0.5, 0.5);
	glEnd();

	glColor3f(1, 1, 1);
}

void upperConnector() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"upperConnector.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5,0.8,-0.4);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.8, -0.4);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.6, -0.4);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.6, -0.4);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.6, -0.4);
	glVertex3f(-0.5, 0.6, -0.2);
	glVertex3f(-0.5, 0.8, -0.2);
	glVertex3f(-0.5, 0.8, -0.4);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, 0.8, -0.4);
	glVertex3f(-0.5, 0.8, -0.2);
	glVertex3f(0.5, 0.8, -0.2);
	glVertex3f(0.5, 0.8, -0.4);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.5, 0.8, -0.4);
	glVertex3f(0.5, 0.8, -0.2);
	glVertex3f(0.5, 0.6, -0.2);
	glVertex3f(0.5, 0.6, -0.4);
	glEnd();

	glColor3f(0.39, 0.38, 0.36);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.6, -0.4);
	glVertex3f(-0.5, 0.6, -0.4);
	glVertex3f(-0.5, 0.6, -0.2);
	glVertex3f(0.5, 0.6, -0.2);
	glEnd();
	glColor3f(1, 1, 1);

	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.6, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.6, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.8, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.8, -0.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void bridgePillar() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"pillar.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	GLUquadricObj *firstPillar = NULL;
	firstPillar = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-1.59, 0.24, -0.475);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(firstPillar, GLU_FILL);
	gluQuadricTexture(firstPillar, true);
	gluCylinder(firstPillar, 0.02, 0.02, 0.74, 10, 30);
	gluDeleteQuadric(firstPillar);
	glPopMatrix();

	GLUquadricObj *secondPillar = NULL;
	secondPillar = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-1.29, 0.15, -0.475);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(secondPillar, GLU_FILL);
	gluQuadricTexture(secondPillar, true);
	gluCylinder(secondPillar, 0.02, 0.02, 0.65, 10, 30);
	gluDeleteQuadric(secondPillar);
	glPopMatrix();

	GLUquadricObj *thirdPillar = NULL;
	thirdPillar = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-0.99, 0.25, -0.475);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(thirdPillar, GLU_FILL);
	gluQuadricTexture(thirdPillar, true);
	gluCylinder(thirdPillar, 0.02, 0.02, 0.75, 10, 30);
	gluDeleteQuadric(thirdPillar);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void sea() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"sea.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) 
	{
		float degInRad = i * (3.14159 / 180);
		glTexCoord2f(cos(degInRad) * 1, sin(degInRad) * 1);
		glVertex3f(cos(degInRad)*2, -0.9 ,sin(degInRad*1)*2);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void background() {
	glBegin(GL_POLYGON);
	glVertex3f(-2, 2, -2);
	glVertex3f(2, 2, -2);
	glVertex3f(2, -2, -2);
	glVertex3f(-2, -2, -2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-2, -2, -2);
	glVertex3f(-2, -2, 2);
	glVertex3f(-2, 2, 2);
	glVertex3f(-2, 2, -2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-2, 2, -2);
	glVertex3f(-2, 2, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 2, -2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2, 2, -2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, -2, 2);
	glVertex3f(2, -2, -2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2, -2, 2);
	glVertex3f(-2, -2, 2);
	glVertex3f(-2, 2, 2);
	glVertex3f(2, 2, 2);
	glEnd();
}

void londonBridge()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.53, 0.81, 0.92,0);
	glEnable(GL_DEPTH_TEST);

	if (resetView) {
		glLoadIdentity();
		resetView = false;
		glScalef(0.5, 0.5, 0.5);
	}

	glMatrixMode(GL_MODELVIEW);
	//glColor3f(0, 0, 0);
	//background();
	sea();
	lowerPart();
	middle();
	outerBridge();
	outerFence();
	upperPart();
	roof();
	bridgeHanger();
	upperConnector();
	bridgePillar();
	tunnel();
	
	//Duplicate Tunnel
	glPushMatrix();
	glTranslatef(0, 0, 0.8);
	tunnel();
	glPopMatrix();

	//Duplicate Bridge Pillar
	glPushMatrix();
	glTranslatef(0, 0, 0.955);
	bridgePillar();
	glPopMatrix();

	//Duplicate Upper Connector
	glPushMatrix();
	glTranslatef(0, 0, 0.6);
	upperConnector();
	glPopMatrix();

	if (bridgeStatus == 1) 
	{
		speed++;
	}
	else if (bridgeStatus == 2) 
	{
		speed--;
	}

	if (speed >= 50) {
		speed = 50;
		bridgeStatus = 0;
	}

	glPushMatrix();
	glTranslatef(-0.4, -0.55, 0);
	glRotatef(speed, 0, 0, 1);
	glTranslatef(0.4, 0.55, 0);
	innerFence();
	innerBridge();
	glPopMatrix();

	///////////////////////// THE OTHER HALF //////////////////////////
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	lowerPart();
	middle();
	outerBridge();
	outerFence();
	upperPart();
	roof();
	bridgeHanger();
	bridgePillar();
	tunnel();

	//Duplicate Tunnel
	glPushMatrix();
	glTranslatef(0, 0, 0.8);
	tunnel();
	glPopMatrix();

	//Duplicate Bridge Pillar
	glPushMatrix();
	glTranslatef(0, 0, 0.955);
	bridgePillar();
	glPopMatrix();

	if (speed <= 0.1) {
		speed = 0.0;
		bridgeStatus = 0;
	}

	glPushMatrix();
	glTranslatef(-0.4, -0.55, 0);
	glRotatef(speed, 0, 0, 1);
	glTranslatef(0.4, 0.55, 0);
	innerFence();
	innerBridge();
	glPopMatrix();

	glPopMatrix();
}
//--------------------------------------------------------------------


void goPerspectiveView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(0.5, 0.5, 0.5);
	gluPerspective(60.0, 1.0, 1, 100);
	glFrustum(-1, 1, -1, 1, 1, 100);
}

void goOrthoView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(0.5, 0.5, 0.5);
	glOrtho(-1, 1, -1, 1, 1, 100);
}

void goBackOriginView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1200, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	glScalef(0.5, 0.5, 0.5);
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
			
		if (goPerspective) 
		{
			goPerspectiveView();
			goPerspective = false;
		}
		
		if (goOrtho)
		{
			goOrthoView();
			goOrtho = false;
		}

		if (goBackOrigin) {
			goBackOriginView();
			goBackOrigin = false;
		}

		if (goViewport) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-zoomValue, zoomValue, -zoomValue, zoomValue, -1, 1);
			goViewport = false;
			zoomValue = 0;
		}

		londonBridge();
		
		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);
	return true;
}
//--------------------------------------------------------------------