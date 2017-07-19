#include <math.h>
#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"

/*
 * Function to draw a circle at x, y
 */
void draw_circle(int x, int y)
{
	float rad = 3.141 / 180.0;
	glBegin(GL_POINTS);
	for (int i = 0; i <= 360; i++)
	{
		glVertex2f(x + (5 * cos(i * rad)), y + (5 * sin(i * rad)));
	}
	glEnd();
}

/*
 * Function to draw a rectangle
 */
void draw_rectangle(int x, int y)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 10, y);
	glVertex2f(x + 10, y + 5);
	glVertex2f(x, y + 5);
	glEnd();
}

/*
* GLUT function to draw the ouput
*/
void display()
{
	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// set the color
	glColor3f(1.0f, 0.0f, 0.0f);

	// draw the cylinder
	for (int i = 0; i < 20; i++)
	{
		draw_circle(10, 10 + (i * 2));
	}

	// draw the parellopiped
	for (int i = 0; i < 20; i++)
	{
		draw_rectangle(25 + (i * 2), 25 + (i * 2));
	}

	// flush the frame buffer
	glFlush();
}

/*
* Helper method to initialize the required variables and GLUT
*/
void init()
{
	// set the backgroud color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// set the ortho space
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
}

/*
* Main function
*/
int main(int argc, char **argv)
{
	// initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// create the window
	glutInitWindowSize(500, 500);
	glutCreateWindow("Circle");

	// initialize the callbacks
	glutDisplayFunc(display);

	// initialize the variables
	init();

	// main loop
	glutMainLoop();
	return 0;
}
