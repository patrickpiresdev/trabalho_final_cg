#include <stdio.h>
#include "GL/freeglut.h"

float rot_x = 0, rot_y = 0;

void rect(float* v1, float* v2, float* v3, float* v4)
{
	glBegin(GL_QUADS);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glEnd();
}

void init()
{
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

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
	rect(v1, v2, v3, v4);

	glColor3f(0, 1, 0);
	rect(v8, v1, v4, v7);

	glColor3f(0, 0, 1);
	rect(v5, v8, v7, v6);

	glColor3f(1, 1, 0);
	rect(v2, v5, v6, v3);

	glColor3f(0, 1, 1);
	rect(v2, v1, v8, v5);

	glColor3f(1, 0, 1);
	rect(v4, v3, v6, v7);

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