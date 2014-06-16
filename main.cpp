/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "obiekt1.h"
#include "obiekt2.h"
#include "obiekt3.h"
#include "obiekt4.h"
#include "obiekt5.h"
#include "obiekt6.h"


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

Obiekt1 obj1(0.0f, 1.0f, 0.0f);
Obiekt2 obj2(-3.0f, 1.0f, 0.0f);
Obiekt3 obj3(3.0f, 1.0f, 0.0f);
Obiekt4 obj4(0.0f, 4.0f, 0.0f);
Obiekt5 obj5(-3.0f, 4.0f, 0.0f);
Obiekt6 obj6(3.0f, 4.0f, 0.0f);

void listy(void) 
{ 
    glNewList(1, GL_COMPILE); //przód szeœcianu
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-SIZE, SIZE, SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(SIZE, SIZE, SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(7, GL_COMPILE); //prawy górny trójk¹t
        glBegin(GL_TRIANGLES);
        glNormal3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(1.0f, 1.0f, -1.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(1.0f, 1.0f, 1.0f);
        glVertex3f(SIZE, SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(8, GL_COMPILE); //prawy dolny trojkat
        glBegin(GL_TRIANGLES);
        glNormal3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, -1.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(9, GL_COMPILE); // pionowa sciana obiekt2
        glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(SIZE, SIZE, SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
        glEnd();
    glEndList();
    
    glNewList(10, GL_COMPILE); //lewy gorny trojkat
        glBegin(GL_TRIANGLES);
        glNormal3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(1.0f, 1.0f, -1.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-SIZE, SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(11, GL_COMPILE); //lewy dolny trojkat
        glBegin(GL_TRIANGLES);
        glNormal3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, -1.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glNormal3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(12, GL_COMPILE); // pionowa sciana obiekt3 
        glBegin(GL_QUADS);
        glNormal3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-SIZE, SIZE, SIZE);
        glNormal3f(1.0f, 1.0f, 1.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glNormal3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(13, GL_COMPILE); // gora obiekt 4
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(14, GL_COMPILE); //lewa trojkatna sciana
        glBegin(GL_TRIANGLES);
        glNormal3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
        glNormal3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(15, GL_COMPILE); //prawa trojkatna sciana
        glBegin(GL_TRIANGLES);
        glNormal3f(1.0f, 1.0f, -1.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, -1.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glNormal3f(1.0f, -1.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
        glEnd();
    glEndList();
    
    glNewList(16, GL_COMPILE); //gora obiektu 5
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(SIZE, -SIZE, SIZE);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
        glEnd();
    glEndList();
    
    glNewList(17, GL_COMPILE); //gora obiektu 6
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-SIZE, -SIZE, SIZE);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glEnd();
    glEndList();
    
    glNewList(18, GL_COMPILE); //tylni prawy trojkat
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
        glEnd();
    glEndList();
    
    glNewList(19, GL_COMPILE); //tylni lewy trojkat
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-SIZE, SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(SIZE, -SIZE, -SIZE);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-SIZE, -SIZE, -SIZE);
        glEnd();
    glEndList();
}


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 800, 600,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            
            glPushMatrix ();
            glRotated(theta, 0.0, 1.0, 0.0);
            //*
            glBegin (GL_QUADS);
            glColor3f(0.0f, 0.0f, 1.0f);
            glNormal3d(-1.0, 1.0, -1.0);
            glVertex3f(-20.0, 0.0, -20.0); // lewy tyl
            glNormal3d(1.0, 1.0, -1.0);
            glVertex3f(20.0, 0.0, -20.0); 
            glNormal3d(1.0, 1.0, 1.0);
            glVertex3f(20.0, 0.0, 20.0);
            glNormal3d(-1.0, 1.0, 1.0);
            glVertex3f(-20.0, 0.0, 20.0);
            glEnd();
            //*/
            //glColor3f(1.0f, 0.0f, 0.0f);
            
            obj1.draw(ALL);
            obj1.reset();
            obj2.draw(ALL);
            obj2.reset();
            obj3.draw(ALL);
            obj3.reset();
            obj4.draw(ALL);
            obj4.reset();
            obj5.draw(ALL);
            obj5.reset();
            obj6.draw(ALL);
            obj6.reset();
            
            glPopMatrix ();
            //Sleep(1);
            theta += 0.2;
            SwapBuffers (hDC);
            
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
    
    //*****
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glShadeModel(GL_SMOOTH);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55, 4.0/3.0, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    listy();
}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
