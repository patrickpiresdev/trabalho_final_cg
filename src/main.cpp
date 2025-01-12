#include <stdio.h>
#include "GL/freeglut.h"
#include "RgbImage.h"
#define CAMERA_ROTATION_MODE '1'
#define CLAMP_MOVEMENT_MODE '2'

char movement_mode = CAMERA_ROTATION_MODE;
float rot_x = 0, rot_y = 0;
int nail_angle = -45;

char* RUGGED_TEXTURE_FILENAME = "./textures/rugged_metal.bmp";
char* RUSTED_TEXTURE_FILENAME = "./textures/rusted_metal.bmp";
char* GOLDEN_TEXTURE_FILENAME = "./textures/golden_metal.bmp";
char* GLASS_TEXTURE_FILENAME = "./textures/glass.bmp";
char* METAL_TEXTURE_FILENAME = "./textures/metal.bmp";

GLuint RUGGED_TEXTURE_ID;
GLuint RUSTED_TEXTURE_ID;
GLuint GOLDEN_TEXTURE_ID;
GLuint GLASS_TEXTURE_ID;
GLuint METAL_TEXTURE_ID;

GLUquadric* RUGGED_QUAD;
GLUquadric* RUSTED_QUAD;
GLUquadric* GOLDEN_QUAD;
GLUquadric* GLASS_QUAD;

//Makes the image into a texture, and returns the id of the texture
GLuint load_texture(char* filename)
{
	GLuint textureId;

	RgbImage theTexMap(filename); //Image with texture

	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);	//Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,	//Always GL_TEXTURE_2D
		0,						//0 for now
		GL_RGB,					//Format OpenGL uses for image
		theTexMap.GetNumCols(),	//Width 
		theTexMap.GetNumRows(),	//Height
		0,						//The border of the image
		GL_RGB,					//GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,		//GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
		theTexMap.ImageData()
	);	//The actual pixel data

	return textureId; //Returns the id of the texture
}


void grid()
{
	glLineWidth(2);
	glBegin(GL_LINES);
	for (int i = -100; i <= 100; i++)
	{
		glVertex3f(i, 0, -100);
		glVertex3f(i, 0, 100);
		glVertex3f(-100, 0, i);
		glVertex3f(100, 0, i);
	}
	glEnd();
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	float ambient[] = {0.5, 0.5, 0.5, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	glEnable(GL_LIGHT0);

	float light0_ambient[] = {0.1, 0.1, 0.1, 1};
	float light0_diffuse[] = {0.8, 0.8, 0.8, 1};
	float light0_specular[] = {1, 1, 1, 1};
	float light0_position[] = {0, 0, 1, 1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	RUGGED_TEXTURE_ID = load_texture(RUGGED_TEXTURE_FILENAME);
	RUSTED_TEXTURE_ID = load_texture(RUSTED_TEXTURE_FILENAME);
	GOLDEN_TEXTURE_ID = load_texture(GOLDEN_TEXTURE_FILENAME);
	GLASS_TEXTURE_ID  = load_texture(GLASS_TEXTURE_FILENAME);
	METAL_TEXTURE_ID  = load_texture(METAL_TEXTURE_FILENAME);

	RUGGED_QUAD = gluNewQuadric();
	RUSTED_QUAD = gluNewQuadric();
	GOLDEN_QUAD = gluNewQuadric();
	GLASS_QUAD = gluNewQuadric();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DesenhaCubo(GLuint _textureId, float lenghtX, float lenghtY, float height)
{
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);			// Face posterior
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, -height);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, -height);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(lenghtX, lenghtY, -height);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, -height);
	glEnd();
	glBegin(GL_QUADS);			// Face frontal
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, height);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, height);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lenghtX, lenghtY, height);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, height);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, -height);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, height);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, height);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, -height);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral direita
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, -height);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lenghtX, lenghtY, -height);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(lenghtX, lenghtY, height);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, height);
	glEnd();
	glBegin(GL_QUADS);			// Face superior
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, -height);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-lenghtX, lenghtY, height);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(lenghtX, lenghtY, height);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(lenghtX, lenghtY, -height);
	glEnd();
	glBegin(GL_QUADS);			// Face inferior
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-lenghtX, -lenghtY, -height);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(lenghtX, -lenghtY, -height);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, height);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, height);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Fun��o que desenha um bast�o com uma luz no final
void DesenhaBastao(float diam_start, float diam_end, float lenght, float radius, int color)
{
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, GOLDEN_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(GOLDEN_QUAD, TRUE);
	gluCylinder(GOLDEN_QUAD, diam_start, diam_end, lenght, 72, 72);
	glTranslatef(0.0f, 0.0f, lenght+radius);
	switch (color)
	{
	case 1:
		glColor4f(1.0f, 0.0f, 0.0f, 0.7f);
		break;
	case 2:
		glColor4f(0.0f, 1.0f, 0.0f, 0.7f);
		break;
	case 3:
		glColor4f(0.0f, 0.0f, 1.0f, 0.7f);
		break;
	case 4:
		glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
		break;
	}
	glBindTexture(GL_TEXTURE_2D, GLASS_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(GLASS_QUAD, TRUE);
	gluSphere(GLASS_QUAD, radius, 72, 72);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DesenhaParteCoroa(float base, float top, float length, float height)
{
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, GOLDEN_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-base, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-top, length, height);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(top, length, height);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(base, 0, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void cabeca()
{
	// Desenha pesco�o (cone)
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, RUGGED_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(RUGGED_QUAD, TRUE);
	gluCylinder(RUGGED_QUAD, 10.0f, 7.5f, 21.5f, 72, 72);
	glTranslatef(0.0f, 0.0f, 21.5f);

	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, RUSTED_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(RUSTED_QUAD, TRUE);
	gluCylinder(RUSTED_QUAD, 7.5f, 2.0f, 17.0f, 72, 72);
	glPopMatrix();
	glTranslatef(0.0f, 37.0f, 0.0f);

	// Desenha haste para os olhos (paralelepipedo)
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	DesenhaCubo(GOLDEN_TEXTURE_ID, 30.0f, 3.0f, 1.5f);

	// Desenha olhos (esferas)
	glColor4f(1.0f, 1.0f, 0.3f, 0.8f);
	glPushMatrix();
	glTranslatef(-25.0, 0, 2.0);
	glBindTexture(GL_TEXTURE_2D, GLASS_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(GLASS_QUAD, TRUE);
	gluSphere(GLASS_QUAD, 3.0f, 72, 72);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25.0, 0, 2.0);
	glBindTexture(GL_TEXTURE_2D, GLASS_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(GLASS_QUAD, TRUE);
	gluSphere(GLASS_QUAD, 3.0f, 72, 72);
	glPopMatrix();

	// Desenha bast�es (cilindros e esferas)
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(165.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(210.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(255.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(300.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 0.0f);
	glRotatef(345.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 25.0f, 1.5, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(15.0f, 2.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 5.0f, 1.5, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-15.0f, 2.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	DesenhaBastao(1.0f, 0.5f, 5.0f, 1.5, 4);
	glPopMatrix();

	// Desenha coroa
	glPushMatrix();
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, RUSTED_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0.0f, 0.0f, 3.0f);
	gluCylinder(RUSTED_QUAD, 0.1f, 10.0f, 2.0f, 72, 72);
	glTranslatef(0.0f, 0.0f, 2.0f);
	glBindTexture(GL_TEXTURE_2D, GOLDEN_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(GOLDEN_QUAD, TRUE);
	gluDisk(GOLDEN_QUAD, 0.0f, 10.0f, 72, 72);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	glPopMatrix();

	// Desenha as partes da coroa
	glPushMatrix();
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();
	glPushMatrix();
	glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();
	glPushMatrix();
	glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();
	glPushMatrix();
	glRotatef(165.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();
	glPushMatrix();
	glRotatef(210.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();
	glPushMatrix();
	glRotatef(255.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();
	glPushMatrix();
	glRotatef(300.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();
	glPushMatrix();
	glRotatef(345.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 5.0f, 9.0f);
	DesenhaParteCoroa(2.0f, 5.0f, 6.0f, 5.0f);
	glPopMatrix();

	// Desenha cabe�a (elipsoide transparente)
	glEnable(GL_CULL_FACE);
	glColor4f(0.4f, 0.4f, 0.4f, 0.5f);
	glPushMatrix();
	glScalef(1.0f, 0.4f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, GLASS_TEXTURE_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(GLASS_QUAD, TRUE);
	gluSphere(GLASS_QUAD, 40.0f, 72, 72);
	glDisable(GL_CULL_FACE);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void cylinder(GLuint texture_id)
{
	GLUquadric* quad = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(quad, TRUE);
	gluCylinder(quad, 1, 1, 1, 32, 32);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void cone(GLuint texture_id)
{
	GLUquadric* quad = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(quad, TRUE);
	gluCylinder(quad, 1, 0, 1, 32, 32);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void sphere(GLuint texture_id)
{
	GLUquadric* quad = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(quad, TRUE);
	gluSphere(quad, 1, 32, 32);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void trunk()
{
	glPushMatrix();
	glTranslatef(0, 0.2, 0);

	glPushMatrix();
	glTranslated(0, 1, 0);
	glScaled(1, 0.2, 1);
	sphere(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	cylinder(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glScaled(1, 0.2, 1);
	sphere(METAL_TEXTURE_ID);
	glPopMatrix();

	glPopMatrix();
}

void nail()
{
	glPushMatrix();
	glRotated(nail_angle, 0, 1, 0);

	glPushMatrix();
	glScaled(0.1, 0.1, 1);
	cylinder(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1);
	glRotated(45, 0, 1, 0);

	glPushMatrix();
	glScaled(0.1, 0.1, 0.1);
	sphere(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.1, 0.1, 1);
	cylinder(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1);
	glScaled(0.1, 0.1, 0.1);
	sphere(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1);
	glRotated(45, 0, 1, 0);
	glScaled(0.1, 0.1, 1);
	cone(METAL_TEXTURE_ID);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void clamp()
{
	glPushMatrix();
	glScaled(0.1, 0.1, 0.1);
	sphere(METAL_TEXTURE_ID);
	glPopMatrix();

	nail();

	glPushMatrix();
	glRotated(180, 0, 0, 1);
	nail();
	glPopMatrix();
}

void disk(GLuint texture_id)
{
	GLUquadric* quad = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(quad, TRUE);
	gluDisk(quad, 0, 1, 32, 32);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void arm()
{
	glPushMatrix();
	glScaled(0.3, 0.3, 0.3);
	sphere(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.3, 0.3, 2);
	cylinder(RUGGED_TEXTURE_ID);
	glPopMatrix();

	// lid
	glPushMatrix();
	glTranslated(0, 0, 2);
	glScaled(0.3, 0.3, 1);
	disk(METAL_TEXTURE_ID);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 2);
	glScaled(0.5, 0.5, 0.5);
	clamp();
	glPopMatrix();
}

void robot()
{
	/* glPushMatrix();
	glScalef(0.02, 0.02, 0.02);
	cabeca();
	glPopMatrix(); */

	// trunk();

	arm();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw
	glTranslatef(0, 0, -5);
	glRotated(rot_x, 1, 0, 0);
	glRotated(rot_y, 0, 1, 0);
	grid();

	robot();
	// end draw

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)w/h, 1, 100);
	// glOrtho(-1, 1, -1, 1, 0.1, 100);
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60, timer, 0);
}

void handle_camera_rotation(char key)
{
	switch (key)
	{
		case 'w':
		case 'W':
			rot_x += 2;
			break;
		case 's':
		case 'S':
			rot_x -= 2;
			break;
		case 'a':
		case 'A':
			rot_y += 2;
			break;
		case 'd':
		case 'D':
			rot_y -= 2;
			break;
		default:
			break;
	}
}

void handle_clamp_movement(char key)
{
	int tmp_angle = nail_angle;

	switch (key)
	{
		case 'w':
		case 'W':
			tmp_angle += 5;
			break;
		case 's':
		case 'S':
			tmp_angle -= 5;
			break;
		default:
			break;
	}

	if (tmp_angle > -45 || tmp_angle < -90 )
		return;

	nail_angle = tmp_angle;
}

void handle_movement(char key)
{
	switch (movement_mode)
	{
		case CAMERA_ROTATION_MODE:
			handle_camera_rotation(key);
			break;
		case CLAMP_MOVEMENT_MODE:
			handle_clamp_movement(key);
			break;
		default:
			break;
	}
}

void handle_keyboard(unsigned char key, int x, int y)
{
	if ('1' <= key && key <= '9')
	{
		movement_mode = key;
		printf("Movement mode: %c\n", movement_mode);
	}
	else if (
		key == 'w' || key == 'W' ||
		key == 'a' || key == 'A' ||
		key == 's' || key == 'S' ||
		key == 'd' || key == 'D'
	) {
		handle_movement(key);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Robo");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(handle_keyboard);
	init();
	glutTimerFunc(1000/60, timer, 0);
	glutMainLoop();
	
	return 0;
}