#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"

// angle of the cube
static GLfloat theta[] = { 0.0, 0.0, 0.0 };

// axis of rotation
static GLint axis = 2;

// vertices of the unit cube
GLfloat vertices[][3] = {
	{ -1.0, -1.0, -1.0 },
	{ 1.0, -1.0, -1.0 },
	{ 1.0,  1.0, -1.0 },
	{ -1.0,  1.0, -1.0 },
	{ -1.0, -1.0,  1.0 },
	{ 1.0, -1.0,  1.0 },
	{ 1.0,  1.0,  1.0 },
	{ -1.0,  1.0,  1.0 }
};

// colors for the vertices of the cube
GLfloat colors[][3] = {
	{ 0.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 0.0, 1.0, 1.0 }
};

/*
 * Function to draw a square whoes end points are a, b, c and d
 */
void drawSquare(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

/*
 * Function to draw a color cube
 */
void drawColorCube(void)
{
	drawSquare(0, 3, 2, 1);
	drawSquare(2, 3, 7, 6);
	drawSquare(0, 4, 7, 3);
	drawSquare(1, 2, 6, 5);
	drawSquare(4, 5, 6, 7);
	drawSquare(0, 1, 5, 4);
}

/*
 * Display function
 */
void display(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// draw the color cube
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	drawColorCube();

	// flush
	glFlush();
	glutSwapBuffers();
}

/*
 * Function to update the angle periodically
 */
void spinCube(int x)
{
	// update the angle of rotation
	for (int i = 0; i < 3; i++)
	{
		theta[i] = theta[i] > 360.0 ? 0 : theta[i] + 0.5;
	}

	// set the next timer
	glutTimerFunc(5, spinCube, 1);

	// call the display
	glutPostRedisplay();
}

/*
 * reshape function
 */
void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

/*
 * Main function
 */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Cube Spin");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutTimerFunc(5, spinCube, 1);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
