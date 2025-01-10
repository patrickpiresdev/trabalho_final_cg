#include <stdio.h>
#include "GL/freeglut.h"
#include "RgbImage.h"

float rot_x = 0, rot_y = 0;

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

void rect(float* v1, float* v2, float* v3, float* v4, GLuint texture_id)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3fv(v1);
	glTexCoord2f(1, 0); glVertex3fv(v2);
	glTexCoord2f(1, 1); glVertex3fv(v3);
	glTexCoord2f(0, 1); glVertex3fv(v4);
	glEnd();
}

void init()
{
	glClearColor(0, 0, 0, 1);
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
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float v1[] = { 0.5,  0.5,  0.5};
	float v2[] = {-0.5,  0.5,  0.5};
	float v3[] = {-0.5, -0.5,  0.5};
	float v4[] = { 0.5, -0.5,  0.5};
	float v5[] = {-0.5,  0.5, -0.5};
	float v6[] = {-0.5, -0.5, -0.5};
	float v7[] = { 0.5, -0.5, -0.5};
	float v8[] = { 0.5,  0.5, -0.5};

	// draw
	glPushMatrix();

	glTranslatef(0, 0, -2);
	glRotatef(rot_x, 1, 0, 0);
	glRotatef(rot_y, 0, 1, 0);

	glColor3f(1, 0, 0);
	rect(v1, v2, v3, v4, RUGGED_TEXTURE_ID);

	glColor3f(0, 1, 0);
	rect(v8, v1, v4, v7, RUSTED_TEXTURE_ID);

	glColor3f(0, 0, 1);
	rect(v5, v8, v7, v6, GOLDEN_TEXTURE_ID);

	glColor3f(1, 1, 0);
	rect(v2, v5, v6, v3, GLASS_TEXTURE_ID);

	glColor3f(0, 1, 1);
	rect(v2, v1, v8, v5, METAL_TEXTURE_ID);

	glColor3f(1, 0, 1);
	rect(v4, v3, v6, v7, RUGGED_TEXTURE_ID);

	glPopMatrix();

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
	rot_x += 1;
	rot_y += 1;
	glutPostRedisplay();
	glutTimerFunc(1000/60, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cabeca de Robo");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutTimerFunc(1000/60, timer, 0);
	glutMainLoop();
	
	return 0;
}