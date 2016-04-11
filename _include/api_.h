#ifndef __API_
#define __API_

#include <windows.h>	
#include <gl\gl.h>		
#include <gl\glu.h>		
#include "_include\glaux.h"


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
GLvoid ReSizeGLScene(GLsizei,GLsizei);
int InitGL(GLvoid);
GLvoid KillGLWindow(GLvoid);
BOOL CreateGLWindow(char*,int,int,int,bool);


HDC			hDC=NULL;		
HGLRC		hRC=NULL;		
HWND		hWnd=NULL;		
HINSTANCE	hInstance;		
bool	fullscreen=TRUE;	
bool	keys[256], keydown[256];
bool	active=TRUE, LBM;		
int mouseX, mouseY;




int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.5, 1.0, 0.0);	
	glAlphaFunc(GL_GREATER, 0.0f);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	
	return TRUE;										
}


LRESULT CALLBACK WndProc(	HWND	hWnd,	
							UINT	uMsg,	
							WPARAM	wParam,	
							LPARAM	lParam)	
{
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

		case WM_MOUSEMOVE:
		{
			mouseX = LOWORD(lParam); 
			mouseY = HIWORD(lParam);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			LBM=true;
			return 0;
		}
		case WM_LBUTTONUP:
		{
			LBM=false;
			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
   if (height==0)			
    {
  	  height=1;			
    }

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);	
    glLoadIdentity();		

	// tryb z perspektyw¹ 3D 
    //gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	// tryb 2d  
	gluOrtho2D(-10.0f, 10.0f,-10.0f, 10.0f );
	
	
    glMatrixMode(GL_MODELVIEW);	
    glLoadIdentity();	

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
			MessageBox(NULL,"B£¥D #1","",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))					
		{
			MessageBox(NULL,"B£¥D #2","",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;									
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					
	{
		MessageBox(NULL,"B£¥D #3","",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										
	}

	if (hWnd && !DestroyWindow(hWnd))					
	{
		MessageBox(NULL,"B£¥D #4","Nie mozna zniszczyc okna!",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;									
	}

	if (!UnregisterClass("OpenGL",hInstance))		
	{
		MessageBox(NULL,"B£¥D #5","Nie mozna wyrejestrowac klasy",MB_OK | MB_ICONINFORMATION);
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
		MessageBox(NULL,"Nie mo¿na zarejestrowac okna!","ERROR",MB_OK|MB_ICONEXCLAMATION);
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
			if (MessageBox(NULL,"Nie ma wybranego trybu pe³noekranowego!\nCzy uruchomiæ program w oknie?","Pytanie?",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;	
			}
			else
			{
				MessageBox(NULL,"Program zostanie zakoñczony!","ERROR",MB_OK|MB_ICONSTOP);
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

	if (!(hWnd=CreateWindowEx(	dwExStyle,							
								"OpenGL",							
								title,								
								dwStyle |							
								WS_CLIPSIBLINGS |					
								WS_CLIPCHILDREN,					
								0, 0,								
								WindowRect.right-WindowRect.left,	
								WindowRect.bottom-WindowRect.top,	
								NULL,								
								NULL,								
								hInstance,							
								NULL)))								
	{
		KillGLWindow();								
		MessageBox(NULL,"B³¹d podczas tworzenia okna!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	static	PIXELFORMATDESCRIPTOR pfd=				
	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,											
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |						
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,								
		bits,										
		0, 0, 0, 0, 0, 0,							
		0,											
		0,											
		0,											
		0, 0, 0, 0,									
		16,											
		0,											
		0,											
		PFD_MAIN_PLANE,								
		0,											
		0, 0, 0										
	};
	
	if (!(hDC=GetDC(hWnd)))							
	{
		KillGLWindow();								
		MessageBox(NULL,"B£¥D #6","Brak urzadzenia",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		KillGLWindow();								
		MessageBox(NULL,"B£¥D #7","Nie ma takiego trybu!",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		
	{
		KillGLWindow();								
		MessageBox(NULL,"B£¥D #8","Nie mozna uruchomic tego trybu",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(hRC=wglCreateContext(hDC)))				
	{
		KillGLWindow();								
		MessageBox(NULL,"B£¥D #9","Nie mozna pobrac rendering context",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!wglMakeCurrent(hDC,hRC))					
	{
		KillGLWindow();								
		MessageBox(NULL,"B£¥D #10","Nie mozna aktywowac rendering context",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	ShowWindow(hWnd,SW_SHOW);						
	SetForegroundWindow(hWnd);						
	SetFocus(hWnd);									
	ReSizeGLScene(width, height);					

	if (!InitGL())									
	{
		KillGLWindow();								
		MessageBox(NULL,"Inicjalizacja nie powiod³a siê!","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	return TRUE;									
}



#endif
