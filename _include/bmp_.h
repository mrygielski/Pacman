
AUX_RGBImageRec *LoadBMP(char *Filename) 
{
	AUX_RGBImageRec* text;
	text=auxDIBImageLoad(Filename);
	return text;
};

GLuint LoadTexture(char* plik)
{
	AUX_RGBImageRec *TextureImage[1];
	GLuint textura[1];
	if (TextureImage[0]=LoadBMP(plik))
	{
		glGenTextures(1, &textura[0]);
		glBindTexture(GL_TEXTURE_2D, textura[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
			TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, 
			GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	free(TextureImage[0]);
	return textura[0];
}