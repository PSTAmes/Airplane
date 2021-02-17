#include <Windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265f

GLfloat windowW = 20;
GLfloat windowH = 20;

// vertices for the plain
GLfloat x = -20.0f;
GLfloat y = -5.0f;
GLfloat z = -5.0f;
GLfloat move = 0.3f;

// variables to move outermost Object Frame (to move all the rendered environment)
GLfloat moveX = 0.12f;
GLfloat moveY = 0.00f;
GLfloat moveZ = 0.0f;

// variables to rotate outermost Object Frame (to move all the rendered environment)
GLfloat rotX = 0.2f;
GLfloat rotY = 0.2f;
GLfloat rotZ = 0.0f;

// For animating the rotation of the objects
GLfloat animateRotation = 0.0f;

//variables to move the camera
GLfloat camY = 0.0f;
GLfloat camX = 0.0f;
GLfloat camZ = 0.0f;

//lighting properties
void initLighting() {
	GLfloat L0_Ambient[] = { 0.4,0.4,0.4,1.0 };
	GLfloat L0_Diffuse[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L0_position[] = {5,5,0,1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, L0_position);

	GLfloat L1_Ambient[] = { 0.6,0.6,0.6,1.0 };
	GLfloat L1_Diffuse[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L1_Specular[] = { 0.0,1.0,0.,1.0 };
	GLfloat L1_position[] = { -5,-5,0,1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, L1_position);

	GLfloat specularReflectance[] = { 1.0,1.0,1.0,1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
	glMateriali(GL_FRONT, GL_SHININESS, 50);

	GLfloat L2_Ambient[] = { 0.5,0.5,0.5,1.0 };
	GLfloat L2_Diffuse[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L2_Specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat L2_position[] = { 0,5,5,1.0 };
	GLfloat L2_spotDirection[] = { 0.0,-1.0,-1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_Diffuse);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_Specular);
	glLightfv(GL_LIGHT2, GL_POSITION, L2_position);

	glMaterialfv(GL_LIGHT2, GL_SPOT_DIRECTION, L2_spotDirection);
	glMateriali(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);

	
}

void init() {

	GLfloat globalAmbient[] = { 0.4,0.4,0.4,1.0 };

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	initLighting();


	//glEnable(GL_CULL_FACE);                 // Enable Hidden Surface Removal
	glPolygonMode(GL_FRONT, GL_FILL);       // Set the Front of the faces of the cube to be unfilled (Skeleton Model)
	glPolygonMode(GL_BACK, GL_FILL);
	glLineWidth(1.0);
}

void wheel(int x, int y) {
	float th;
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.5, 1.0);
	for (int i = 0; i < 360; i++) {
		th = i* (PI / 180);
		glVertex2f(x + 20 * cos(th), y + 20 * sin(th));
	}
	glEnd();

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat radius = 1.0f;

	//gluLookAt(0.0f+camX, 0.0f+camY, 0.0f+camZ,0,0,0,1.0,0,0);

	//windows
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(x+1.2f, y+0.5f, z + 0.2f);
	glVertex3f(x+1.9f, y+0.5f, z + 0.2f);
	glVertex3f(x+1.9f, y+(-0.5f), z + 0.2f);
	glVertex3f(x+1.2f, y+(-0.5f), z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x+(-0.2f), y+ 0.5f, z + 0.2f);
	glVertex3f(x+0.5f, y+0.5f, z + 0.2f);
	glVertex3f(x+0.5f, y+(-0.5f), z + 0.2f);
	glVertex3f(x+(-0.2f), y+(-0.5f), z + 0.2f);
	glEnd();
	//glTranslatef(9.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex3f(x+(-1.6f), y+0.5f, z + 0.2f);
	glVertex3f(x+(-0.9f), y+0.5f, z + 0.2f);
	glVertex3f(x+(-0.9f), y+(-0.5f), z + 0.2f);
	glVertex3f(x+(-1.6f), y+(-0.5f), z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x+(-3.0f), y+0.5f, z + 0.2f);
	glVertex3f(x+(-2.3f), y+0.5f, z + 0.2f);
	glVertex3f(x+(-2.3f), y+(-0.5f), z + 0.2f);
	glVertex3f(x+(-3.0f), y+(-0.5f), z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x+(-4.4f),y+ 0.5f, z + 0.2f);
	glVertex3f(x+(-3.7f),y+ 0.5f, z + 0.2f);
	glVertex3f(x+(-3.7f),y+ (-0.5f), z + 0.2f);
	glVertex3f(x+(-4.4f),y+( -0.5f), z + 0.2f);
	glEnd();

	glPopMatrix();

	//windscreen
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(x+6.8f, y+2.0f,z + 0.2f);
	glVertex3f(x+7.3f, y+1.0f, z + 0.2f);
	glVertex3f(x+7.5f, y+0.1f, z + 0.2f);
	glVertex3f(x+6.4f, y+1.2f, z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x+5.6f, y+0.6f, z + 0.2f);
	glVertex3f(x+6.3f, y+1.1f, z + 0.2f);
	glVertex3f(x+7.4f, y, z + 0.2f);
	glVertex3f(x+6.2f, y+(-0.8f), z + 0.2f);
	glEnd();

	glPopMatrix();

	//Door
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glVertex3f(x+5.1f, y + (-2.6f), z + 0.2f);
	glVertex3f(x+3.5f, y + (-2.6f), z + 0.2f);
	glVertex3f(x+3.5f, y + (-2.6f), z + 0.2f);
	glVertex3f(x+3.5f, y + (-0.2f), z + 0.2f);
	glVertex3f(x+3.5f, y + (-0.2f), z + 0.2f);
	glVertex3f(x+5.1f, y + (-0.2f), z + 0.2f);
	glVertex3f(x+5.1f, y + (-0.2f), z + 0.2f);
	glVertex3f(x+5.1f, y + (-2.6f), z + 0.2f);
	glEnd();
	
	//Body
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.5, 1.0, 1.0);
	
	glBegin(GL_POLYGON);
	glVertex3f(x + 0.0f, y + 2.5f, 0.2f);
	glVertex3f(x + 4.0f, y + 2.5f, 0.2f);
	glVertex3f(x + 5.6f, y + 2.4f, 0.2f);

	glVertex3f(x + 6.8f, y + 2.0f, 0.2f);
	glVertex3f(x + 7.30f, y + 1.0f, 0.2f);

	glVertex3f(x + 9.0f, y + 0.5f, 0.2f);
	glVertex3f(x + 10.0f, y + 0.0f, 0.2f);
	glVertex3f(x + 10.4f, y + (-0.3f), 0.2f);
	glVertex3f(x + 10.5f, y + (-0.7f), 0.2f);
	glVertex3f(x + 9.8f, y + (-1.5f), 0.2f);
	glVertex3f(x + 8.5f, y + (-2.0f), 0.2f);
	glVertex3f(x + 7.2f, y + (-2.3f), 0.2f);

	//wheel(200, 100);

	glVertex3f(x + 5.6f, y + (-2.6f), 0.2f);
	glVertex3f(x + 4.0f, y + (-2.6f), 0.2f);
	glVertex3f(x + 2.0f, y + (-2.5f), 0.2f);

	glVertex3f(x + 0.0f, y + (-2.5f), 0.2f);
	glVertex3f(x + (-1.6f), y + (-2.3f), 0.2f);
	glVertex3f(x + (-3.2f), y + (-2.1f), 0.2f);
	glVertex3f(x + (-5.5f), y + (-1.9f), 0.2f);
	glVertex3f(x + (-7.4f), y + (-1.7f), 0.2f);

	//wheel(380, 100);

	glVertex3f(x + (-8.3f), y + (-1.5f), 0.2f);
	glVertex3f(x + (-9.0f), y + (-1.3f), 0.2f);
	glVertex3f(x + (-9.8f), y + (-0.7f), 0.2f);
	glVertex3f(x + (-10.4f), y + (-0.3f), 0.2f);
	glVertex3f(x + (-10.5f), y + (-0.1f), 0.2f);

	glVertex3f(x + (-10.4f), y + 0.2f, 0.2f);
	glVertex3f(x + (-9.8f), y + 0.4f, 0.2f);
	glVertex3f(x + (-8.8f), y + 0.6f, 0.2f);
	glVertex3f(x + (-7.00f), y + 1.2f, 0.2f);
	glVertex3f(x + (-5.0f), y + 1.8f, 0.2f);
	glVertex3f(x + (-3.4f), y + 2.1f, 0.2f);
	glVertex3f(x + (-2.4f), y + 2.3f, 0.2f);
	glTranslatef(9.0, 1.0, 0.0);
	glRotatef(rotX, 0.0f, 0.0f, 1.0f);
	//glutSolidSphere(0.4, 100, 100);
	glEnd();
	glPopMatrix();

	
	//right wing
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.5, 1.0, 1.0);

	glBegin(GL_POLYGON);
	//glVertex3f(3.1f, -1.9f, 0.2f);
	glVertex3f(x + 2.7f, y + (-2.5f), 0.2f);
	glVertex3f(x + 2.4f, y + (-3.0f), 0.2f); //b
	/*glVertex3f(3.0f, -3.3f, 0.2f);
	glVertex3f(3.2f, -3.8f, 0.2f);
	glVertex3f(2.8f, -3.9f, 0.2f);
	glVertex3f(2.2f, -3.7f, 0.2f); //f

	glVertex3f(2.2f, -3.7f, 0.2f); //f 	*/
	glVertex3f(x + 1.8f, y + (-4.5f), 0.2f);
	//glVertex3f(2.8f, -4.8f, 0.2f);
	//glVertex3f(2.9f, -5.2f, 0.2f);
	//glVertex3f(2.4f, -5.4f, 0.2f);
	glVertex3f(x + 1.5f, y + (-5.1f), 0.2f);
	glVertex3f(x + 0.3f, y + (-7.4f), 0.2f);
	glVertex3f(x + (-0.1f), y + (-7.2f), 0.2f);
	glVertex3f(x + (-1.5f), y + (-6.8f), 0.2f);

	glVertex3f(x + -1.3f, y + (-6.3f), 0.2f);
	glVertex3f(x + -1.0f, y + (-6.4f), 0.2f);
	glVertex3f(x + -0.1f, y + (-2.8f), 0.2f);
	glVertex3f(x + -0.3f, y + (-2.4f), 0.2f);
	//glVertex3f(-0.1f, -1.8f, 0.2f);
	glEnd();
	glTranslatef(9.0, 1.0, 0.0);
	glRotatef(rotX, 0.0f, 0.0f, 1.0f);
	glPopMatrix();

	//left wing
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.5, 1.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(x + 3.0f, y + 2.5f, 0.2f);
	glVertex3f(x + 1.5f, y + 5.4f, 0.2f);
	glVertex3f(x + 0.2f, y + 4.8f, 0.2f);
	glVertex3f(x + 0.2f, y + 4.5f, 0.2f);
	glVertex3f(x + 0.4f, y + 4.6f, 0.2f);
	glVertex3f(x + 0.8f, y + 2.5f, 0.2f);
	glEnd();
	glTranslatef(9.0, 1.0, 0.0);
	glRotatef(rotX, 0.0f, 0.0f, 1.0f);
	glPopMatrix();

	//back right wing
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.5, 1.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(x + -5.5f, y + (-1.9f), 0.2f);
	glVertex3f(x + -6.8f, y + (-4.0f), 0.2f);
	glVertex3f(x + -8.1f, y + (-3.5f), 0.2f);
	glVertex3f(x + -7.4f, y + (-1.5f), 0.2f);
	glEnd();
	glTranslatef(9.0, 1.0, 0.0);
	glRotatef(rotX, 0.0f, 0.0f, 1.0f);
	glPopMatrix();

	//fin
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.5, 1.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(x + -5.0f, y + 1.8f, 0.2f);
	glVertex3f(x + -7.0f, y + 1.2f, 0.2f);
	glVertex3f(x + -8.5f, y + 4.5f, 0.2f);
	glVertex3f(x + -7.2f, y + 4.1f, 0.2f);
	glEnd();
	glTranslatef(9.0, 1.0, 0.0);
	glRotatef(rotX, 0.0f, 0.0f, 1.0f);
	glPopMatrix();

	glutSwapBuffers();

}


void Timer(int value) {

	//if (x >= windowW - move || x <= -windowW)
		//moveX = -moveX;
	//if (y >= windowH - move || y <= -windowH)
		//moveY = -moveY;

	//glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT0);
	x += moveX;
	y += moveY;
	z += moveZ;
	

	if (x >= -5.0f) {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		moveX = 0.10f;
		moveY = 0.05f;
		moveZ = 0.02f;
		x += moveX;
		y += moveY;
		z += moveZ;
		glutPostRedisplay();
		glutTimerFunc(60, Timer, 5);
	}

	glutPostRedisplay();
	glutTimerFunc(60, Timer, 1);
}

void changeSize(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-windowW, windowW, -windowH / aspect_ratio, windowH / aspect_ratio, 20.0, -20.0);
	}
	else {
		glOrtho(-windowW * aspect_ratio, windowW * aspect_ratio, -windowH, windowH, 20.0, -20.0);
	}

	//gluPerspective(120.0, aspect_ratio, 2.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(1400, 800);
	glutInitWindowPosition(50, 10);
	glutCreateWindow("OpenGL Setup Test");
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutTimerFunc(80, Timer, 3);
	init();
	glutMainLoop();

	return 0;
}