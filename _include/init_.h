void InitTextures()
{
	texture[0]=LoadTexture("gfx/star.bmp");
	texture[1]=LoadTexture("gfx/wall.bmp");
	texture[2]=LoadTexture("gfx/p1.bmp");
	texture[3]=LoadTexture("gfx/arrow_left.bmp");
	texture[4]=LoadTexture("gfx/arrow_right.bmp");
	texture[5]=LoadTexture("gfx/ghost1.bmp");
	texture[6]=LoadTexture("gfx/ghost2.bmp");
	texture[7]=LoadTexture("gfx/ghost3.bmp");
	texture[8]=LoadTexture("gfx/ghost4.bmp");
	texture[9]=LoadTexture("gfx/piorun.bmp");
	texture[10]=LoadTexture("gfx/ghost.bmp");
	texture[11]=LoadTexture("gfx/p2.bmp");
	texture[12]=LoadTexture("gfx/p3.bmp");
	texture[13]=LoadTexture("gfx/p4.bmp");
	texture[14]=LoadTexture("gfx/menu1.bmp");
	texture[15]=LoadTexture("gfx/menu2.bmp");
	fonttext=LoadTexture("gfx/fonts.bmp");
}



void InitGame()
{
	glClearColor(0,0,0,0);

	TimerInit(); // inicjowanie zegara do funkcji FPS
	framerate=.01f;

}

