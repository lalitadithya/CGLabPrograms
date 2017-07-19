#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"

// vertices of the cube
GLfloat vertices[][3] = {
	{ -1,-1,-1 },
	{ 1,-1,-1 },
	{ 1,1,-1 },
	{ -1,1,-1 },
	{ -1,-1,1 },
	{ 1,-1,1 },
	{ 1,1,1 },
	{ -1,1,1 }
};

// colors for the vertices
GLfloat colors[][3] = {
	{ 0,0,0 },
	{ 1,0,0 },
	{ 1,1,0 },
	{ 0,1,0 },
	{ 0,0,1 },
	{ 1,0,1 },
	{ 1,1,1 },
	{ 0,1,1 }
};

// viewer position
static GLdouble viewer[] = { 0,0,5 };

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
 * display function
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
	drawColorCube();
	glFlush();
	glutSwapBuffers();
}

/*
 * keyboard call back
 */
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')    viewer[0] -= 1;
	if (key == 'X')    viewer[0] += 1;
	if (key == 'y')    viewer[1] -= 1;
	if (key == 'Y')    viewer[1] += 1;
	if (key == 'z')    viewer[2] -= 1;
	if (key == 'Z')    viewer[2] += 1;
	glutPostRedisplay();
}

/*
 * function to initialize glut
 */
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

/*
 * main function
 */
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prespective viewing");
	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
