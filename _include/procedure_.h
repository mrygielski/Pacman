
int Rectangle(float x1, float y1, float z1, float x2, float y2, float z2,
              float x3, float y3, float z3, float x4, float y4, float z4, int texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_STRIP);
	    glTexCoord2f(1,0);glVertex3f(x1,y1,z1);
	    glTexCoord2f(1,1);glVertex3f(x2,y2,z2);
	    glTexCoord2f(0,0);glVertex3f(x3,y3,z3);
	    glTexCoord2f(0,1);glVertex3f(x4,y4,z4);
    glEnd();
	return true;
}


int Wall(float x1, float y1, float z1, float width, float height, float thickness, int texture)
{
	{
   
		glPushMatrix();


		glTranslatef(0,y1,0);

//		glRotatef(rott,1,0,0);
    
		glPushMatrix();
    
    

		glTranslatef(x1-(width/2),-(height/2),z1-(thickness/2)); 

		glColor4ub(255,255,255,255);

		Rectangle(0,0,0, width, 0, 0,
				  0,0+height,0, width,0+height,0, texture);

		Rectangle(0,0,0+thickness, 0+width, 0, 0+thickness,
				  0,0+height,0+thickness, 0+width,0+height,0+thickness, texture);

		Rectangle(0,0+height,0, 0+width,0+height,0,
				  0,0+height,0+thickness, 0+width,0+height,0+thickness, texture);

		Rectangle(0,0,0, 0+width,0,0,
				  0,0,0+thickness, 0+width,0,0+thickness, texture);


		Rectangle(0,0,0, 0, 0, 0+thickness,
				  0, 0+height, 0, 0, 0+height, 0+thickness, texture);

		Rectangle(0+width,0,0, 0+width, 0, 0+thickness,
				  0+width, 0+height, 0, 0+width, 0+height, 0+thickness, texture);


		
		glPopMatrix();

	   glPopMatrix();

	}

   return true;

}

void ShowBackground()
{
	glBindTexture(GL_TEXTURE_2D, texture[3]);		
	glBegin(GL_QUADS);								
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-16.1f, -11.4f,  -1.0f);	
		glTexCoord2f(4.0f, 0.0f); glVertex3f( 16.1f, -11.4f,  -1.0f);	
		glTexCoord2f(4.0f, 4.0f); glVertex3f( 16.1f,  11.4f,  -1.0f);	
		glTexCoord2f(0.0f, 4.0f); glVertex3f(-16.1f,  11.4f,  -1.0f);
	glEnd();
}

void ShowMenu()
{
	glBindTexture(GL_TEXTURE_2D, texture[menu_texture]);		
	glBegin(GL_QUADS);								
		glTexCoord2f(0, 0); glVertex3f(-10.1f, -10,  1.0f);	
		glTexCoord2f(1, 0); glVertex3f( 10.1f, -10,  1.0f);	
		glTexCoord2f(1, 1); glVertex3f( 10.1f,  10,  1.0f);	
		glTexCoord2f(0, 1); glVertex3f(-10.1f,  10,  1.0f);
	glEnd();						



}


void ShowText()
{

	piszTXT(0.0, 17.5f ,0.8f,1.2f,1.2f,255,255,255,255,fonttext,"gwizadki=%d",ilosc_star);
	piszTXT(0.0, 16.5f ,0.8f,1.2f,1.2f,255,255,255,255,fonttext,"zycia=%d",ilosc_zyc);
	
}



int BLOCK::Ghost(float x, float y, int t) {
	glPushMatrix();	
    Wall((float)x, (float)y, 0.8f, 0.8f, 1, 1, texture[t]);
	glPopMatrix();	
    return true;
}



int enemy_ai(int i) { // inteligencja wroga
    if (enemy[i].mR) {
		enemy[i].xx=enemy[i].tmX;
		if (BadajTablice((int)enemy[i].PlayerY,(int)enemy[i].PlayerX+1,1)) enemy[i].tmX+=steps;
		if(enemy[i].tmX>=1.0+enemy[i].PlayerX+steps) { enemy[i].tmX=enemy[i].xx; enemy[i].PlayerX+=1; enemy[i].mR=0; }
	}

    if (enemy[i].mL) {
		enemy[i].xx=enemy[i].tmX;
		if (BadajTablice((int)enemy[i].PlayerY,(int)enemy[i].PlayerX-1,1)) enemy[i].tmX-=steps;
		if(enemy[i].tmX<=-1.0-steps+enemy[i].PlayerX) { enemy[i].tmX=enemy[i].xx; enemy[i].PlayerX-=1; enemy[i].mL=0; }		
	}

    if (enemy[i].mU) {
		enemy[i].yy=enemy[i].tmY;
		if (BadajTablice((int)enemy[i].PlayerY+1,(int)enemy[i].PlayerX,1)) enemy[i].tmY+=steps;
		if(enemy[i].tmY>=1.0+steps+enemy[i].PlayerY) { enemy[i].tmY=enemy[i].yy; enemy[i].PlayerY+=1; enemy[i].mU=0; }
	}

    if (enemy[i].mD) {
		enemy[i].yy=enemy[i].tmY;
		if (BadajTablice((int)enemy[i].PlayerY-1,(int)enemy[i].PlayerX,1)) enemy[i].tmY-=steps;
		if(enemy[i].tmY<=-1.0-steps+enemy[i].PlayerY) { enemy[i].tmY=enemy[i].yy; enemy[i].PlayerY-=1; enemy[i].mD=0; }
	}


	if (enemy[i].moveRIGHT && BadajTablice((int)enemy[i].PlayerY,(int)enemy[i].PlayerX+1,1) && !enemy[i].mL && !enemy[i].mU && !enemy[i].mD) {
	  enemy[i].mR=1;
	}
	if (enemy[i].moveLEFT && BadajTablice((int)enemy[i].PlayerY,(int)enemy[i].PlayerX-1,1) && !enemy[i].mR && !enemy[i].mU && !enemy[i].mD) {
	  enemy[i].mL=1;
	}
	if (enemy[i].moveUP && BadajTablice((int)enemy[i].PlayerY+1,(int)enemy[i].PlayerX,1) && !enemy[i].mL && !enemy[i].mR && !enemy[i].mD) {
	  enemy[i].mU=1;      
	} 
	if (enemy[i].moveDOWN && BadajTablice((int)enemy[i].PlayerY-1,(int)enemy[i].PlayerX,1) && !enemy[i].mL && !enemy[i].mU && !enemy[i].mR) {
      enemy[i].mD=1;
	}

	if (enemy[i].los==2 && enemy[i].mL && enemy[i].mR && enemy[i].mD && !enemy[i].mU) {
	 enemy[i].los=3;
	}

	//teleportacja
	if (!BadajTablice((int)enemy[i].PlayerY,(int)enemy[i].PlayerX,3)) { enemy[i].PlayerX=17; enemy[i].tmX=17; }
	if (!BadajTablice((int)enemy[i].PlayerY,(int)enemy[i].PlayerX,4)) { enemy[i].PlayerX=1; enemy[i].tmX=1; }


	randomize();
	enemy[i].los=rand()%10;

    
	
	if (enemy[i].los==0 && !enemy[i].moveDOWN && !enemy[i].moveUP && !enemy[i].moveLEFT) {
	  enemy[i].moveRIGHT=1;
	} else enemy[i].moveRIGHT=0;
	if (enemy[i].los==1 && !enemy[i].moveDOWN && !enemy[i].moveUP && !enemy[i].moveRIGHT) {
	  enemy[i].moveLEFT=1;
	} else enemy[i].moveLEFT=0;
	if (enemy[i].los==2 && !enemy[i].moveDOWN && !enemy[i].moveRIGHT && !enemy[i].moveLEFT) {
	  enemy[i].moveUP=1;
    } else { enemy[i].moveUP=0; }
	if (enemy[i].los==3 && !enemy[i].moveUP && !enemy[i].moveRIGHT && !enemy[i].moveLEFT) {
	  enemy[i].moveDOWN=1;
	} else { enemy[i].moveDOWN=0;}

   
	
	return true;
}

int init_enemy() { // ustawianie pozycji i parametrow przeciwnikow
	randomize();
	enemy[0].los=rand()%4;
	enemy[0].stoi=false;

	enemy[0].PlayerX=15;
	enemy[0].PlayerY=8;
	enemy[0].tmX=15;
	enemy[0].tmY=8;
	enemy[0].t=5;

	randomize();
	enemy[1].los=rand()%4;
	enemy[1].stoi=false;

	enemy[1].PlayerX=8;
	enemy[1].PlayerY=5;
	enemy[1].tmX=8;
	enemy[1].tmY=5;
	enemy[1].t=6;

	randomize();
	enemy[2].los=rand()%4;
	enemy[2].stoi=false;

	enemy[2].PlayerX=3;
	enemy[2].PlayerY=10;
	enemy[2].tmX=3;
	enemy[2].tmY=10;
	enemy[2].t=7;

	randomize();
	enemy[3].los=rand()%4;
	enemy[3].stoi=false;

	enemy[3].PlayerX=15;
	enemy[3].PlayerY=11;
	enemy[3].tmX=15;
	enemy[3].tmY=11;
    enemy[3].t=8;

	return true;
}