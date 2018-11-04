#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

/*In this project, to draw lines you may use: 
 glBegin(GL_LINES);
    glColor3f(1.f, 0.f, 0.f); // Set the color for every subsequent vertex to red
    glVertex2f(point1x, point1y); // Give OpenGL the first vertex, etc. You can put more glColor3fs between to get multicolor lines.
    glVertex2f(point2x, point2y);
    glColor3f(0.f, 0.f, 1.f); // Now I'm a blueberry
    glVertex2f(point3x, point3y);
        (...)
glEnd();

You may not use: gluOrtho2D, gluLookAt, or functions to rotate, scale, or translate 
*/

//global variables

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION); 
	//Bounding Box: 
	glOrtho(-500, 500, -500, 500, -500, 500); 
}
void init2()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
        glMatrixMode(GL_PROJECTION);	
	glOrtho(-500, 500, -500, 500, -500, 500);
}
void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0); 
		glVertex2f(-450, -450);
		glVertex2f(450, 450);
		glVertex2f(450, -450);
		glVertex2f(-450, 450); 
	glEnd(); 
	glFlush(); 
}
void titles() 
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glFlush(); 
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(800, 800); 
	int windowID = glutCreateWindow("An Example OpenGL Program"); 
	init2(); 
	glutDisplayFunc(titles);

	int window1 = glutCreateSubWindow(windowID, 25, 50, 320, 320);
	init();
	glutDisplayFunc(lineSegment); 

	int window2 = glutCreateSubWindow(windowID, 25, 450, 320, 320); 
	init(); 
	glutDisplayFunc(lineSegment);	

	int window3 = glutCreateSubWindow(windowID, 425, 450, 320, 320); 
	init(); 
	glutDisplayFunc(lineSegment); 

	glutMainLoop(); 

	return 0; 
}
