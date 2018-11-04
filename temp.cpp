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
float *PixelBuffer;
float *PolygonBuffer;
vector<vector<double>> vArr;
int wWidth;
int wLength;
inline void mainMenu(int pid) {;}
//main display loop, this function will be called again and again by OpenGL
void display()
{
        //Displays window to screen        
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        //draws pixel on screen, width and height must match pixel buffer dimension
        glDrawPixels(wWidth, wLength, GL_RGB, GL_FLOAT, PixelBuffer);

        //window refresh
        glFlush();
}
void makePix(int x, int y, int pid)
{
        PolygonBuffer[pid*wWidth*wLength*3 + (y*wWidth+x)*3+0] = 0;
        PolygonBuffer[pid*wWidth*wLength*3 + (y*wWidth+x)*3+1] = 255;
        PolygonBuffer[pid*wWidth*wLength*3 + (y*wWidth+x)*3+2] = 255;
}
void copyBuffer(int pid)
{
        for (int i = 0; i < wLength*wWidth*3; i++) {
                if (PolygonBuffer[pid*wWidth*wLength*3 + i] != 0)
                        PixelBuffer[i] = PolygonBuffer[pid*wWidth*wLength*3 + i];
        }
}
void clearPixelBuffer() 
{
	for (int i = 0; i < wLength*wWidth*3; i++)
		PixelBuffer[i] = 0; 
}
void clearPolygonBuffer(int pid)
{
	for (int i = 0; i < wLength*wWidth*3; i++) 
		PolygonBuffer[pid*wWidth*wLength*3 + i] = 0; 
}
void scaleMenu(int pid)
{
	double scale; 
	int vertices = vArr.at(pid).at(0);
        double xSum = 0;
	double ySum = 0; 	
	double centX, centY;

	cout << "Please enter the magnitude you'd like to scale by:\n";	
	cin >> scale; 

	for (int i = 0; i < vertices; i++) {
		xSum += vArr.at(pid).at(1+i*2);
	}
	centX = xSum / (double)vertices; 
	for (int i = 0; i < vertices; i++) {
		ySum += vArr.at(pid).at(2+i*2); 
	}
	centY = ySum / (double)vertices;
	for (int i = 0; i < vertices; i++) {
		vArr.at(pid).at(1+i*2) = scale*(vArr.at(pid).at(1+i*2) - centX) + centX; 
		vArr.at(pid).at(2+i*2) = scale*(vArr.at(pid).at(2+i*2) - centY) + centY; 		
	}

	ofstream file;
        file.open("inputFile.txt", std::ofstream::out | std::ofstream::trunc);
        if (!file) {
                cerr << "Unable to open file\n";
                exit(1);   
        }
        file << vArr.size() << '\n';
        for (int i = 0; i < vArr.size(); i++) {
                for (int j = 0; j < vArr.at(i).size(); j++)
                        file << vArr.at(i).at(j) << '\n';
        }

	lineDrawRaster();
        glutPostRedisplay();
}
void rotateMenu(int pid)
{
        double alpha;
        int vertices = vArr.at(pid).at(0);
        double xSum = 0;
        double ySum = 0;
        double centX, centY; 
	
        cout << "Please enter the angle in radians you'd like to rotate by:\n";
        cin >> alpha;

        for (int i = 0; i < vertices; i++) {
                xSum += vArr.at(pid).at(1+i*2);
        }
        centX = xSum / (double)vertices;
        for (int i = 0; i < vertices; i++) {
                ySum += vArr.at(pid).at(2+i*2);
        }
        centY = ySum / (double)vertices;
        for (int i = 0; i < vertices; i++) {
		double oldX, oldY; 
                oldX = vArr.at(pid).at(1+i*2) - centX;
                oldY = vArr.at(pid).at(2+i*2) - centY;
                vArr.at(pid).at(1+i*2) = (oldX*cos(alpha) - oldY*sin(alpha)) + centX;
                vArr.at(pid).at(2+i*2) = (oldX*sin(alpha) + oldY*cos(alpha)) + centY;
        }

	ofstream file;
        file.open("inputFile.txt", std::ofstream::out | std::ofstream::trunc);
        if (!file) {
                cerr << "Unable to open file\n";
                exit(1);   
        }
        file << vArr.size() << '\n';
        for (int i = 0; i < vArr.size(); i++) {
                for (int j = 0; j < vArr.at(i).size(); j++)
                        file << vArr.at(i).at(j) << '\n';
        }

        lineDrawRaster();
        glutPostRedisplay();
}
void translateMenu(int pid)
{
        int x, y; 
	int vertices = vArr.at(pid).at(0);
	cout << "Please enter the x and y translation values:\n";
	cin >> x >> y;
	for (int i = 0; i < vertices; i++) {
		vArr.at(pid).at(1+2*i) += x; 
		vArr.at(pid).at(2+2*i) += y;
	}
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

	lineDrawRaster(); 
	glutPostRedisplay(); 
}
int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // These are the default values 

        wWidth = 801;
        wLength = 801;
        glutInitWindowSize(wWidth, wLength);
        glutInitWindowPosition(100, 100);
        int MainWindow = glutCreateWindow("Polyhedrons");
        glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL, sets a black background
        int scale_menu, rotate_menu, translate_menu; //For use in graphical menu

        vector<double> v; // The main V 
        double num;
        fstream file;
        file.open("inputFile.txt");

        if (!file) {
                cerr << "Unable to open file\n";
                exit(1);
        }
        while (file >> num)
                v.push_back(num); //Initial vector for all polygons
        file.close();

        auto vpoint = v.begin();
        int polyTotalForBuffer = (int)*vpoint;

        for (int i = 0; i < polyTotalForBuffer; i++) {
                vector<double> Vx;
                vArr.push_back(Vx);
                double vertices = *(++vpoint);
                vArr.at(i).push_back(vertices);
                for (int j = 0; j < vertices; j++) {
                        vArr.at(i).push_back(*(++vpoint));
                        vArr.at(i).push_back(*(++vpoint));
                }
        }
        // Prepping area before being copied to Pixel Buffer 
        PolygonBuffer = new float[polyTotalForBuffer*wWidth*wLength*3]();

        //Buffer drawn to screen
        PixelBuffer = new float[wWidth * wLength * 3]();


        //Line Draw and Rasterize the original polygons! 
        lineDrawRaster();


        // Offer the user opportunities to transform! 
        translate_menu = glutCreateMenu(translateMenu);
                glutAddMenuEntry("Square", 0);
                glutAddMenuEntry("Triangle", 1);
                glutAddMenuEntry("Pentagon", 2);

        scale_menu = glutCreateMenu(scaleMenu);
                glutAddMenuEntry("Square", 0);
                glutAddMenuEntry("Triangle", 1);
                glutAddMenuEntry("Pentagon", 2);

        rotate_menu = glutCreateMenu(rotateMenu);
                glutAddMenuEntry("Square", 0);
                glutAddMenuEntry("Triangle", 1);
                glutAddMenuEntry("Pentagon", 2);

        glutCreateMenu(mainMenu);
                glutAddSubMenu("Translate", translate_menu);
                glutAddSubMenu("Scale", scale_menu);
                glutAddSubMenu("Rotate", rotate_menu);
                glutAddSubMenu("Clipping", clipping_menu);
        glutAttachMenu(GLUT_RIGHT_BUTTON);


        glutDisplayFunc(display);


        glutMainLoop();//main display loop, will display until terminate

        return 0;
}

