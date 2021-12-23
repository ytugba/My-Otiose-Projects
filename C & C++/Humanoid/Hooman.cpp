/*
GUIDE

KOLLAR					|	ELLER
Sol			Sag			|	Sol			Sag
Q (yukari)	E (yukari)	|	W (yukari)	R (yukari)
A			D			|	S			F

BACAKLAR				|	AYAKLAR
Sol			Sag			|	Sol			Sag
Z (yukari)	C (yukari)	|	G (yukari)	B (yukari)
X			K			|	H			N

YATAY DONUS				|	DIKEY DONUS				|	CAPRAZ DONUS
Sol			Sag			|	Yukari		Asagi		|	Saat		-Saat
4			6			|	8			2			|	1			9

POZISYON SIFIRLAMA		|	KAMERA SIFIRLAMA
i						|	m

ANIMASYON HIZI
ARTIS			AZALIS		DEFAULT HIZ
YUKARI OK		ASAGI OK	i

POZISYON KAYIT/YUKLEME
1. Pozisyon		2. Pozisyon		Yukleme
J				K				L

CIKIS
P
*/

#include <GL/glut.h>
#include <iostream>
#include <fstream>
using namespace std;

//GLOBAL VARIABLES
enum 
{
	GOVDE = 0, 
	SOLUK, SOLAK,
	SAGUK, SAGAK,
	SOLUB, SOLAB,
	SAGUB, SAGAB,
	BOYUT 
};

float KAFA_YUKSEKLIK = 7.0, KAFA_CAP = 3.0;
float GOVDE_YUKSEKLIK = 10.0, GOVDE_CAP = 2.0;
float UST_KOL_YUKSEKLIK = 6.0, ALT_KOL_YUKSEKLIK = 4.0;
float UST_KOL_CAP = 1.0, ALT_KOL_CAP = 1.0;
float UST_BACAK_YUKSEKLIK = 9.0, ALT_BACAK_YUKSEKLIK = 2.0;
float UST_BACAK_CAP = 1.0, ALT_BACAK_CAP = 1.0;

float xRotate = 0, yRotate = 0, zRotate=0;

float a[BOYUT] = { 0 };
float b[BOYUT] = { 0 };
float aci[BOYUT] = { 0 };

bool interpolate_bool = false;
bool go_up[BOYUT] = { true, true, true, true, true, true, true, true, true};
int speed = 50;

GLUquadricObj *g, *k; /* govde, kafa */
GLUquadricObj *soluk, *solak, *saguk, *sagak; /* kollar */
GLUquadricObj *solub, *solab, *sagub, *sagab; /* bacaklar */

//COORDINATES OF HUMANOID FUNCTION DEFINITIONS
void head();
void govde();
void sol_ust_kol();
void sol_alt_kol();
void sag_ust_kol();
void sag_alt_kol();
void sol_ust_bacak();
void sol_alt_bacak();
void sag_ust_bacak();
void sag_alt_bacak();

//FUNCTION DEFINITIONS
void writeFile(int a);
void interpolate(int d);
void DrawRobot(float x, float y, float z, float soluk, float solak, float saguk, float sagak, float solub, float solab, float sagub, float sagab);
void InitQuadrics();
void Display();
void Keyboard(unsigned char key, int x, int y);
void view();
void speed_of_animation(int key, int x, int y);

//FUNCTIONS
void view()
{
	glClearColor(0.19f, 0.49f, 0.32f, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1.0f, 10.0f, -15.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 40, 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	InitQuadrics();
}

void writeFile(int a)
{
	ofstream myfile;
	
	if (a == 1)	
		myfile.open("1in.txt");
	
	if (a == 2)	 
		myfile.open("2in.txt");

	for (int i = 0; i<BOYUT; i++)
		myfile << aci[i] << " ";

	myfile.close();
}

void InitQuadrics() 
{
	g = gluNewQuadric();
	gluQuadricDrawStyle(g, GLU_FILL);

	soluk = gluNewQuadric();
	gluQuadricDrawStyle(soluk, GLU_FILL);
	
	k = gluNewQuadric();
	gluQuadricDrawStyle(k, GLU_FILL);
	
	solak = gluNewQuadric();
	gluQuadricDrawStyle(solak, GLU_FILL);
	
	saguk = gluNewQuadric();
	gluQuadricDrawStyle(saguk, GLU_FILL);
	
	solub = gluNewQuadric();
	gluQuadricDrawStyle(solub, GLU_FILL);
	
	solab = gluNewQuadric();
	gluQuadricDrawStyle(solab, GLU_FILL);
	
	sagub = gluNewQuadric();
	gluQuadricDrawStyle(sagub, GLU_FILL);
	
	sagab = gluNewQuadric();
	gluQuadricDrawStyle(sagab, GLU_FILL);
}

void interpolate(int d) 
{
	if (d) 
	{
		for (int i = 0; i<BOYUT; i++) 
		{
			if ((b[i] - a[i]) < 0) 
			{
				if (go_up[i]) 
				{
					if (aci[i] >= b[i] && aci[i] <= a[i])
							aci[i] += (b[i] - a[i]) / speed;
					if (aci[i] <= b[i]) 
					{
						go_up[i] = !go_up[i];
						aci[i] = b[i];
					}
				}
				else 
				{
					if (aci[i] >= b[i] && aci[i] <= a[i])
							aci[i] -= (b[i] - a[i]) / speed;
					if (aci[i] >= a[i]) 
					{
						go_up[i] = !go_up[i];
						aci[i] = a[i];
					}
				}
			}
			else 
			{
				if (go_up[i]) 
				{
					if (aci[i] <= b[i] && aci[i] >= a[i]) 
						aci[i] += (b[i] - a[i]) / speed;
					if (aci[i] >= b[i]) 
					{
						go_up[i] = !go_up[i];
						aci[i] = b[i];
					}
				}
				else
				{
					if (aci[i] <= b[i] && aci[i] >= a[i]) 
						aci[i] -= (b[i] - a[i]) / speed;
					if (aci[i] <= a[i]) 
					{
						go_up[i] = !go_up[i];
						aci[i] = a[i];
					}
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(20, interpolate, interpolate_bool);
}

void DrawRobot(float x, float y, float z, float soluk, float solak, float saguk, float sagak, float solub, float solab, float sagub, float sagab)
{
	//GOVDE
	govde();

	glPushMatrix(); //KAFA
		glTranslatef(0, KAFA_YUKSEKLIK / 2, 0);
		head();
	glPopMatrix();

	glPushMatrix(); //SOL KOL
		glTranslatef(GOVDE_CAP, 0, 0);
		glRotatef(soluk, 0, 0, 1);
		sol_ust_kol();

		glTranslatef(UST_KOL_YUKSEKLIK, 0, 0);
		glRotatef(solak, 0, 0, 1);
		sol_alt_kol();
	glPopMatrix();

	glPushMatrix(); //SAG KOL
		glTranslatef(-GOVDE_CAP, 0, 0);
		glRotatef(saguk, 0, 0, 1);
		sag_ust_kol();

		glTranslatef(-UST_KOL_YUKSEKLIK, 0, 0);
		glRotatef(sagak, 0, 0, 1);
		sag_alt_kol();
	glPopMatrix();

	glPushMatrix(); //SOL BACAK
		glTranslatef(GOVDE_CAP, -GOVDE_YUKSEKLIK, 0);
		glRotatef(solub, 1, 0, 0);
		sol_ust_bacak();

		glTranslatef(0, -UST_BACAK_YUKSEKLIK, 0);
		glRotatef(solab, 1, 0, 0);
		sol_alt_bacak();
	glPopMatrix();

	glPushMatrix(); //SAG BACAK
		glTranslatef(-GOVDE_CAP, -GOVDE_YUKSEKLIK, 0);
		glRotatef(sagub, 1, 0, 0);
		sag_ust_bacak();

		glTranslatef(0, -UST_BACAK_YUKSEKLIK, 0);
		glRotatef(sagab, 1, 0, 0);
		sag_alt_bacak();
	glPopMatrix();
}

void Display()
{

	glDrawBuffer(GL_FRONT_AND_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 40, 0, 0, 0, 0, 1, 0);

	glRotatef(xRotate, 0, 1, 0);

	glRotatef(yRotate, 1, 0, 0);

	glRotatef(zRotate, 0, 0, 1);

	DrawRobot(0, 0, 0, aci[SOLUK], aci[SOLAK], aci[SAGUK], aci[SAGAK], aci[SOLUB], aci[SOLAB], aci[SAGUB], aci[SAGAB]);

	glFlush();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'a':
		aci[SAGUK] += 5; break;
	case 'q':
		aci[SAGUK] -= 5; break;
	case 'e':
		aci[SOLUK] += 5; break;
	case 'd':
		aci[SOLUK] -= 5; break;
	case 'z':
		aci[SAGUB] += 5; break;
	case 'x':
		aci[SAGUB] -= 5; break;
	case 'c':
		aci[SOLUB] += 5; break;
	case 'v':
		aci[SOLUB] -= 5; break;
	case 's':
		aci[SAGAK] += 5; break;
	case 'w':
		aci[SAGAK] -= 5; break;
	case 'r':
		aci[SOLAK] += 5; break;
	case 'f':
		aci[SOLAK] -= 5; break;
	case 'g':
		aci[SAGAB] += 5; break;
	case 'h':
		aci[SAGAB] -= 5; break;
	case 'b':
		aci[SOLAB] += 5; break;
	case 'n':
		aci[SOLAB] -= 5; break;
	case '4':
		xRotate -= 5.0; break;
	case '6':
		xRotate += 5.0; break;
	case '8':
		yRotate -= 5.0; break;
	case '2':
		yRotate += 5.0; break;
	case '1':
		zRotate -= 5; break;
	case '9':
		zRotate += 5; break;
	case 'j':
		writeFile(1); break;
	case 'k':
		writeFile(2); break;
	case 'l': 
	{
		ifstream myfile1; 
			myfile1.open("1in.txt");
		ifstream myfile2; 
			myfile2.open("2in.txt");
	
		for (int i = 0; i<BOYUT; i++) 
		{
			myfile1 >> a[i];
			myfile2 >> b[i];
		}

			myfile1.close();
			myfile2.close();

		interpolate_bool = !interpolate_bool;

		break;
	}
	case 'i':
		for (int i = 0; i<BOYUT; i++)
			aci[i] = 0;
			speed = 50;
			break;
	case 'm':
		yRotate = 0;
		xRotate = 0;
		zRotate = 0;
		break;
	case 'p':
		exit(0);
	}
	glutPostRedisplay();
}

void speed_of_animation(int key, int x, int y)
{
	if (speed >= 0 && speed <= 50)
	{
		if (key == GLUT_KEY_UP)
			speed--;
		if (key == GLUT_KEY_DOWN)
			speed++;
	}
}

//MAIN FUNCTION
int main (int argc, char **argv) 
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200,50);
	glutCreateWindow("16290085 & 16290616");

	view();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(speed_of_animation);
	glutTimerFunc(20, interpolate, interpolate_bool);

	glutMainLoop();
}

//COORDINATES OF HUMANOID
void head()
{
	glPushMatrix();
	glColor3f(1.0f, 0.93f, 0.57f);
	glScalef(KAFA_CAP, KAFA_YUKSEKLIK / 2, KAFA_CAP);
	gluSphere(k, 1.0, 100, 100);
	glPopMatrix();
}

void govde()
{
	glPushMatrix();
	glColor3f(0.6f, 0.11f, 0.09f);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(g, GOVDE_CAP, GOVDE_CAP, GOVDE_YUKSEKLIK, 1000, 1000);
	glPopMatrix();
}

void sol_ust_kol()
{
	glPushMatrix();
	glColor3f(0.6f, 0.11f, 0.09f);
	glRotatef(90, 0, 1, 0);
	gluCylinder(soluk, UST_KOL_CAP, UST_KOL_CAP, UST_KOL_YUKSEKLIK, 100, 100);
	glPopMatrix();
}

void sol_alt_kol()
{
	glPushMatrix();
	glColor3f(1.0f, 0.93f, 0.57f);
	glRotatef(90, 0, 1, 0);
	gluCylinder(solak, ALT_KOL_CAP, ALT_KOL_CAP, ALT_KOL_YUKSEKLIK, 100, 100);
	glPopMatrix();
}

void sag_ust_kol()
{
	glPushMatrix();
	glColor3f(0.6f, 0.11f, 0.09f);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(saguk, UST_KOL_CAP, UST_KOL_CAP, UST_KOL_YUKSEKLIK, 100, 100);
	glPopMatrix();
}

void sag_alt_kol()
{
	glPushMatrix();
	glColor3f(1.0f, 0.93f, 0.57f);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(solak, ALT_KOL_CAP, ALT_KOL_CAP, ALT_KOL_YUKSEKLIK, 100, 100);
	glPopMatrix();
}

void sol_ust_bacak()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(solub, UST_BACAK_CAP, UST_BACAK_CAP, UST_BACAK_YUKSEKLIK, 100, 100);
	glPopMatrix();
}

void sol_alt_bacak()
{
	glPushMatrix();
	glColor3f(1.0f, 0.93f, 0.57f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(solab, ALT_BACAK_CAP, ALT_BACAK_CAP, ALT_BACAK_YUKSEKLIK, 100, 100);
	glPopMatrix();
}

void sag_ust_bacak()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(sagub, UST_BACAK_CAP, UST_BACAK_CAP, UST_BACAK_YUKSEKLIK, 100, 100);
	glPopMatrix();
}

void sag_alt_bacak()
{
	glPushMatrix();
	glColor3f(1.0f, 0.93f, 0.57f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(sagab, ALT_BACAK_CAP, ALT_BACAK_CAP, ALT_BACAK_YUKSEKLIK, 100, 100);
	glPopMatrix();
}
