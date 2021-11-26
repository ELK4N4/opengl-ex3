#include <GL/glut.h>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <iomanip>
using std::fixed;
using std::setprecision;
using std::setw;
#include <stdio.h>

class RenderState {
public:
	float mouseX, mouseY, cameraX, cameraY;
	bool mouseLeftDown, mouseRightDown;
	RenderState() {
		this->mouseX = 0;
		this->mouseY = 0;
		this->mouseLeftDown = false;
		this->mouseRightDown = false;
		this->cameraX = 0.0f;
		this->cameraY = 0.0f;
	}

};

RenderState rs;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	RenderState* rsp = new RenderState();
	rs = *rsp;
}

void exit() {
	delete &rs;
}

char spin = 0;
void keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
	{
		spin = !spin;
	}
}

float angle = 0;
void timer(int value)
{
	if (spin)
	{
		angle += 3;
	}

	glutTimerFunc(16, timer, 0);
	glutPostRedisplay();
}

void drawCoordinates() {

	// draw some lines
	glColor3f(1.0, 0.0, 0.0); // red XXX
	glBegin(GL_LINES);
	// x aix

	glVertex3f(-4.0, 0.0f, 0.0f);
	glVertex3f(4.0, 0.0f, 0.0f);

	glVertex3f(4.0, 0.0f, 0.0f);
	glVertex3f(3.0, 1.0f, 0.0f);

	glVertex3f(4.0, 0.0f, 0.0f);
	glVertex3f(3.0, -1.0f, 0.0f);
	glEnd();

	// y 
	glColor3f(0.0, 1.0, 0.0); // green YYY
	glBegin(GL_LINES);
	glVertex3f(0.0, -4.0f, 0.0f);
	glVertex3f(0.0, 4.0f, 0.0f);

	glVertex3f(0.0, 4.0f, 0.0f);
	glVertex3f(1.0, 3.0f, 0.0f);

	glVertex3f(0.0, 4.0f, 0.0f);
	glVertex3f(-1.0, 3.0f, 0.0f);
	glEnd();

	// z 
	glColor3f(0.0, 0.0, 1.0); // blue ZZZ
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0f, -4.0f);
	glVertex3f(0.0, 0.0f, 4.0f);


	glVertex3f(0.0, 0.0f, 4.0f);
	glVertex3f(0.0, 1.0f, 3.0f);

	glVertex3f(0.0, 0.0f, 4.0f);
	glVertex3f(0.0, -1.0f, 3.0f);
	glEnd();

	const double p1x = 1;
	const double p1y = 1;
	const double p1z = 0.5;

	const double p2x = 3;
	const double p2y = 0.05;
	const double p2z = 2;

	const double p3x = 2.5;
	const double p3y = 1.7;
	const double p3z = -1;


	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glBegin(GL_LINES);
	glVertex3f(p1x, p1y, p1z); // P1
	glVertex3f(p2x, p2y, p2z); // P2

	glVertex3f(p1x, p1y, p1z); // P1
	glVertex3f(p3x, p3y, p3z); // P3

	glEnd();

	//glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glRotatef(-111, 1, 0, 0);
	glRotatef(-53, 0, 1, 0);
	glTranslatef(-p1x, -p1y, -p1z);

	glBegin(GL_LINES);
	glVertex3f(p1x, p1y, p1z); // P1
	glVertex3f(p2x, p2y, p2z); // P2

	glVertex3f(p1x, p1y, p1z); // P1
	glVertex3f(p3x, p3y, p3z); // P3

	glEnd();

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(0, 0, -10.0f);
	glRotatef(rs.cameraX, 1, 0, 0);
	glRotatef(rs.cameraY, 0, 1, 0);

	glScalef(1.0, 2.0, 1.0);
	drawCoordinates();

	glFlush();
}

void mouseCallback(int button, int state, int x, int y)
{
	rs.mouseX = x;
	rs.mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			rs.mouseLeftDown = true;
		}
		else if (state == GLUT_UP)
			rs.mouseLeftDown = false;
	}
}

void mouseMotionCallback(int x, int y)
{
	if (rs.mouseLeftDown)
	{
		rs.cameraY += (x - rs.mouseX);
		rs.cameraX += (y - rs.mouseY);
		rs.mouseX = x;
		rs.mouseY = y;
	}
}


void idleCallback()
{
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idleCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotionCallback);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, timer, 0);

	glViewport(0, 0, (GLsizei)500, (GLsizei)500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
	exit();
	return 0;
}