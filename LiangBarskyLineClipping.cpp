#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"

// end points of the line
int x1 = -80, x2 = 0, y1 = -80, y2 = 0;

// end points of the clipping region
int xmin = -50, ymin = -50, xmax = 50, ymax = 50;

/*
* Function to draw a line from (x1, y1) to (x2, y2)
*/
void drawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

/*
 * Function to initialize GLUT
 */
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -240, 240);
}

/*
 * Function to clip the line segment according to Liang Barsky algorithm
 */
void clip(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1;
	float u1 = 0, u2 = 1;
	double t, p[4], q[4];

	p[0] = -dx;
	p[1] = dx;
	p[2] = -dy;
	p[3] = dy;

	q[0] = x1 - xmin;
	q[1] = xmax - x1;
	q[2] = y1 - ymin;
	q[3] = ymax - y1;

	for (int i = 0; i < 4; i++)
	{
		if (p[i] == 0 && q[i] < 0)
			return;

		t = (q[i]) / (p[i]);

		if (p[i] < 0 && t > u1 && t < u2)
			u1 = t;
		else if (p[i] > 0 && t > u1 && t < u2)
			u2 = t;
	}

	if (u1 < u2)
	{
		x1 = x1 + u1*(x2 - x1);
		y1 = y1 + u1*(y2 - y1);
		x2 = x1 + u2*(x2 - x1);
		y2 = y1 + u2*(y2 - y1);

		drawLine(x1, y1, x2, y2);
	}
}

/*
 * Display function
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the bounding box
	glColor3f(1.0, 0.0, 0.0);
	glRectd(xmin, ymin, xmax, ymax);

	// clip the line segment and draw the same
	glColor3f(0.0, 0.0, 0.0);
	clip(x1, y1, x2, y2);

	glFlush();
}

/*
 * Main Function
 */
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Clip");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
