#include <windows.h>		
#include <gl\gl.h>			
#include <gl\glu.h>			
#include <gl\glaux.h>		
#include "Scena.h"
#include <time.h>

#define SIZE 2.0f

Scena scena;

HDC			hDC=NULL;	
HGLRC		hRC=NULL;		
HWND		hWnd=NULL;		
HINSTANCE	hInstance;		
bool	keys[256];			
bool	active=TRUE;		
bool	fullscreen=TRUE;	
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		
{
	if (height==0)											
	{
		height=1;											
	}

	glViewport(0,0,width,height);						
	glMatrixMode(GL_PROJECTION);							
	glLoadIdentity();									
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,500.0f);	
	glMatrixMode(GL_MODELVIEW);								
	glLoadIdentity();
}

int InitGL(GLvoid)										
{
	glShadeModel(GL_SMOOTH);								
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);					
	glClearDepth(1.0f);										
	glEnable(GL_DEPTH_TEST);								
	glDepthFunc(GL_LEQUAL);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//*
	float pos [] = {20.0, 10.0, 20.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos); // swiatlo
	//*/
    
    glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glEnable(GL_NORMALIZE);

	glNewList(1, GL_COMPILE);    // sciana kostki     
	glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-SIZE, SIZE, SIZE);

        glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
        glVertex3f(SIZE, SIZE, SIZE);

        glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
        glVertex3f(SIZE, -SIZE, SIZE);

        glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    // od pochylni
    glNewList(13, GL_COMPILE);         
	glBegin(GL_QUADS); //gora
        glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
		glTexCoord2f(1.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
		glTexCoord2f(0.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(14, GL_COMPILE);         
	glBegin(GL_TRIANGLES); //bok lewy
        glNormal3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
		glTexCoord2f(1.0f, 0.0f);
        glNormal3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(15, GL_COMPILE);         
	glBegin(GL_TRIANGLES); //bok prawy
        glNormal3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();

	srand(time(NULL));
	glMatrixMode(GL_MODELVIEW);
	scena.loadTexture();
	return TRUE;										
}

int DrawGLScene(GLvoid)									
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
    glLoadIdentity();
	gluLookAt(scena.ox, scena.oy, scena.oz, scena.cz + scena.ox, scena.cy + scena.oy, scena.cx + scena.oz, 0.0, 1.0, 0.0);
	scena.draw();
	return TRUE;										
}

GLvoid KillGLWindow(GLvoid)								
{
	if (fullscreen)											
	{
		ChangeDisplaySettings(NULL,0);							
		ShowCursor(TRUE);									
	}

	if (hRC)												
	{
		if (!wglMakeCurrent(NULL,NULL))							
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))								
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;											
	}

	if (hDC && !ReleaseDC(hWnd,hDC))						
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;											
	}

	if (hWnd && !DestroyWindow(hWnd))						
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;											
	}

	if (!UnregisterClass("OpenGL",hInstance))				
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;										
	}
}

 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;				
	WNDCLASS	wc;							
	DWORD		dwExStyle;					
	DWORD		dwStyle;					
	RECT		WindowRect;					
	WindowRect.left=(long)0;				
	WindowRect.right=(long)width;			
	WindowRect.top=(long)0;					
	WindowRect.bottom=(long)height;		
	fullscreen=fullscreenflag;			
	hInstance			= GetModuleHandle(NULL);					
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		
	wc.lpfnWndProc		= (WNDPROC) WndProc;						
	wc.cbClsExtra		= 0;										
	wc.cbWndExtra		= 0;										
	wc.hInstance		= hInstance;								
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);				
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);				
	wc.hbrBackground	= NULL;										
	wc.lpszMenuName		= NULL;										
	wc.lpszClassName	= "OpenGL";								
	if (!RegisterClass(&wc))										
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;												
	}
	
	if (fullscreen)													
	{
		DEVMODE dmScreenSettings;										
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));			
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);				
		dmScreenSettings.dmPelsWidth	= width;						
		dmScreenSettings.dmPelsHeight	= height;						
		dmScreenSettings.dmBitsPerPel	= bits;							
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;					
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;												
			}
		}
	}

	if (fullscreen)													
	{
		dwExStyle=WS_EX_APPWINDOW;										
		dwStyle=WS_POPUP;												
		ShowCursor(FALSE);											
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;					
		dwStyle=WS_OVERLAPPEDWINDOW;								
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		
		if (!(hWnd=CreateWindowEx(	dwExStyle,	"OpenGL",title,	dwStyle |WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,0, 0,WindowRect.right-WindowRect.left,	WindowRect.bottom-WindowRect.top,NULL,NULL,	hInstance,	NULL)))
		{
		KillGLWindow();										
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									
		}

	static	PIXELFORMATDESCRIPTOR pfd=					
	{
		sizeof(PIXELFORMATDESCRIPTOR),	1,PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER,	PFD_TYPE_RGBA,	bits,0, 0, 0, 0, 0, 0,0,0,	0,	0, 0, 0, 0,	16,	0,	0,	PFD_MAIN_PLANE,	0,	0, 0, 0	
	};
	
	if (!(hDC=GetDC(hWnd)))								
	{
		KillGLWindow();										
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		
	{
		KillGLWindow();										
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			
	{
		KillGLWindow();										
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									
	}

	if (!(hRC=wglCreateContext(hDC)))					
	{
		KillGLWindow();										
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									
	}

	if(!wglMakeCurrent(hDC,hRC))						
	{
		KillGLWindow();										
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									
	}

	ShowWindow(hWnd,SW_SHOW);							
	SetForegroundWindow(hWnd);							SetFocus(hWnd);										ReSizeGLScene(width, height);					
	if (!InitGL())										
	{
		KillGLWindow();										
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									
	}

	return TRUE;									
}

LRESULT CALLBACK WndProc(	HWND	hWnd,UINT	uMsg,WPARAM	wParam,	LPARAM	lParam)			{
	switch (uMsg)									
	{
		case WM_ACTIVATE:									
			{
			if (!HIWORD(wParam))								
			{
				active=TRUE;									
			}
			else
			{
				active=FALSE;									
			}

			return 0;										
			}

		case WM_SYSCOMMAND:									
			{
			switch (wParam)										
			{
				case SC_SCREENSAVE:									
				case SC_MONITORPOWER:								
					return 0;										
			}
			break;											
			}

		case WM_CLOSE:										
			{
			PostQuitMessage(0);									
			return 0;										
			}

		case WM_KEYDOWN:									
			{
			keys[wParam] = TRUE;								
			return 0;										
			}

		case WM_KEYUP:										
			{
			keys[wParam] = FALSE;								
			return 0;										
			}

		case WM_SIZE:										
			{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  			
			return 0;										
			}
	}

		return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,HINSTANCE	hPrevInstance,LPSTR lpCmdLine,	int	nCmdShow)			
{
	MSG		msg;										
	BOOL	done=FALSE;								
	fullscreen=FALSE;
	if (!CreateGLWindow("NeHe's OpenGL Framework",640,480,16,fullscreen))
	{
		return 0;										
	}

	while(!done)										
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))			
		{
			if (msg.message==WM_QUIT)							
			{
				done=TRUE;										
			}
			else												
			{
				TranslateMessage(&msg);								
				DispatchMessage(&msg);							
			}
		}
		else												
		{
				if (active)											
				{
				if (keys[VK_ESCAPE])								
				{
					done=TRUE;										
				}
				else												
				{
					DrawGLScene();										
					SwapBuffers(hDC);				
					if(keys[VK_RIGHT])
					{
						scena.addHangle(-0.7);
					}

					if(keys[VK_LEFT])
					{
						scena.addHangle(0.7);
					}

					if(keys[VK_UP])
					{
						scena.step(1);
					}

					if(keys[VK_DOWN])
					{
						scena.step(-1);
					}
				}
			}

			if (keys[VK_F1])									
			{
				keys[VK_F1]=FALSE;									
				KillGLWindow();										
				fullscreen=!fullscreen;												
				if (!CreateGLWindow("NeHe's OpenGL Framework",640,480,16,fullscreen))
				{
					return 0;										
				}
			}
		}
	}

		KillGLWindow();										
		return (msg.wParam);							
}
