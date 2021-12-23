#include <GL/glut.h>
#include <iostream>

void left ();
void right ();
void bottom ();
void top ();
void front ();
void back ();
void Cube ();
void Draw ();
void Reshape (int width, int height);
void Keyboard (unsigned char key, int x, int y);
void Display ();

int checker = 0;
double width = 500.0, height = 500.0;
static double xangle = 0.0, yangle = 0.0;

void Cube ()
{
	left ();
	right ();
	bottom ();
	top ();
	front ();
	back ();
}

void Draw ()
{
	glBegin(GL_QUADS);
		Cube();
  	glEnd();	
}

//WHEN CHECKER IS 1 ORTHO VIEW WORKS, OTHERWISE PERSPECTIVE WORKS
void Reshape (int width, int height)
{
	glViewport(0.0, 0.0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		
		double ratio = width / height;
	
	if(checker == 1)
		//GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal,GLdouble farVal
	       glOrtho(-3.0 * ratio, 3.0 * ratio, -3.0, 3.0, 5.0, 20.0);
	
	else if(checker ==0)
		//GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar
		  gluPerspective(24.2, width / (double) height, 5.0, 20.0);
	glutPostRedisplay();
}

// W -> UP S-> DOWN A->LEFT D->RIGHT P- PERSPECTIVE TO ORTHOGONAL 
// (0 IS PERSPECTIVE, 1 IS ORTHOGONAL)
void Keyboard (unsigned char key, int x, int y)
{
	if (key == 'w')
	    yangle = yangle - 1.0; 

	else  if (key == 'a')
	    xangle = xangle - 1.0;

	else  if (key == 's')
	    yangle = yangle + 1.0;

	else if (key == 'd')
	    xangle = xangle + 1.0;

	else if (key == 'p')
	{
	 	if (checker == 0)
	 		checker = 1;

	 	else if (checker == 1)
	 		checker = 0;
	 
	Reshape(width, height);
	}
}

//DISPLAY ON SCREEN
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//Specify the x, y, and z coordinates of a translation vector.
    glTranslatef(0.0f, 0.0f, -15.0f);

//angle - Specifies the angle of rotation, in degrees. x, y, z - Specify the x, y, and z coordinates of a vector, respectively.
//based on cube's front face.
    	glRotatef(30.0, 0.0, 1.0, 0);
		glRotatef(xangle, 0.0f, 1.0f, 0.0f);

		glRotatef(30.0, 1.0, 0.0, 0.0);
		glRotatef(yangle, 1.0f, 0.0f, 0.0f);
		  
	Draw();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

//MAIN FUNCTION
int	main(int argc, char **argv)
{

//INITILIZATION
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100,50);
  glutCreateWindow("16290085 COM337 HW2");

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);

//FUNCTIONS
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);

  glutMainLoop();

  return 0;
}

//COORDINATES OF THE CUBE

void left()
{
 	glColor3f(0.301, 0.180, 0.298); 
 	
	 	glVertex3f(-1, -1, -1); 
	 	glVertex3f(-1, -1,  1);
	 	glVertex3f(-1,  1,  1);
	 	glVertex3f(-1,  1, -1);
}

void right()
{
 	glColor3f(0.094, 0.431, 0.584); 

	 	glVertex3f( 1, -1, -1);
	 	glVertex3f( 1, -1,  1);
	 	glVertex3f( 1,  1,  1);
	 	glVertex3f( 1,  1, -1);
}

void bottom()
{
	glColor3f(0.098, 0.243, 0.176);

		glVertex3f(-1, -1, -1);
		glVertex3f(-1, -1,  1);
		glVertex3f( 1, -1,  1);
		glVertex3f( 1, -1, -1);
}

void top()
{
 	glColor3f(0.2, 0.882, 0.337); 
  		glVertex3f(-1,  1, -1);
  	glColor3f(0.458, 0.882, 0.2); 
  		glVertex3f(-1,  1,  1);
  	glColor3f(0.701, 0.882, 0.2); 
  		glVertex3f( 1,  1,  1);
  	glColor3f(0.878, 0.882, 0.2); 
  		glVertex3f( 1,  1, -1);
}

void front()
{
  	glColor3f(0.925, 0.709, 0.929); 
  		glVertex3f(-1, -1,  1);
 	glColor3f(0.811, 0.709, 0.929); 
  		glVertex3f(-1,  1,  1);
  	glColor3f(0.549, 0.533, 0.827); 
  		glVertex3f( 1,  1,  1);
  	glColor3f(0.443, 0.709, 0.815); 
  		glVertex3f( 1, -1,  1);
}

void back()
{
  	glColor3f(0.890, 0.309, 0.321); 

	  	glVertex3f(-1, -1, -1);
	    glVertex3f(-1,  1, -1);
	  	glVertex3f( 1,  1, -1);
	    glVertex3f( 1, -1, -1);
}
