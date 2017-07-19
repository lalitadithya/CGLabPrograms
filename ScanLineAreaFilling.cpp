#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
	int ymin, ymax;
	int xmin, xmax;
	float slope;
};

vector<Edge> EdgeTable, ActiveEdgeTable;

int yminComparator(Edge e1, Edge e2)
{
	return e1.ymin < e2.ymin;
}

int xminComparator(Edge e1, Edge e2)
{
	return e1.xmin < e2.xmin;
}

float CalculateSlope(float x0, float y0, float x1, float y1)
{
	return (y1 - y0) / (x1 - x0);
}

void displayLine(int x0, int y0, int x1, int y1)
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glEnd();
	glFlush();
}

void ScanLineAreaFilling()
{
	sort(EdgeTable.begin(), EdgeTable.end(), yminComparator);

	int scanLine = EdgeTable.front().ymin;

	do
	{
		for (vector<Edge>::iterator i = EdgeTable.begin(); i != EdgeTable.end(); )
		{
			if ((*i).ymin == scanLine)
			{
				ActiveEdgeTable.push_back(*i);
				i = EdgeTable.erase(i);
			}
			else
			{
				i++;
			}
		}

		sort(ActiveEdgeTable.begin(), ActiveEdgeTable.end(), xminComparator);

		for (vector<Edge>::iterator i = ActiveEdgeTable.begin(); i != ActiveEdgeTable.end(); i += 2)
		{
			displayLine((*i).xmin, scanLine, (*(i + 1)).xmin, scanLine);
			(*i).xmin += (*i).slope;
			(*(i + 1)).xmin += (*(i + 1)).slope;
		}

		scanLine++;

		for (vector<Edge>::iterator i = ActiveEdgeTable.begin(); i != ActiveEdgeTable.end(); )
		{
			if ((*i).ymax <= scanLine)
			{
				i = ActiveEdgeTable.erase(i);
			}
			else
			{
				i++;
			}
		}

	} while (!ActiveEdgeTable.empty());
}

void display()
{
	EdgeTable.clear();

	Edge ac = { 100, 150, 100, 200, 1.0 / CalculateSlope(100, 100, 200, 150) };
	Edge ab = { 100, 200, 100, 100, 1.0 / CalculateSlope(100, 100, 100, 200) };
	Edge bc = { 150, 200, 200, 100, 1.0 / CalculateSlope(100, 200, 200, 150) };

	EdgeTable.push_back(ac);
	EdgeTable.push_back(ab);
	EdgeTable.push_back(bc);

	glClear(GL_COLOR_BUFFER_BIT);

	ScanLineAreaFilling();

	glFlush();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(100.0, 200.0, 100.0, 200.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(100, 100);
	glutCreateWindow("Scan Line");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
