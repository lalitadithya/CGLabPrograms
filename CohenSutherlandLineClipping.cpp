#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"

static const int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;
static const int XMIN = 10, XMAX = 200, YMIN = 10, YMAX = 200;

/*
 * Function to compute out code
 */
int ComputeOutCode(float x, float y)
{
	int code = INSIDE;

	if (x < XMIN)
		code |= LEFT;
	else if (x > XMAX)
		code |= RIGHT;

	if (y < YMIN)
		code |= BOTTOM;
	else if (y > YMAX)
		code |= TOP;

	return code;
}

/*
 * Function to calculate slope
 */
float CalculateSlope(float x0, float y0, float x1, float y1)
{
	return (y1 - y0) / (x1 - x0);
}

/*
 * Function to clip a line using Cohen Sutherland line clipping algorithm
 */
void CohenSutherlandClip(float x0, float y0, float x1, float y1)
{
	bool accept = false;

	while (true)
	{
		int outcode0 = ComputeOutCode(x0, y0);
		int outcode1 = ComputeOutCode(x1, y1);

		if(!(outcode0 | outcode1))	// trivial accept
		{
			accept = true;
			break;
		}
		else if (outcode0 & outcode1)  // trivial reject
		{
			break;
		}
		else		//clipping needed
		{
			float x, y;

			// find the point outside the clip rectangle
			int outcode = outcode0 ? outcode0 : outcode1;

			if (outcode & TOP)	// point is north of the rectangle
			{
				x = x0 + (1 / CalculateSlope(x0, y0, x1, y1)) * (YMAX - y0);
				y = YMAX;
			}
			else if (outcode & BOTTOM) // point is south of rectangle
			{
				x = x0 + (1 / CalculateSlope(x0, y0, x1, y1)) * (YMIN - y0);
				y = YMIN;
			}
			else if (outcode & RIGHT) // point is east of rectangle
			{
				y = y0 + CalculateSlope(x0, y0, x1, y1) * (XMAX - x0);
				x = XMAX;
			}
			else if (outcode & LEFT) // point is west of rectangle
			{
				y = y0 + CalculateSlope(x0, y0, x1, y1) * (XMIN - x0);
				x = XMIN;
			}

			// update the intersection point
			if (outcode == outcode0)
			{
				x0 = x;
				y0 = y;
			}
			else
			{
				x1 = x;
				y1 = y;
			}
		}
	}

	if (accept)
	{
		// draw bounding box in red
		glColor3f(1, 0, 0);
		glRectd(XMIN, YMIN, XMAX, YMAX);

		// draw line in white
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glEnd();
	}

}

/*
 * display function
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	CohenSutherlandClip(1, 1, 300, 300);
	glFlush();
}

/*
 * function to initialize glut
 */
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Line Clipping");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
