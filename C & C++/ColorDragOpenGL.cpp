/*  

	About the use of Program:

	Window Size 640 x 360; (min. and max. windows size in glOrtho function has ratio 1.0/640, 1.0/360)

	Starting point of mouse coordinates: left bottom.

	Exit: Q or q
	Used classes for working on rectangle better.

	Ability:
	Dragging a recrtangle with mouse. 
	Change the color of a blue rectangle with mouse click inside of it. (Used rand function for this.)

	How to Compile on Ubuntu: 
	g++ 16290085.cpp -lGL -lglut -lGLU -o 16290085 (ps)

	Screenshots while running the program:
	https://drive.google.com/open?id=0BxKz8WRIkakFVnZqeEJLZlE4NXM

	Check function:
	check function controls that if mouse is in the triangle or not. To do that I used Fermat-Toricelli Point rule.
	Let's call our triangles corner as A, B and C. Their coordinates are A(Ax,Ay), B(Bx,By), C(Cx,Xy).
	Our mouse coordinates are P(px, py).

	bx = Bx-Ax, by = By-Ay,
	cx = Cx-Ax, cy = Cy-Ay,
	k = px - Ax, l = py - Ay and d = bx * cy - cx * by.
	with this calculations I found the distance of every corner of triangle to the mouse click 
	and (wa,wb,wc) applied the rules of the functions in the code block.  */

#include <iostream> //C++ Library
#include <GL/glut.h>  //OpenGL Library

double r,g,b; // global values to change the color of triangle. r for red, g for green, b for blue. 
//They are defined here because we need them in different functions.

class Points //a class for mouse coordinates
{
public:
    double x,y; //coordinates of mouse
    Points() { x = 0.0; y = 0.0; } //default constructor
    Points(double _x, double _y) : x(_x), y(_y) {} //constructor to use variables out of the class
};

class Triangle //class of triangle
{
public:
    Points corner[3]; //corner coordinates
    Triangle() //default constructor
    {
    	corner[0] = Points(0.76,0.845); // A (up)
    	corner[1] = Points(0.63,0.35);  // B (left-bottom)
    	corner[2] = Points(0.89,0.35);  // C (right- bottom)
    }
    Points mouseCoordinates(double x, double y); //mouse coordinates to use in triangle class
};

class Rectangle // class of rectangle
{
public:
    Points corner[4]; //corner coordinates
    
    Rectangle() //default constructor
    {
    	corner[0] = Points(0.05,0.5); // A (left-bottom)
	    corner[1] = Points(0.40,0.5); // B (right-bottom)
	    corner[2] = Points(0.40,0.8); // C (right-up)
	    corner[3] = Points(0.05,0.8); // D (left-up)
    }
    Points mouseCoordinates(double x, double y); //mouse coordinates to use in rectangle class
};

Triangle* tri = new Triangle; //to create a new triangle
Rectangle* rec = new Rectangle; //to create a new rectangle

Points Triangle::mouseCoordinates(double x, double y) //mouse function to detect on screen
{
    return Points(x / 640.0, 1.0 - y /360.0); //why did we substact y/360.0 from 1.0? => because we had to find the start point of coordinates (left-bottom)
}

Points Rectangle::mouseCoordinates(double x, double y) //mouse function to detect on screen
{
    return Points(x / 640.0, 1.0 - y / 360.0); //we traversed mouse detection starting point to left-up.
}

void drawTriangle(Triangle *tri) //drawing function of triangle
{
    glColor3f(r,g,b); // color of triangle, default blue is defined in main
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // polygon mode
    glBegin(GL_POLYGON); // start drawing a polygon
        glVertex2f(tri->corner[0].x, tri->corner[0].y); //insert points into glVertex2f function to draw triangle. tri calls points in triangle constructor.
        glVertex2f(tri->corner[1].x, tri->corner[1].y);
        glVertex2f(tri->corner[2].x, tri->corner[2].y);
    glEnd(); // end drawing a polygon
}

void drawRectangle(Rectangle *rec) //drawing function of rectangle
{
    glColor3f(0.0, 0.0, 0.0); // color of recrangle frame
    glLineWidth(3); //line width
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // polygon mode for drawing an empty rectangle
    glBegin(GL_POLYGON); // start drawing a polygon 
        glVertex2f(rec->corner[0].x, rec->corner[0].y); //insert points into glVertex2f function to draw rectangle. tri calls points in rectangle constructor.
        glVertex2f(rec->corner[1].x, rec->corner[1].y);
        glVertex2f(rec->corner[2].x, rec->corner[2].y);
        glVertex2f(rec->corner[3].x, rec->corner[3].y);
    glEnd();  // end drawing a polygon
}

bool check(double px, double py) //controller if mouse is in the triangle or not (explanation is in the head comment)
{
	double bx = -0.13 , by = -0.495, cx = 0.13 , cy = -0.495;
	double k = px - 0.76;
	double l = py - 0.845;
	double d = 0.1287;
	double wa=0 , wb=0, wc=0;

		wa = (k * (by-cy) + l * (cx-bx) + bx*cy - cx * by) / d;
		wb = (k * cy - l * cx) / d;
		wc = (l * bx - k * by) / d;

		if (wa > 0 && wa < 1)
		{	
			if (wb > 0 && wb < 1)
			{
				if (wc > 0 && wc < 1)
				{
					return 1;
				}
			}
		}
}

void click (int button, int state, int x, int y) //detect mouse left click and change color
{
	Points mouseObject = tri->mouseCoordinates(x,y); //class object 
    Points* mouse = &mouseObject; // pointer to hold class object's addresses which points the current coordinates of mouse

    int control = check(mouse->x, mouse->y);

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
				if(control == 1) //if check is true that means mouse is inside of the triangle
				{
					r=(double)(rand()%255)/256; //for a full RGB scale there should be also a +1 but I didn't want to do that.
					g=(double)(rand()%255)/256;
					b=(double)(rand()%255)/256;

					glutPostRedisplay();//to call another mouse click to change color
				}			
		}		
}

void move (int x, int y) //dragging rectangle
{
    Points mouseObject = rec->mouseCoordinates(x,y); //class object 
    Points* mouse = &mouseObject; // pointer to hold class object's addresses which points the current coordinates of mouse

    if (mouse->x >= rec->corner[0].x && mouse->y >= rec->corner[0].y) //check if the mouse is on the rectangle or not
    {
    		if (mouse->x <= rec->corner[2].x && mouse->y <= rec->corner[2].y)
    		{
    		    rec->corner[0].x = mouse->x - 0.25; //change the coordinates of current rectangle (right upper)
    			rec->corner[0].y = mouse->y - 0.05; //numbers... I used 1.0 at the beginning so I had to deal with the little numbers

    			rec->corner[1].x = mouse->x + 0.1; // so numbers are kind of trial and error. That's why mouse isn't on the center while dragging
   				rec->corner[1].y = mouse->y - 0.05; //there wasn't any condition like this so I left it like that (left upper)

    			rec->corner[2].x = mouse->x + 0.1; //(left under)
    			rec->corner[2].y = mouse->y + 0.25;

    			rec->corner[3].x = mouse->x - 0.25; //(right under)*
    			rec->corner[3].y = mouse->y + 0.25; //*moves the opposite way kind of pushing

            glutPostRedisplay();
    	} 	
    }
}

void display() //display function to draw rectangle and triangle
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle(tri);
    drawRectangle(rec);
    glFlush();
}

void processNormalKeys(unsigned char key, int x, int y) //exit program
{
	if (key == 'Q' || 'q')
		exit(0);
}

int main(int iArgc, char** cppArgv) {

    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 360);
    glutInitWindowPosition(200, 200);

    glutCreateWindow("Triangle");

    glClearColor(1.0, 1.0, 1.0, 1.0); //white background
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); //screen coordinates minx, maxx, miny, maxy ,minz, maxz

    glutMouseFunc(click);
    glutMotionFunc(move);
	glutKeyboardFunc(processNormalKeys);

	   //default value of triangle: light blue. 
	   r= 0.0;
	   g= 0.639;
	   b= 0.913;

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
