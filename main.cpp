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
	//glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0); 
}
void drawSceneXY()
{
	glClear(GL_COLOR_BUFFER_BIT); 
        glLoadIdentity();
	glBegin(GL_LINES);
		//XY: All Z values are ignored 
		for (int i = 0; i < lArr.size(); i++) { //For each polyhedron
			for (int j = 1; j < lArr.at(i).size(); j = j+2) { //For each each line in the polyhedron 
				//First vArr entry appears as [6,0,100,200,200,100,200,0,300,200,200,300,200,100,200,400,100,200,0]
				//First lArr entry appears as [12,1,2,1,3,2,4,3,4,1,5,2,5,3,5,4,5,1,6,2,6,3,6,4,6]
				float x1 = vArr.at(i).at((lArr.at(i).at(j) - 1)*3+1);    //X of first point
                        	float y1 = vArr.at(i).at((lArr.at(i).at(j) - 1)*3+2);    //Y of first point

                        	float x2 = vArr.at(i).at((lArr.at(i).at(j+1) - 1)*3+1);   //X of second point
                        	float y2 = vArr.at(i).at((lArr.at(i).at(j+1) - 1)*3+2);   //Y of second point

				glColor3f(1.0, 1.0, 1.0); 
				glVertex2f(x1, y1);
				glVertex2f(x2, y2); 
			}
		}
	glEnd(); 
	glFlush(); 
}
void drawSceneXZ()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
	glBegin(GL_LINES);
		//XZ: All Y values are ignored 
        	for (int i = 0; i < lArr.size(); i++) { //For each polyhedron
                	for (int j = 1; j < lArr.at(i).size(); j = j+2) { //For each each line in the polyhedron 
                        	//First vArr entry appears as [6,0,100,200,200,100,200,0,300,200,200,300,200,100,200,400,100,200,0]
                        	//First lArr entry appears as [12,1,2,1,3,2,4,3,4,1,5,2,5,3,5,4,5,1,6,2,6,3,6,4,6]
                        	float x1 = vArr.at(i).at((lArr.at(i).at(j) - 1)*3+1);    //X of first point
                        	float z1 = vArr.at(i).at((lArr.at(i).at(j) - 1)*3+3);    //Z of first point

                        	float x2 = vArr.at(i).at((lArr.at(i).at(j+1) - 1)*3+1);   //X of second point
                        	float z2 = vArr.at(i).at((lArr.at(i).at(j+1) - 1)*3+3);   //Z of second point

                                glColor3f(1.0, 1.0, 1.0);
                                glVertex2f(x1, z1);
                                glVertex2f(x2, z2);
                	}
        	}
	glEnd(); 
	glFlush(); 
}
void drawSceneYZ()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
	glBegin(GL_LINES);
		//YZ: All X values are ignored
        	for (int i = 0; i < lArr.size(); i++) { //For each polyhedron
                	for (int j = 1; j < lArr.at(i).size(); j = j+2) { //For each each line in the polyhedron 
				//First vArr entry appears as [6,0,100,200,200,100,200,0,300,200,200,300,200,100,200,400,100,200,0]
                        	//First lArr entry appears as [12,1,2,1,3,2,4,3,4,1,5,2,5,3,5,4,5,1,6,2,6,3,6,4,6]
                        	float y1 = vArr.at(i).at((lArr.at(i).at(j) - 1)*3+2);    //Y of first point
                        	float z1 = vArr.at(i).at((lArr.at(i).at(j) - 1)*3+3);    //Z of first point

                        	float y2 = vArr.at(i).at((lArr.at(i).at(j+1) - 1)*3+2);   //Y of second point
                        	float z2 = vArr.at(i).at((lArr.at(i).at(j+1) - 1)*3+3);   //Z of second point
			
				glColor3f(1.0, 1.0, 1.0);
                                glVertex2f(y1, z1);
                                glVertex2f(y2, z2);
                	}
        	}
	glEnd(); 
	glFlush(); 
}
void background() 
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        //glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);

	glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();	
	glFlush(); 
}
void translateMenu(int pid)
{
        /*ofstream file;
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

	glutPostRedisplay()*/;
}
void scaleMenu(int pid) 
{
	/*ofstream file;
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
 
	glutPostRedisplay()*/;
}
void rotateMenu(int pid)
{
        /*ofstream file;
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

        glutPostRedisplay()*/;
	
}
void vertexMenu(int pid)
{
	switch (pid) 
	{
		case 0: cout << "Present vertices of the octahedron or polhedron 0:\n";
			break; 
		case 1: cout << "Present vertices of the tetrahedron or polyhedron 1:\n"; 
		        break; 
		case 2: cout << "Present vertices of the hexahedron or polyhedron 2:\n";  	
			break; 
	}
	for (int i = 1; i < vArr.at(pid).size(); i+=3) 
		cout << "(" << vArr.at(pid).at(i) << ", " << vArr.at(pid).at(i+1) << ", " << vArr.at(pid).at(i+2) << ")\n"; 

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

	int scale_menu, rotate_menu, translate_menu, vertex_menu; //For use in graphical menu

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
                        vArr.at(i).push_back(*(++vpoint) / 500.0);
                        vArr.at(i).push_back(*(++vpoint) / 500.0);
			vArr.at(i).push_back(*(++vpoint) / 500.0); 
                }
		int lines = (int)*(++vpoint); 
		lArr.at(i).push_back(lines);
	       	for (int k = 0; k < lines; k++) {
			lArr.at(i).push_back(*(++vpoint));
			lArr.at(i).push_back(*(++vpoint));
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
                glutAddMenuEntry("Octahedron/Polyhedron 0", 0);
                glutAddMenuEntry("Tetrahedron/Polyhedron 1", 1);
                glutAddMenuEntry("Hexahedron/Polyhedron 2", 2);

        scale_menu = glutCreateMenu(scaleMenu);
                glutAddMenuEntry("Octahedron/Polyhedron 0", 0);
                glutAddMenuEntry("Tetrahedron/Polyhedron 1", 1);
                glutAddMenuEntry("Hexahedron/Polyhedron 2", 2);

        rotate_menu = glutCreateMenu(rotateMenu);
                glutAddMenuEntry("Octahedron/Polyhedron 0", 0);      
      		glutAddMenuEntry("Tetrahedron/Polyhedron 1", 1);
                glutAddMenuEntry("Hexahedron/Polyhedron 2", 2);
	
	vertex_menu = glutCreateMenu(vertexMenu);
                glutAddMenuEntry("Octahedron/Polyhedron 0", 0);
                glutAddMenuEntry("Tetrahedron/Polyhedron 1", 1);
                glutAddMenuEntry("Hexahedron/Polyhedron 2", 2);

        glutCreateMenu(mainMenu);
                glutAddSubMenu("Translate", translate_menu);
                glutAddSubMenu("Scale", scale_menu);
                glutAddSubMenu("Rotate", rotate_menu);
		glutAddSubMenu("Vertex Dump", vertex_menu); 
        glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop(); 

	return 0; 
}
