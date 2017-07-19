// Program to display 3D Serp

#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"

/*
* function to draw a triangle
*/
void drawTriangle(float a[], float b[], float c[])
{
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

/*
* function to draw a tetrahedron
*/
void drawTetrahedron(float a[], float b[], float c[], float d[])
{
	glColor3f(1, 1, 0);
	drawTriangle(c, b, d);
	glColor3f(1, 0, 0);
	drawTriangle(b, a, d);
	glColor3f(0, 1, 0);
	drawTriangle(b, c, a);
	glColor3f(0, 0, 1);
	drawTriangle(d, a, c);
}

/*
 * function to divide a tetrahedron
 */
void divideTetrahedron(float a[], float b[], float c[], float d[], int numberOfDivisions)
{
	float bd[3], bc[3], ba[3], ca[3], cd[3], ad[3];

	if (numberOfDivisions == 0)
	{
		drawTetrahedron(a, b, c, d);
	}
	else
	{
		// calculate mid points
		for (int i = 0; i < 3; i++)
		{
			bd[i] = (b[i] + d[i]) / 2.0;
			bc[i] = (b[i] + c[i]) / 2.0;
			ba[i] = (b[i] + a[i]) / 2.0;
			ca[i] = (c[i] + a[i]) / 2.0;
			cd[i] = (c[i] + d[i]) / 2.0;
			ad[i] = (a[i] + d[i]) / 2.0;
		}

		// divide the tetrahedron
		divideTetrahedron(ba, b, bc, bd, numberOfDivisions - 1);
		divideTetrahedron(ca, bc, c, cd, numberOfDivisions - 1);
		divideTetrahedron(ad, bd, cd, d, numberOfDivisions - 1);
		divideTetrahedron(a, ba, ca, ad, numberOfDivisions - 1);
	}
}

/*
* GLUT function to draw the ouput
*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divideTetrahedron(new float[3]{ 0, 0, 0.5 }, new float[3]{ -0.5, -0.25, 0 },
		new float[3]{ 0, 0.5, 0 }, new float[3]{ 0.5, -0.25, 0 }, 1);
	glFlush();
}

/*
* Helper method to initialize the required variables and GLUT
*/
void init()
{
	// set the backgroud color
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

/*
* Main function
*/
int main(int argc, char **argv)
{
	// initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	// create the window
	glutInitWindowSize(500, 500);
	glutCreateWindow("3d serp");

	// initialize the callbacks
	glutDisplayFunc(display);

	// initialize the variables
	init();

	// main loop
	glutMainLoop();
	return 0;
}
