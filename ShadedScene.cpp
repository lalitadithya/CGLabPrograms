#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"
#define X 0
#define Y 1
#define Z 2
#define JUGAAD 15

const int TABLE_CENTER[] = { 50, 40, -50 };
const int TABLE_SIZE[] = { 50, 5, 50 };
const int TABLE_LEG_SIZE[] = { 5, 30, 5 };
const int WALL_SIZE[] = { 100, 5, 100 };
const int TEA_POT_SIZE = 10;
const int ORIGIN[] = { 0, 0, 0 };

/*
 * function to draw a table top
 */
void drawTableTop()
{
	glPushMatrix();
	glTranslated(TABLE_CENTER[X], TABLE_CENTER[Y], TABLE_CENTER[Z]);
	glScaled(TABLE_SIZE[X], TABLE_SIZE[Y], TABLE_SIZE[Z]);
	glutSolidCube(1.0);
	glPopMatrix();
}

/*
 * Function to draw a table leg
 */
void drawTableLeg(int XPositionOfTableLeg, int YPositionOfTableLeg, int ZPositionOfTableLeg)
{
	glPushMatrix();
	glTranslated(XPositionOfTableLeg, YPositionOfTableLeg, ZPositionOfTableLeg);
	glScaled(TABLE_LEG_SIZE[X], TABLE_LEG_SIZE[Y], TABLE_LEG_SIZE[Z]);
	glutSolidCube(1.0);
	glPopMatrix();
}

/*
 * function to draw a table
 */
void drawTable()
{
	drawTableTop();
	drawTableLeg(TABLE_CENTER[X] - 20, TABLE_CENTER[Y] - 15, TABLE_CENTER[Z] + 20);
	drawTableLeg(TABLE_CENTER[X] + 20, TABLE_CENTER[Y] - 15, TABLE_CENTER[Z] + 20);
	drawTableLeg(TABLE_CENTER[X] - 20, TABLE_CENTER[Y] - 15, TABLE_CENTER[Z] - 20);
	drawTableLeg(TABLE_CENTER[X] + 20, TABLE_CENTER[Y] - 15, TABLE_CENTER[Z] - 20);
}

/*
 * function to draw a wall
 */
void drawWall(int rotationAlongX, int rotationAlongY, int rotationAlongZ,
	int XPosition, int YPosition, int ZPosition)
{
	glPushMatrix();
	glTranslated(XPosition, YPosition, ZPosition);
	glRotated(90, rotationAlongX, rotationAlongY, rotationAlongZ);
	glScaled(WALL_SIZE[X], WALL_SIZE[Y], WALL_SIZE[Z]);
	glutSolidCube(1.0);
	glPopMatrix();
}

/*
 * function to initialize glut
 */
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 200, -50, 200, -200, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * function to draw a teapot
 */
void drawTeapot()
{
	glPushMatrix();
	glTranslated(TABLE_CENTER[X], TABLE_CENTER[Y] + TEA_POT_SIZE, TABLE_CENTER[Z]);
	glutSolidTeapot(TEA_POT_SIZE);
	glFlush();
	glPopMatrix();
}

/*
 * display function
 */
void displaySolid()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1.0f });
	glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[4]{ .5f, .5f, .5f, 1.0f });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[4]{ 1.0f, 1.0f, 1.0f, 1.0f });
	glMaterialfv(GL_FRONT, GL_SHININESS, new GLfloat[1]{ 50.0f });

	glLightfv(GL_LIGHT0, GL_POSITION, new GLfloat[3]{ 100,100,100 });
	glLightfv(GL_LIGHT0, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1.0f });

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(TABLE_CENTER[X], TABLE_CENTER[Y], -TABLE_CENTER[Z],
		ORIGIN[X], ORIGIN[Y], TABLE_CENTER[Z],
		0, 1, 0);

	drawTeapot();
	drawTable();
	// draw the floor consider the floor as another wall
	drawWall(0, 1, 0, TABLE_CENTER[X], TABLE_CENTER[Y] - TABLE_LEG_SIZE[Y] - WALL_SIZE[Y], TABLE_CENTER[Z]);
	// draw left wall
	drawWall(0, 0, 1, TABLE_CENTER[X] - TABLE_SIZE[X], TABLE_CENTER[Y] + JUGAAD, TABLE_CENTER[Z]);
	// draw back wall
	drawWall(1, 0, 0, TABLE_CENTER[X], TABLE_CENTER[Y] + JUGAAD, TABLE_CENTER[Z] - TABLE_SIZE[Z]);
	glFlush();
}

/*
 * Main function
 */
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("scene");
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	init();
	glutMainLoop();
}
