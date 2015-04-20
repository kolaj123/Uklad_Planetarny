//Micha³ Miko³ajczak
#include <iostream>

#include <GL/freeglut.h>

// Initial translation (x,y,z) and rotation (xrot, yrot, zrot) of model coordinate system
double x = 0, y = 0, z = 0;
double xrot = 0, yrot = 0, zrot = 0;

// Last mouse position
int mouseLastX = 0, mouseLastY = 0;

// Storing information if left mouse button is clicked
bool mouseLeftBtnClicked = false;

/* GLUT callback Handlers */
static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void idle(void)
{
	glutPostRedisplay();
}

void mouseMovement(int x, int y) {

	if (mouseLeftBtnClicked)
	{
		int diffx = x - mouseLastX; //check the difference between the current x and the last x position
		int diffy = y - mouseLastY; //check the difference between the current y and the last y position
		mouseLastX = x; //set lastx to the current x position
		mouseLastY = y; //set lasty to the current y position

		// conversion between mouse plane and axes of coordination system
		yrot += diffx * 0.5; // rotation around Y axis is based on mouse movement in x direction
		xrot += diffy * 0.5; // rotation around X axis is based on mouse movement in y direction
	}
}

void onMouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		mouseLeftBtnClicked = false;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseLastX = x;
		mouseLastY = y;
		mouseLeftBtnClicked = true;
	}
}

void setModelRotationAndTranslation()
{
	// Translation of model coordinate system
	glTranslated(x, y, z);

	// Initial rotation of model coordinate system
	glRotated(xrot, 1, 0, 0);
	glRotated(yrot, 0, 1, 0);
	glRotated(zrot, 0, 0, 1);
}

float radiany(float angle)
{
	angle = 3.1415*angle / 180;
	return angle;
}
class Planeta
{
private:
	float x, y, z, r, g, b, promien;
public:
	float angle;
	Planeta(float x1, float y1, float z1, float r1, float g1, float b1, float angle1, float promien1)
	{
		this->x = x1;
		this->y = y1;
		this-> z= z1;
		this->r = r1;
		this->g = g1;
		this->b = b1;
		this->angle = angle1;
		this->promien = promien1;
	}
	void drawPierscien()//funkcja rysujaca pierscien
	{
		glRotated(110, 1, 0, 0);
		glBegin(GL_POLYGON);
		{
			for (int i = 0; i < 360; i += 1)
			{
				glColor3d(i * 0.5 / 10000.0 + 0.3, i*2.5 / 10000.0, i / 1500.0);
				glVertex3d(1.4 * cos(radiany(i)), 1.4 * sin(radiany(i)), -0.06);
				glVertex3d(1.4 * cos(radiany(i)), 1.4 * sin(radiany(i)) , 0.06);
			}
		}
		glEnd();
	}
	void drawPlaneta()//funkcja rysujaca planete
	{
		float x_X = x * cos(radiany(angle));
		float y_Y = y * sin(radiany(angle));
		glTranslated(x_X, y_Y, z);
		glColor3d(r, g, b);
		glutSolidSphere(promien, 100, 100);
	}
};

Planeta slonce(0, 0, 0, 1, 1, 0, 0, 1.75);
Planeta merkury(3, 3, 0, 0.8, 0.5, 0.2, 0, 0.2);
Planeta wenus(4, 4, 0, 1, 0.8, 0, 0, 0.3);
Planeta ziemia(8, 8, 0, 0, 0, 1, 0, 0.4);
Planeta ksiezyc(1, 1, 0, 0.9, 0.9, 0.9, 0, 0.09);
Planeta mars(14, 14, 0, 1, 0, 0, 0, 0.45);
Planeta jowisz(16, 16, 0, 1, 1, 0.6, 0, 0.76);
Planeta saturn(19, 19, 0, 1, 0.5, 0, 0, 0.8);
Planeta uran(22, 22, 0, 0.8, 0.8, 0.8, 0, 0.5);
Planeta neptun(24, 24, 0, 0.3, 0.3, 0.75, 0, 0.4);

void timer(int time)//timer zwiekszajacy kat dla kazdej z planet
{
	merkury.angle += 2.5; wenus.angle += 0.98;
	ksiezyc.angle += 7.2;
	ziemia.angle += 0.6; mars.angle += 0.32;
	jowisz.angle += 0.05; saturn.angle += 0.02;
	uran.angle += 0.007;
	neptun.angle += 0.004;
	glutTimerFunc(1, timer, 0);
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	// X axis
	if (key == 'q')
		x = x - 0.1;
	else if (key == 'w')
		x = x + 0.1;
	else if (key == 'e')
		xrot = xrot - 5;
	else if (key == 'r')
		xrot = xrot + 5;

	// Y axis
	if (key == 'a')
		y = y - 0.1;
	else if (key == 's')
		y = y + 0.1;
	else if (key == 'd')
		yrot = yrot - 5;
	else if (key == 'f')
		yrot = yrot + 5;

	// Z axis
	else if (key == 'z')
		z = z - 0.1;
	else if (key == 'x')
		z = z + 0.1;
	else if (key == 'c')
		zrot = zrot - 5;
	else if (key == 'v')
		zrot = zrot + 5;
}
static void display(void)
{
	// clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	setModelRotationAndTranslation();

	// Drawing cube at (1,1,1) with black color (0.0, 0.0, 0.0) with size = 0.5
	glPushMatrix();
	slonce.drawPlaneta();
	glPopMatrix();
	
	glPushMatrix();
	merkury.drawPlaneta();
	glPopMatrix();
	glPushMatrix();
	wenus.drawPlaneta();
	glPopMatrix();
	glPushMatrix();
	ziemia.drawPlaneta();
	ksiezyc.drawPlaneta();
	glPopMatrix();
	glPushMatrix();
	mars.drawPlaneta();
	glPopMatrix();
	glPushMatrix();
	jowisz.drawPlaneta();
	glPopMatrix();
	glPushMatrix();
	saturn.drawPlaneta();
	saturn.drawPierscien();
	glPopMatrix();
	glPushMatrix();
	uran.drawPlaneta();
	glPopMatrix();
	glPushMatrix();
	neptun.drawPlaneta();
	glPopMatrix();
	// Add your drawing functions below 
	// ...
	// ...
	// ...

	glPopMatrix();

	glutSwapBuffers();
}

void menu() {
	std::cout << "Keys: " << std::endl << std::endl;

	// X axis
	std::cout << "'q' - move coordinate system in direction of minus X" << std::endl;
	std::cout << "'w' - move coordinate system in direction of plus X" << std::endl;
	std::cout << "'e' - rotate coordinate system of minus angle around X" << std::endl;
	std::cout << "'r' - rotate coordinate system of plus angle around X" << std::endl << std::endl;

	// Y axis
	std::cout << "'a' - move coordinate system in direction of minus Y" << std::endl;
	std::cout << "'s' - move coordinate system in direction of plus Y" << std::endl;
	std::cout << "'d' - rotate coordinate system of minus angle around Y" << std::endl;
	std::cout << "'f' - rotate coordinate system of plus angle around Y" << std::endl << std::endl;

	// Z axis
	std::cout << "'z' - move coordinate system in direction of minus Z" << std::endl;
	std::cout << "'x' - move coordinate system in direction of plus Z" << std::endl;
	std::cout << "'c' - rotate coordinate system of minus angle around Z" << std::endl;
	std::cout << "'v' - rotate coordinate system of plus angle around Z" << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
	menu();

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("OpenGLUT Shapes");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(onMouseButton);
	glutMotionFunc(mouseMovement);

	// set white as the clear colour
	glClearColor(0, 0, 0.1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	timer(0);
	glutMainLoop();

	return 0;
}
/*void drawAxesOfCoordinateSystem()
{
	// Drawing axes
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	// X axis -> blue
	glPushMatrix();
	glColor3d(0.0, 0.0, 1.0);
	glRotated(90, 0, 1, 0);
	gluCylinder(quadratic, 0.1f, 0.1f, 2, 32, 32);
	glPopMatrix();

	// Y axis -> red
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(quadratic, 0.1f, 0.1f, 2, 32, 32);
	glPopMatrix();

	// Z axis -> green
	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);
	gluCylinder(quadratic, 0.1f, 0.1f, 2, 32, 32);
	glPopMatrix();
}*/