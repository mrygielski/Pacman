#ifndef __FONTS
#define __FONTS
#include <conio.h>
#include <stdio.h> 
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <time.h>

void piszTXT(GLfloat x,GLfloat y,float odleglosc,GLfloat rozmiarx,float rozmiary,int r, int g, int b, int a,
				GLuint tekstura,char* control,...);



void litera(int jaki_znak,GLfloat gdzie_x,
				   GLfloat gdzie_y,GLfloat rozmiarx,float rozmiary,GLuint textura,int r, int g, int b,int a)
{
	if (jaki_znak<0) return;
	if (jaki_znak-32>0)
	{	
	GLfloat x1=0,x2=16,y1=0,y2=16.0f;
	int znak=0;
	do
	{
		if (x2 != 256)
		{
			x1+=16;
			x2+=16;
			znak=znak+1;
		}
		else
		{
			x1=0;x2=16;
			y1+=16;
			y2+=16;
			znak=znak+1;
		};
	}
	while(znak+32!=jaki_znak);
	y1=256-y1;
	y2=256-y2;
    glColor4ub(r,g,b,a);
	glBindTexture(GL_TEXTURE_2D, textura);// Tekstura z fontem
	glBegin(GL_QUADS);
		glTexCoord2f(x1/256, y2/256); glVertex2f(gdzie_x, gdzie_y-rozmiary);
		glTexCoord2f(x2/256, y2/256); glVertex2f(gdzie_x+rozmiarx, gdzie_y -rozmiary);
		glTexCoord2f(x2/256, y1/256); glVertex2f(gdzie_x+rozmiarx, gdzie_y);
		glTexCoord2f(x1/256, y1/256); glVertex2f(gdzie_x, gdzie_y);
	glEnd();
	}
}

void piszTXT(GLfloat x,GLfloat y,float odleglosc,GLfloat rozmiarx,float rozmiary,int r, int g, int b,int a,
				GLuint tekstura,char* control,...)
{
	char buf[1000];
    va_list args;
    va_start(args, control);
	vsprintf(buf,control,args);
    va_end(args);
	char *str=buf;
	GLfloat XXX = x;
	while(*str!=0)
	{
		litera(*str,XXX,y,rozmiarx,rozmiary,tekstura,r,g,b,a);
		XXX+=odleglosc;
		str++;
	}
}

#endif