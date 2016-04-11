
//Micha³ 'REGi' Rygielski
//http://regi.gamedev.pl
//mrygielski@o2.pl

#include <windows.h>	
#include <gl\gl.h>	
#include <time.h>


#include "_include\api_.h"
#include "_include\bmp_.h"
#include "_include\variables_.h"
#include "_include\class_.h"
#include "_include\fps_.h"
#include "_include\other_.h"
#include "_include\fonts_.h"
#include "_include\procedure_.h"
#include "_include\init_.h"









void DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	

	glTranslatef(-9.1f,-8.7f,0);

	//glTranslatef(0,0,-22);

	ShowText();

//	ShowBackground();

	glPushMatrix();	
	
	//for (i=0; i<ilosc_blokow; i++)	blok[i].Block(blok[i].x,blok[i].y,0,3.3f,1,1,texture[blok[i].type]);
	
	//player.Block(move_x-0.5f,-11,0,5,1,1,texture[0]);
//	player.Block(-13.5f,-2.5f-move_y,0,1,5,1,texture[0]);


    for (i=0; i<19; i++)
	for (j=0; j<15; j++) {
	  /*if (mapa[j][i]!=0) */
		if (mapa[j][i]==0) Wall((float)i, (float)j, -1, 1, 1, 1, texture[mapa[j][i]]);
		if (mapa[j][i]==9) Wall((float)i, (float)j, -1, 1, 1, 1, texture[mapa[j][i]]);
		if (mapa[j][i]!=200 && mapa[j][i]!=0 && mapa[j][i]!=9) Wall((float)i, (float)j, 1, 1, 1, 1, texture[mapa[j][i]]);
		//if (mapa[j][i]==0) Wall((float)i, (float)j, -1, 1, 1, 1, texture[mapa[j][i]]);
		//else Wall((float)i, (float)j, 1, 1, 1, 1, texture[mapa[j][i]]);
	}




    if (mR) {
		xx=tmX;
		if (BadajTablice((int)PlayerY,(int)PlayerX+1,1)) tmX+=steps;
		if(tmX>=1.0+PlayerX+steps) { tmX=xx; PlayerX+=1; mR=0; }
	}

    if (mL) {
		xx=tmX;
		if (BadajTablice((int)PlayerY,(int)PlayerX-1,1)) tmX-=steps;
		if(tmX<=-1.0-steps+PlayerX) { tmX=xx; PlayerX-=1; mL=0; }		
	}

    if (mU) {
		yy=tmY;
		if (BadajTablice((int)PlayerY+1,(int)PlayerX,1)) tmY+=steps;
		if(tmY>=1.0+steps+PlayerY) { tmY=yy; PlayerY+=1; mU=0; }
	}

    if (mD) {
		yy=tmY;
		if (BadajTablice((int)PlayerY-1,(int)PlayerX,1)) tmY-=steps;
		if(tmY<=-1.0-steps+PlayerY) { tmY=yy; PlayerY-=1; mD=0; }
	}


	if (moveRIGHT && BadajTablice((int)PlayerY,(int)PlayerX+1,1) && !mL && !mU && !mD) {
	  mR=1;
	}
	if (moveLEFT && BadajTablice((int)PlayerY,(int)PlayerX-1,1) && !mR && !mU && !mD) {
		mL=1;
	}
	if (moveUP && BadajTablice((int)PlayerY+1,(int)PlayerX,1) && !mL && !mR && !mD) {
	  mU=1;
	}
	if (moveDOWN && BadajTablice((int)PlayerY-1,(int)PlayerX,1) && !mL && !mU && !mR) {
		mD=1;
	}


	//teleportacja
	if (!BadajTablice((int)PlayerY,(int)PlayerX,3)) { PlayerX=17; tmX=17; }
	if (!BadajTablice((int)PlayerY,(int)PlayerX,4)) { PlayerX=1; tmX=1; }




	if (keys[VK_RIGHT] && !moveDOWN && !moveUP && !moveLEFT) {
	  moveRIGHT=1;
	  text_p=2;
	} else moveRIGHT=0;
	if (keys[VK_LEFT] && !moveDOWN && !moveUP && !moveRIGHT) {
	  moveLEFT=1;
	  text_p=11;
	} else moveLEFT=0;
	if (keys[VK_UP] && !moveDOWN && !moveRIGHT && !moveLEFT) {
	  moveUP=1;
	  text_p=12;
	} else moveUP=0;
	if (keys[VK_DOWN] && !moveUP && !moveRIGHT && !moveLEFT) {
	  moveDOWN=1;
	  text_p=13;
	} else moveDOWN=0;


	if (mapa[(int)PlayerY][(int)PlayerX]==0) {
		mapa[(int)PlayerY][(int)PlayerX]=200;
		ilosc_star+=1;
	}
	
	if (mapa[(int)PlayerY][(int)PlayerX]==9) {
		mapa[(int)PlayerY][(int)PlayerX]=200;
		czas_on=1;
	}

	if (czas_on) {
		for (i=0; i<4; i++) enemy[i].t=10;
		czas++;
		if (czas>300) {
			czas_on=0;
			czas=0;
			enemy[0].t=5;
			enemy[1].t=6;
			enemy[2].t=7;
			enemy[3].t=8;
		}

	}


	if (czas_on) {
		for (i=0; i<4; i++) if (PlayerX==enemy[i].PlayerX && PlayerY==enemy[i].PlayerY) {
			enemy[i].PlayerX=9;
			enemy[i].PlayerY=8;
			enemy[i].tmX=9;
			enemy[i].tmY=8;
		    enemy[i].moveUP=0;
		    enemy[i].moveDOWN=0;
		    enemy[i].moveRIGHT=0;
	 	    enemy[i].moveLEFT=0;
	 	    enemy[i].mR=0;
	 	    enemy[i].mL=0;
	 	    enemy[i].mU=0;
		    enemy[i].mD=0;
		}
	} else {
		for (i=0; i<4; i++) if (PlayerX==enemy[i].PlayerX && PlayerY==enemy[i].PlayerY) {
			player_die=1;
		}
	}

	if (player_die) {
  	  PlayerX=9;
	  PlayerY=5;
	  tmX=9;
	  tmY=5;
	  ilosc_zyc--;	
	  player_die=0;
      moveUP=0;
	  moveDOWN=0;
	  moveRIGHT=0;
	  moveLEFT=0;
      mR=0;
	  mL=0;
	  mU=0;
	  mD=0;
	}

    for (i=0; i<4; i++) enemy_ai(i);


	for (i=0; i<4; i++) enemy[i].Ghost(enemy[i].tmX,enemy[i].tmY,enemy[i].t);


	glPushMatrix();


	
	Wall((float)tmX, (float)tmY, 0.8f, 0.8f, 1, 1, texture[text_p]);
    glPopMatrix();
	
	glPopMatrix();
}


void DrawGLMenu(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	

	glTranslatef(0,0,0);


	ShowMenu();

	glPushMatrix();	
	
	glPushMatrix();

    glPopMatrix();
	
	glPopMatrix();
}



int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
		


	if (CreateGLWindow("PACMAN v1.0",640,480,16,fullscreen)==FALSE) return 0;


	

	InitTextures();

	InitGame();

   
	menu_texture=15;
	while(!done)
	{if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){if (msg.message==WM_QUIT){done=TRUE;}else{TranslateMessage(&msg);DispatchMessage(&msg);}}else
	
	{
		if (keys[VK_UP]) menu_texture=15;
		if (keys[VK_DOWN]) menu_texture=14;
		
		DrawGLMenu();
		Draw_FPS();


		if (keys[VK_RETURN] && (menu_texture==15)) {
			
			    init_enemy();
 
		

				InitGame();
				
				done2=false;


				PlayerX=3;
				PlayerY=3;

				tmX=3;
				tmY=3;

				while(!done2)
				{if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){if (msg.message==WM_QUIT){done2=TRUE;}else{TranslateMessage(&msg);DispatchMessage(&msg);}}else
				
				{
					DrawGLScene();
					Draw_FPS();

					SwapBuffers(hDC);


					if (keys[VK_ESCAPE] || ilosc_star==89 || ilosc_zyc==0)
					{
						done2=TRUE;
					}

				}}


		}



		SwapBuffers(hDC);

		if (keys[VK_RETURN] && (menu_texture==14)) // wyjscie
		{
			done=TRUE;
					
		}
		
	}}






	KillGLWindow(); 
	return (msg.wParam);	
	
	

	

		




	KillGLWindow(); 
	return (msg.wParam);
}