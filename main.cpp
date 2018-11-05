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


//global variables
vector<vector<double>> vArr;
vector<vector<double>> lArr; 

inline void mainMenu(int pid) {;}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION); 
	//Bounding Box: 
	glOrtho(-500, 500, -500, 500, -500, 500); 
}
void drawSceneXY()
{
	
	glClear(GL_COLOR_BUFFER_BIT); 
        glLoadIdentity();
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0); 
		glVertex2f(-450, -450);
		glVertex2f(450, 450);
		glVertex2f(450, -450);
		glVertex2f(-450, 450); 
	glEnd(); 
	glFlush(); 
}
void drawSceneXZ()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glBegin(GL_LINES);
                glColor3f(1.0, 1.0, 1.0);
                glVertex2f(-450, -450);
                glVertex2f(450, 450);
                glVertex2f(450, -450);
                glVertex2f(-450, 450);
        glEnd();
        glFlush();

}
void drawSceneYZ()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glBegin(GL_LINES);
                glColor3f(1.0, 1.0, 1.0);
                glVertex2f(-450, -450);
                glVertex2f(450, 450);
                glVertex2f(450, -450);
                glVertex2f(-450, 450);
        glEnd();
        glFlush();

}
void background() 
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        glOrtho(-500, 500, -500, 500, -500, 500);

	glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();	
	glFlush(); 
}
void translateMenu(int pid)
{
        ofstream file;
        file.open("inputFile.txt", std::ofstream::out | std::ofstream::trunc);
        if (!file) {
                cerr << "Unable to open file\n";
                exit(1);   // call system to stop
        }
        file << vArr.size() << '\n';
        for (int i = 0; i < vArr.size(); i++) {
                for (int j = 0; j < vArr.at(i).size(); j++)
                        file << vArr.at(i).at(j) << '\n';
        }

	glutPostRedisplay();
}
void scaleMenu(int pid) 
{
	ofstream file;
        file.open("inputFile.txt", std::ofstream::out | std::ofstream::trunc);
        if (!file) {
                cerr << "Unable to open file\n";
                exit(1);   // call system to stop
        }
        file << vArr.size() << '\n';
        for (int i = 0; i < vArr.size(); i++) {
                for (int j = 0; j < vArr.at(i).size(); j++)
                        file << vArr.at(i).at(j) << '\n';
        }
 
	glutPostRedisplay();
}
void rotateMenu(int pid)
{
        ofstream file;
        file.open("inputFile.txt", std::ofstream::out | std::ofstream::trunc);
        if (!file) {
                cerr << "Unable to open file\n";
                exit(1);   // call system to stop
        }
        file << vArr.size() << '\n';
        for (int i = 0; i < vArr.size(); i++) {
                for (int j = 0; j < vArr.at(i).size(); j++)
                        file << vArr.at(i).at(j) << '\n';
        }

        glutPostRedisplay();
}
int main(int argc, char** argv) 
{
	if (argc != 2) {
		cout << "Usage: p1 <input_file_name> \n";
		exit(1); 
	}	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(800, 800); 
	int windowID = glutCreateWindow("Polyhedron Orthographic Projections: XY, XZ, YZ from left to right and top down");  
	glutDisplayFunc(background);

	int scale_menu, rotate_menu, translate_menu; //For use in graphical menu

        vector<double> v; // The main V
        double num;
        fstream file;
        file.open(argv[1]);

        if (!file) {
                cerr << "Unable to open file\n";
                exit(1);
        }
        while (file >> num)
                v.push_back(num); //Initial vector for all polygons
        file.close();

	auto vpoint = v.begin(); 
	int polyTotal = (int)*vpoint;
	
	for (int i = 0; i < polyTotal; i++) {
        	vector<double> Va;
		vector<double> Vb; 
                vArr.push_back(Va);
		lArr.push_back(Vb); 
                int vertices = (int)*(++vpoint);
                vArr.at(i).push_back(vertices);
                for (int j = 0; j < vertices; j++) {
                        vArr.at(i).push_back(*(++vpoint));
                        vArr.at(i).push_back(*(++vpoint));
			vArr.at(i).push_back(*(++vpoint)); 
                }
		int lines = (int)*(++vpoint); 
		lArr.at(i).push_back(lines); 
	       	for (int k = 0; k < lines; k++) {
			vArr.at(i).push_back(*(++vpoint)); 
			vArr.at(i).push_back(*(++vpoint));
		}
        }

	//XY
	int window1 = glutCreateSubWindow(windowID, 25, 50, 320, 320);
	init();
	glutDisplayFunc(drawSceneXY); 

	//XZ
	int window2 = glutCreateSubWindow(windowID, 25, 450, 320, 320); 
	init(); 
	glutDisplayFunc(drawSceneXZ);	

	//YZ
	int window3 = glutCreateSubWindow(windowID, 425, 450, 320, 320); 
	init(); 
	glutDisplayFunc(drawSceneYZ);

	glutSetWindow(windowID); 

        // Offer the user opportunities to 3D transform! 
        translate_menu = glutCreateMenu(translateMenu);
                glutAddMenuEntry("Tetrahedron", 0);
                glutAddMenuEntry("Hexahedron", 1);
                glutAddMenuEntry("Octahedron", 2);

        scale_menu = glutCreateMenu(scaleMenu);
                glutAddMenuEntry("Tetrahedron", 0);
                glutAddMenuEntry("Hexahedron", 1);
                glutAddMenuEntry("Octahedron", 2);

        rotate_menu = glutCreateMenu(rotateMenu);
                glutAddMenuEntry("Tetrahedron", 0);
                glutAddMenuEntry("Hexahedron", 1);
                glutAddMenuEntry("Octahedron", 2);

        glutCreateMenu(mainMenu);
                glutAddSubMenu("Translate", translate_menu);
                glutAddSubMenu("Scale", scale_menu);
                glutAddSubMenu("Rotate", rotate_menu);
        glutAttachMenu(GLUT_RIGHT_BUTTON);




	glutMainLoop(); 

	return 0; 
}
