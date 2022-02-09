#include <Windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "SOIL2.h"
#include <string.h>
#include <stdlib.h>
#define PI 3.14159265f

GLfloat windowW = 20;
GLfloat windowH = 20;

//count variables 
int count = 0;

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

//texture 
GLuint tex;
GLuint cloudtx;
GLuint road;
GLuint plainBody;
GLuint grass;
GLuint tire;

void output(int x, int y, char* string, void* font) {

	int len, i;

	glRasterPos2f(x, y);

	len = (int)strlen(string);

	for (i = 0; i < len; i++) {

		glutBitmapCharacter(font, string[i]);

	}

}

void initTexture() {

	int width, height;
	unsigned char* image = SOIL_load_image("D:/UOP/YR 3/SEMESTER II/CS308 - COMPUTER GRAPHICS PROGRAMMING/Project/temp/Plain/Plain/Building.jpg", &width, &height, 0, SOIL_LOAD_RGB);


	if (!image) {
		std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
	}
	else {
		std::cout << &image << std::endl;
	}


	unsigned char data[] =
	{
		128, 128, 128, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);

}

void initTextureTire() {

	int width, height;
	unsigned char* image = SOIL_load_image("D:/UOP/YR 3/SEMESTER II/CS308 - COMPUTER GRAPHICS PROGRAMMING/Project/temp/Plain/Plain/tire.jpg", &width, &height, 0, SOIL_LOAD_RGB);


	if (!image) {
		std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
	}
	else {
		std::cout << &image << std::endl;
	}


	unsigned char data[] =
	{
		128, 128, 128, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	glGenTextures(1, &tire);
	glBindTexture(GL_TEXTURE_2D, tire);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);

}

void initTextureCloud() {

	int width, height;
	unsigned char* image = SOIL_load_image("D:/UOP/YR 3/SEMESTER II/CS308 - COMPUTER GRAPHICS PROGRAMMING/Project/temp/Plain/Plain/cloud.jpg", &width, &height, 0, SOIL_LOAD_RGB);


	if (!image) {
		std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
	}
	else {
		std::cout << &image << std::endl;
	}


	unsigned char data[] =
	{
		128, 128, 128, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	glGenTextures(1, &cloudtx);
	glBindTexture(GL_TEXTURE_2D, cloudtx);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);

	
}

void initTextureroad() {

	int width, height;
	unsigned char* image = SOIL_load_image("D:/UOP/YR 3/SEMESTER II/CS308 - COMPUTER GRAPHICS PROGRAMMING/Project/temp/Plain/Plain/bg.jpg", &width, &height, 0, SOIL_LOAD_RGB);


	if (!image) {
		std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
	}
	else {
		std::cout << &image << std::endl;
	}


	unsigned char data[] =
	{
		128, 128, 128, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	glGenTextures(1, &road);
	glBindTexture(GL_TEXTURE_2D, road);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);

	
}

void initTextureGrass() {

	int width, height;
	unsigned char* image = SOIL_load_image("D:/UOP/YR 3/SEMESTER II/CS308 - COMPUTER GRAPHICS PROGRAMMING/Project/temp/Plain/Plain/bg.jpg", &width, &height, 0, SOIL_LOAD_RGB);



	if (!image) {
		std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
	}
	else {
		std::cout << &image << std::endl;
	}


	unsigned char data[] =
	{
		128, 128, 128, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	glGenTextures(1, &grass);
	glBindTexture(GL_TEXTURE_2D, grass);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);


}

void initTexturePlain() {

	int width, height;
	unsigned char* image = SOIL_load_image("D:/UOP/YR 3/SEMESTER II/CS308 - COMPUTER GRAPHICS PROGRAMMING/Project/temp/Plain/Plain/body.jpg", &width, &height, 0, SOIL_LOAD_RGB);


	if (!image) {
		std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
	}
	else {
		std::cout << &image << std::endl;
	}


	unsigned char data[] =
	{
		128, 128, 128, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	glGenTextures(1, &plainBody);
	glBindTexture(GL_TEXTURE_2D, plainBody);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);

}


//lighting properties
void initLighting() {
	//GLfloat L0_Ambient[] = { 0.2,0.2,0.4,1.0 };
	//GLfloat L0_Diffuse[] = { 0.7,0.5,0.7,1.0 };
	//GLfloat L0_position[] = {5,5,0,1.0 };

	//glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, L0_position);

	//GLfloat L1_Ambient[] = { 0.6,0.3,0.6,1.0 };
	GLfloat L1_Diffuse[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L1_Specular[] = { 1,0,0,1.0 };
	GLfloat L1_position[] = { 5,5,0,1.0 };

	//glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, L1_position);

	GLfloat specularReflectance[] = { 1.0,1.0,1.0,1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
	glMateriali(GL_FRONT, GL_SHININESS, 50);
}

void init() {

	GLfloat globalAmbient[] = { 0.5,0.5,0.5,1.0 };

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

	//texture
	glShadeModel(GL_SMOOTH);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Enabling the color tracking of each faces of the materials. this enables the color visibility of the materials
	glEnable(GL_COLOR_MATERIAL);

	// enable the normalization of the normal vectors (converting the vector values to the range 0-1)
	glEnable(GL_NORMALIZE);

	initTexture();
}


GLfloat* calNormal(GLfloat* va, GLfloat* vb) {
	GLfloat vNormal[3] = {};
	vNormal[0] = va[1] * vb[2] - va[2] * vb[1];
	vNormal[1] = va[0] * vb[2] - va[2] * vb[0];
	vNormal[2] = va[0] * vb[1] - va[1] * vb[0];

	return vNormal;
}

GLfloat* findNormal(GLfloat* a, GLfloat* b, GLfloat* c) {

	GLfloat va[] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
	GLfloat vb[] = { c[0] - a[0], c[1] - a[1], c[2] - a[2] };

	return calNormal(va, vb);
}


void wheel() {
	initTextureTire();
	GLfloat wheelx = 0.0f;
	GLfloat wheely = 0.0f;
	GLfloat wheelz = 0.0f;

	if (x <= -10.0f) {
		wheelx = 8.4f;
		wheely = -3.6f;
		wheelz = -3.0f;

		glBegin(GL_POLYGON);
		glColor3f(0.5, 1.0, 1.0);
		glVertex3f(x + 7.9f, y + -2.3f, z + 3.0f);
		glVertex3f(x + 7.7f, y + -2.2f, z + 3.0f);
		glVertex3f(x + 8.0f, y + -3.1f, z + 3.0f);
		glVertex3f(x + 8.3f, y + -3.0f, z + 3.0f);
		glEnd();

		glPushMatrix();
		glColor3f(0.5, 1.0, 1.0);
		glScalef(1.0f, 1.0f, 0.2f);
		glTranslatef(x + wheelx, y + wheely, z + wheelz);
		glTexCoord2f(0, 1);
		glutSolidTorus(0.25, 0.5, 32, 32);
		glPopMatrix();

		wheelx = -3.5f;
		wheely = -3.6f;
		wheelz = -3.0f;

		glBegin(GL_POLYGON);
		glColor3f(0.5, 1.0, 1.0);
		glVertex3f(x + -4.0f, y + -1.9f, z + 3.0f);
		glVertex3f(x + -4.3f, y + -1.8f, z + 3.0f);
		glVertex3f(x + -3.6f, y + -3.1f, z + 3.0f);
		glVertex3f(x + -3.8f, y + -3.0f, z + 3.0f);
		glEnd();

		glPushMatrix();
		glColor3f(0.5, 1.0, 1.0);
		glScalef(1.0f, 1.0f, 0.2f);
		glTranslatef(x + wheelx, y + wheely, z + wheelz);
		glTexCoord2f(1, 1);
		glutSolidTorus(0.25, 0.5, 32, 32);
		glPopMatrix();

		wheelx = -2.5f;
		wheely = -3.2f;
		wheelz = -3.0f;

		glBegin(GL_POLYGON);
		glColor3f(0.5, 1.0, 1.0);
		glVertex3f(x + -3.3f, y + -1.9f, z + 3.0f);
		glVertex3f(x + -3.0f, y + -1.8f, z + 3.0f);
		glVertex3f(x + -2.6f, y + -2.8f, z + 3.0f);
		glVertex3f(x + -2.8f, y + -2.7f, z + 3.0f);
		glEnd();

		glPushMatrix();
		glColor3f(0.5, 1.0, 1.0);
		glScalef(1.0f, 1.0f, 0.2f);
		glTranslatef(x + wheelx, y + wheely, z + wheelz);
		glTexCoord2f(1, 0);
		glutSolidTorus(0.25, 0.5, 32, 32);
		glPopMatrix();

		glutPostRedisplay();

	}else if((x >= -20.0f) && (x <= 0.0f)){
		wheelx -= 0.01f;
		wheely -= 0.005f;
		wheelz -= 0.005f;

		glPushMatrix();
		glColor3f(0.5, 1.0, 1.0);
		glScalef(1.0f, 1.0f, 0.2f);
		glTranslatef(x + wheelx, y + wheely, z + wheelz);
		glTexCoord2f(0, 0);
		glutSolidTorus(0.25, 0.5, 32, 32);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5, 1.0, 1.0);
		glScalef(1.0f, 1.0f, 0.2f);
		glTranslatef(x + wheelx, y + wheely, z + wheelz);
		glTexCoord2f(1, 0);
		glutSolidTorus(0.25, 0.5, 32, 32);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5, 1.0, 1.0);
		glScalef(1.0f, 1.0f, 0.2f);
		glTranslatef(x + wheelx, y + wheely, z + wheelz);
		glTexCoord2f(0, 1);
		glutSolidTorus(0.25, 0.5, 32, 32);
		glPopMatrix();

		glutPostRedisplay();
	}

}

void background() {
	initTextureGrass();
	/*glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(38, y + 6, z + 15);
	glTexCoord2f(1, 1);
	glVertex3f( 38, y + 95, z + 25);
	glTexCoord2f(0, 0);
	glVertex3f( -40, y + 45, z + 45);
	glTexCoord2f(0, 1);
	glVertex3f(-40, y + 6, z + 20);
	glEnd();*/

	glBegin(GL_QUADS);
	{
		GLfloat back[4][4] = {
				{38, 1, 10},
				{38, 90, 40},
				{-41, 90, 40},
				{-41, 1, 10}
		};

		glNormal3fv(findNormal(back[0], back[1], back[2]));
		glScalef(1.5, 1, 1.25);
		glTranslatef(-28.5, 0, -5);
		glTexCoord2f(1,1);
		glVertex3fv(back[0]);
		glTexCoord2f(1,0);
		glVertex3fv(back[1]);
		glTexCoord2f(0,0);
		glVertex3fv(back[2]);
		glTexCoord2f(0,1);
		glVertex3fv(back[3]);
	}
	glEnd();

	
}


void cloud(){
	//cloud1
	initTextureCloud();
	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(10, 11.5, -3);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(1, 0);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(8.5, 10.5, -1);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(0, 0);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(10, 10, -3);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(0.5, 1);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(11, 10.5, -2);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(1, 0);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(12, 9.5, -4);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(1, 0.5);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	//cloud2
	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(13, 15, -5);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(1, 0);
	glutSolidSphere(1.25, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(16, 15.5, -1);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(0,0);
	glutSolidSphere(1.25, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(15, 17, 2);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(0,1);
	glutSolidSphere(1.25, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(14, 16, -2);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(1, 0);
	glutSolidSphere(1.25, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1, 1.25);
	glTranslatef(14.25, 14, -4);
	glColor4f(1, 1, 1, 0.9f);
	glTexCoord2f(0.5, 0);
	glutSolidSphere(1.25, 32, 32);
	glPopMatrix();

	////cloud3
	//glPushMatrix();
	//glScalef(1.5, 1, 1.25);
	//glTranslatef(22, 8, -3);
	//glColor4f(1, 1, 1, 0.9f);
	//glTexCoord2f(0, 0);
	//glutSolidSphere(1.75, 32, 32);
	//glPopMatrix();

	//glPushMatrix();
	//glScalef(1.5, 1, 1.25);
	//glTranslatef(19, 7, -1);
	//glColor4f(1, 1, 1, 0.9f);
	//glTexCoord2f(1, 0.5);
	//glutSolidSphere(1.75, 32, 32);
	//glPopMatrix();

	//glPushMatrix();
	//glScalef(1.5, 1, 1.25);
	//glTranslatef(20, 6, 0);
	//glColor4f(1, 1, 1, 0.9f);
	//glTexCoord2f(0, 1);
	//glutSolidSphere(1.75, 32, 32);
	//glPopMatrix();

	//glPushMatrix();
	//glScalef(1.5, 1, 1.25);
	//glTranslatef(20, 8, -2);
	//glColor4f(1, 1, 1, 0.9f);
	//glTexCoord2f(1, 0);
	//glutSolidSphere(1.75, 32, 32);
	//glPopMatrix();

	//glPushMatrix();
	//glScalef(1.5, 1, 1.25);
	//glTranslatef(18, 8, -5);
	//glColor4f(1, 1, 1, 0.9f);
	//glTexCoord2f(0,0);
	//glutSolidSphere(1.75, 32, 32);
	//glPopMatrix();
}

void ground() {
	
	glBegin(GL_POLYGON);
	//glColor3f(0.0f, 0.128f, 0.0f);
	//glTexCoord2f(0,1);
	glVertex3f(-100, -15, 90);
	//glTexCoord2f(1, 0);
	glVertex3f(0, -15, 90);
	//glTexCoord2f(0,0);
	glVertex3f(-30, -15, 90);
	//glTexCoord2f(0,1);
	glVertex3f(0, -15, 0);
	//glTexCoord2f(1, 0);
	glVertex3f(-50, -15, -90);
	//glTexCoord2f(1, 1);
	glVertex3f(-100, -15, -90);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.0f, 0.128f, 0.0f);
	//glTexCoord2f(1, 0);
	glVertex3f(0, -15, 0);
	//glTexCoord2f(0, 1);
	glVertex3f(-20, -15, 50);
	//glTexCoord2f(1, 1);
	glVertex3f(-30, -15, 50);
	//glTexCoord2f(0, 0);
	glVertex3f(100, -15, 90);
	//glTexCoord2f(1, 0);
	glVertex3f(100, -15, -90);
	//glTexCoord2f(0, 1);
	glVertex3f(-50, -15, -90);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.0f, 0.128f, 0.0f);
	//glTexCoord2f(0, 0);
	//glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 100);
	//glTexCoord2f(1, 0);
	glVertex3f(-30, 0, 50);
	//glTexCoord2f(1,1);
	glVertex3f(-30, 10, 50);
	//glTexCoord2f(0, 1);
	glVertex3f(0, 10, 100);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3f(0.0f, 0.128f, 0.0f);
	//glTexCoord2f(1, 0);
	glVertex3f(-100, 0, 100);
	//glTexCoord2f(1, 1);
	glVertex3f(100, 0, 100);
	//glTexCoord2f(0,0);
	glVertex3f(100, 0, -100);
	//glTexCoord2f(0, 1);
	glVertex3f(-100, 0, -100);
	glEnd();

	initTextureroad();
	glBegin(GL_POLYGON);
	glTexCoord2f(1,1);
	glVertex3f(-120, 0, 5);
	glTexCoord2f(1,1);
	glVertex3f(-120, -15, 5);
	glTexCoord2f(1,1);
	glVertex3f(100, -15, 5);
	glTexCoord2f(1, 0);
	glVertex3f(100, 0, 5);
	glEnd();

}

void building() {         

	// BACK
	glBegin(GL_QUADS);
	{
		GLfloat back[4][4] = {
				{-28, 20, 15},
				{-28, 5, 15},
				{-23, 5, 15},
				{-23, 20, 15}
		};

		glNormal3fv(findNormal(back[0], back[1], back[2]));
		glScalef(1.5, 1, 1.25);
		glTranslatef(-28.5, 0, -5);
		glTexCoord2f(0, 0);
		glVertex3fv(back[0]);
		glTexCoord2f(0, 1);
		glVertex3fv(back[1]);
		glTexCoord2f(1, 0);
		glVertex3fv(back[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(back[3]);
	}
	glEnd();

	// FRONT
	glBegin(GL_QUADS);
	{
		GLfloat front[4][4] = {
				{-30, 15, -15},
				{-30, 0, -15},
				{-25, 0, -15},
				{-25, 15, -15}
		};

		glNormal3fv(findNormal(front[0], front[1], front[2]));

		glTranslatef(-28.5, 0, -5);
		glScalef(1.5, 1, 1.25);
		glTexCoord2f(0, 1);
		glVertex3fv(front[0]);
		glTexCoord2f(0, 0);
		glVertex3fv(front[1]);
		glTexCoord2f(1, 0);
		glVertex3fv(front[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(front[3]);
	}
	glEnd();

	// LEFT
	glBegin(GL_QUADS);
	{
		GLfloat left[4][4] = {
				{-28, 20, 15},
				{-30, 15, -15},
				{-30, 0, -15},
				{-28, 5, 15}
		};

		glNormal3fv(findNormal(left[0], left[1], left[2]));
		glTranslatef(-28.5, 0, -5);
		glScalef(1.5, 1, 1.25);
		glTexCoord2f(0, 0);
		glVertex3fv(left[0]);
		glTexCoord2f(1, 0);
		glVertex3fv(left[1]);
		glTexCoord2f(0, 1);
		glVertex3fv(left[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(left[3]);
	}

	
	glEnd();


	//Right
	glBegin(GL_QUADS);
	{
		GLfloat right[4][4] = {
				{-25, 15, -15},
				{-25, 0, -15},
				{-23, 5, 15},
				{-23, 20, 15}
		};

		glNormal3fv(findNormal(right[0], right[1], right[2]));
		glTranslatef(-28.5, 0, -5);
		glScalef(1.5, 1, 1.25);
		glTexCoord2f(0, 1);
		glVertex3fv(right[0]);
		glTexCoord2f(0, 0);
		glVertex3fv(right[1]);
		glTexCoord2f(1, 0);
		glVertex3fv(right[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(right[3]);
	}
	
	glEnd();


	//Top
	glBegin(GL_QUADS);
	{
		GLfloat top[4][4] = {
				{-25, 15, -15},
				{-23, 20, 15},
				{-28, 20, 15},
				{-30, 15, -15}
		};

		//glNormal3fv(findNormal(top[0], top[1], top[2]));

		glScalef(1.5, 1, 1.25);
		glTranslatef(-28.5, 0, -5);
		glColor3f(1.0, 1.0, 0.0);
		glTexCoord2f(1, 1);
		glVertex3fv(top[0]);
		glTexCoord2f(1, 0);
		glVertex3fv(top[1]);
		glTexCoord2f(1,1);
		glVertex3fv(top[2]);
		glTexCoord2f(1, 0);
		glVertex3fv(top[3]);
	}
	
	glEnd();

	//Bottom
	glBegin(GL_QUADS);
	{
		GLfloat bottom[4][4] = {
				{-28, 5, 15},
				{-30, 0, -15},
				{-25, 0, -15},
				{-23, 5, 15}
		};

		glNormal3fv(findNormal(bottom[0], bottom[1], bottom[2]));

		glScalef(1.5, 1, 1.25);
		glTranslatef(-28.5, 0, -5);
		glTexCoord2f(0, 0);
		glVertex3fv(bottom[0]);
		glTexCoord2f(1, 0);
		glVertex3fv(bottom[1]);
		glTexCoord2f(1, 1);
		glVertex3fv(bottom[2]);
		glTexCoord2f(0, 1);
		glVertex3fv(bottom[3]);
	}
	
	
	glEnd();

	
}

void building2() {

	// BACK
	glBegin(GL_QUADS);
	{
		GLfloat back[4][4] = {
				{-20, 15, 15},
				{-20, 5, 15},
				{-15, 5, 15},
				{-15, 15, 15}
		};

		glNormal3fv(findNormal(back[0], back[1], back[2]));
		glScalef(1.5, 1, 1.25);
		glTranslatef(-28.5, 0, -5);
		glTexCoord2f(0, 0);
		glVertex3fv(back[0]);
		glTexCoord2f(0, 1);
		glVertex3fv(back[1]);
		glTexCoord2f(1, 0);
		glVertex3fv(back[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(back[3]);
	}
	glEnd();

	// FRONT
	glBegin(GL_QUADS);
	{
		GLfloat front[4][4] = {
				{-22, 10, -15},
				{-22, 0, -15},
				{-17, 0, -15},
				{-17, 10, -15}
		};

		glNormal3fv(findNormal(front[0], front[1], front[2]));

		glTranslatef(-28.5, 0, -5);
		glScalef(1.5, 1, 1.25);
		glTexCoord2f(0, 1);
		glVertex3fv(front[0]);
		glTexCoord2f(0, 0);
		glVertex3fv(front[1]);
		glTexCoord2f(1, 0);
		glVertex3fv(front[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(front[3]);
	}
	glEnd();

	// LEFT
	glBegin(GL_QUADS);
	{
		GLfloat left[4][4] = {
				{-20, 15, 15},
				{-22, 10, -15},
				{-22, 0, -15},
				{-20, 5, 15}
		};

		glNormal3fv(findNormal(left[0], left[1], left[2]));
		glTranslatef(-28.5, 0, -5);
		glScalef(1.5, 1, 1.25);
		glTexCoord2f(0, 0);
		glVertex3fv(left[0]);
		glTexCoord2f(1, 0);
		glVertex3fv(left[1]);
		glTexCoord2f(0, 1);
		glVertex3fv(left[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(left[3]);
	}


	glEnd();


	//Right
	glBegin(GL_QUADS);
	{
		GLfloat right[4][4] = {
				{-17, 10, -15},
				{-17, 0, -15},
				{-15, 5, 15},
				{-15, 15, 15}
		};

		glNormal3fv(findNormal(right[0], right[1], right[2]));
		glTranslatef(-28.5, 0, -5);
		glScalef(1.5, 1, 1.25);
		glTexCoord2f(0, 1);
		glVertex3fv(right[0]);
		glTexCoord2f(0, 0);
		glVertex3fv(right[1]);
		glTexCoord2f(1, 0);
		glVertex3fv(right[2]);
		glTexCoord2f(1, 1);
		glVertex3fv(right[3]);
	}

	glEnd();


	//Top
	glBegin(GL_QUADS);
	{
		GLfloat top[4][4] = {
				{-17, 10, -15},
				{-15, 15, 15},
				{-20, 15, 15},
				{-22, 10, -15}
		};

		//glNormal3fv(findNormal(top[0], top[1], top[2]));

		glScalef(1.5, 1, 1.25);
		glTranslatef(-28.5, 0, -5);
		glColor3f(1.0, 1.0, 0.0);
		glTexCoord2f(1, 1);
		glVertex3fv(top[0]);
		glTexCoord2f(1, 0);
		glVertex3fv(top[1]);
		glTexCoord2f(1, 1);
		glVertex3fv(top[2]);
		glTexCoord2f(1, 0);
		glVertex3fv(top[3]);
	}

	glEnd();

	//Bottom
	glBegin(GL_QUADS);
	{
		GLfloat bottom[4][4] = {
				{-20, 5, 15},
				{-22, 0, -15},
				{-17, 0, -15},
				{-15, 5, 15}
		};

		glNormal3fv(findNormal(bottom[0], bottom[1], bottom[2]));

		glScalef(1.5, 1, 1.25);
		glTranslatef(-28.5, 0, -5);
		glTexCoord2f(0, 0);
		glVertex3fv(bottom[0]);
		glTexCoord2f(1, 0);
		glVertex3fv(bottom[1]);
		glTexCoord2f(1, 1);
		glVertex3fv(bottom[2]);
		glTexCoord2f(0, 1);
		glVertex3fv(bottom[3]);
	}


	glEnd();


}


void tracklight() {
	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(-28.5, 0, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(-18.5, 0, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(-8.5, 0, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(2.5, 0, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(12.5, 0, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(22.5, 0, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(32.5, 0, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	//lower
	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(-33.5, -15, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(-23.5, -15, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(-13.5, -15, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(-3.5, -15, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(7.5, -15, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(17.5, -15, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1.25);
	glTranslatef(27.5, -15, -5);
	glColor4f(1, 1, 0, 0.9f);
	glutSolidCube(1.25);
	glPopMatrix();
}


void* fonts[] = {

	GLUT_BITMAP_9_BY_15,

	GLUT_BITMAP_TIMES_ROMAN_10,

	GLUT_BITMAP_TIMES_ROMAN_24,

	GLUT_BITMAP_HELVETICA_18,

	GLUT_BITMAP_HELVETICA_12

};

void front() {

	glColor3f(1.0, 0.0, 0.0);

	char text[] = "GRAPHICAL REPRESENTATION OF FLIGHT TAKEOFF";

	output(-16, 10, text, fonts[2]);

	glColor3f(1.0, 0.0, 0.0);

	char text1[] = "SUBMITTED BY";

	output(-6, 8, text1, fonts[3]);

	//glColor3f(0.8,0.1,0.2); red 

	glColor3f(1.0, 1.0, 1.0);

	char text2[] = "S15180 - P. S. THISSERA";

	output(-8, 6, text2, fonts[3]);

	glColor3f(1.0f, 1.0f, 1.0f);

	char text3[] = "CS 308 - COMPUTER GRAPHICS";

	output(-10, 4, text3, fonts[3]);

	glColor3f(1.0f, 1.0f, 1.0f);

	char text4[] = "DEPARTMENT OF STATISTICS AND COMPUTER SCIENCE";

	output(-16, 2, text4, fonts[3]);

	char text5[] = "FACULTY OF SCIENCE";

	output(-7, 0, text5, fonts[3]);

	char text6[] = "UNIVERSITY OF PERADENIYA";

	output(-9, -2, text6, fonts[3]);

	glColor3f(1.0,1.0,1.0); 

	char text7[] = "[ FOLLOW THE KEY GUIDE TO CONTINUE ]";

	output(-7, -4, text7, fonts[4]);

	glColor3f(1.0,1.0,1.0);

	char text8[] = " PRESS ANY KEY TO CONTINUE TO THE TAKEOFF";

	output(-8, -6, text8, fonts[4]);

	glColor3f(1.0,1.0,1.0);

	char text9[] = "PRES 'b' TO START FLIGHT TAKE OFF";

	output(-8, -8, text9, fonts[4]);

}

void plain() {
	//windows
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(x + 1.2f, y + 0.5f, z + 0.2f);
	glVertex3f(x + 1.9f, y + 0.5f, z + 0.2f);
	glVertex3f(x + 1.9f, y + (-0.5f), z + 0.2f);
	glVertex3f(x + 1.2f, y + (-0.5f), z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + (-0.2f), y + 0.5f, z + 0.2f);
	glVertex3f(x + 0.5f, y + 0.5f, z + 0.2f);
	glVertex3f(x + 0.5f, y + (-0.5f), z + 0.2f);
	glVertex3f(x + (-0.2f), y + (-0.5f), z + 0.2f);
	glEnd();
	//glTranslatef(9.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex3f(x + (-1.6f), y + 0.5f, z + 0.2f);
	glVertex3f(x + (-0.9f), y + 0.5f, z + 0.2f);
	glVertex3f(x + (-0.9f), y + (-0.5f), z + 0.2f);
	glVertex3f(x + (-1.6f), y + (-0.5f), z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + (-3.0f), y + 0.5f, z + 0.2f);
	glVertex3f(x + (-2.3f), y + 0.5f, z + 0.2f);
	glVertex3f(x + (-2.3f), y + (-0.5f), z + 0.2f);
	glVertex3f(x + (-3.0f), y + (-0.5f), z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + (-4.4f), y + 0.5f, z + 0.2f);
	glVertex3f(x + (-3.7f), y + 0.5f, z + 0.2f);
	glVertex3f(x + (-3.7f), y + (-0.5f), z + 0.2f);
	glVertex3f(x + (-4.4f), y + (-0.5f), z + 0.2f);
	glEnd();

	glPopMatrix();

	//windscreen
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(x + 6.8f, y + 2.0f, z + 0.2f);
	glVertex3f(x + 7.3f, y + 1.0f, z + 0.2f);
	glVertex3f(x + 7.5f, y + 0.1f, z + 0.2f);
	glVertex3f(x + 6.4f, y + 1.2f, z + 0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + 5.6f, y + 0.6f, z + 0.2f);
	glVertex3f(x + 6.3f, y + 1.1f, z + 0.2f);
	glVertex3f(x + 7.4f, y, z + 0.2f);
	glVertex3f(x + 6.2f, y + (-0.8f), z + 0.2f);
	glEnd();

	glPopMatrix();

	//Door
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glVertex3f(x + 5.1f, y + (-2.6f), z + 0.2f);
	glVertex3f(x + 3.5f, y + (-2.6f), z + 0.2f);
	glVertex3f(x + 3.5f, y + (-2.6f), z + 0.2f);
	glVertex3f(x + 3.5f, y + (-0.2f), z + 0.2f);
	glVertex3f(x + 3.5f, y + (-0.2f), z + 0.2f);
	glVertex3f(x + 5.1f, y + (-0.2f), z + 0.2f);
	glVertex3f(x + 5.1f, y + (-0.2f), z + 0.2f);
	glVertex3f(x + 5.1f, y + (-2.6f), z + 0.2f);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tire);
	wheel();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, plainBody);
	//Body
	glPushMatrix();
	glRotatef(rotX, 1.0f, 1.0f, 1.0f);
	glColor3f(0.5, 1.0, 1.0);

	initTexturePlain();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(x + 0.0f, y + 2.5f, 0.2f);
	glTexCoord2f(0, 1);
	glVertex3f(x + 4.0f, y + 2.5f, 0.2f);
	glTexCoord2f(1, 0.0);
	glVertex3f(x + 5.6f, y + 2.4f, 0.2f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(x + 6.8f, y + 2.0f, 0.2f);
	glVertex3f(x + 7.30f, y + 1.0f, 0.2f);

	glVertex3f(x + 9.0f, y + 0.5f, 0.2f);
	glVertex3f(x + 10.0f, y + 0.0f, 0.2f);
	glVertex3f(x + 10.4f, y + (-0.3f), 0.2f);
	glVertex3f(x + 10.5f, y + (-0.7f), 0.2f);
	glVertex3f(x + 9.8f, y + (-1.5f), 0.2f);
	glVertex3f(x + 8.5f, y + (-2.0f), 0.2f);
	glVertex3f(x + 7.2f, y + (-2.3f), 0.2f);

	glVertex3f(x + 5.6f, y + (-2.6f), 0.2f);
	glVertex3f(x + 4.0f, y + (-2.6f), 0.2f);
	glVertex3f(x + 2.0f, y + (-2.5f), 0.2f);

	glVertex3f(x + 0.0f, y + (-2.5f), 0.2f);
	glVertex3f(x + (-1.6f), y + (-2.3f), 0.2f);
	glVertex3f(x + (-3.2f), y + (-2.1f), 0.2f);
	glVertex3f(x + (-5.5f), y + (-1.9f), 0.2f);
	glVertex3f(x + (-7.4f), y + (-1.7f), 0.2f);

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

	//wheel();

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

}

void display1() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat radius = 1.0f;

	//gluLookAt(0.0f+camX, 0.0f+camY, 0.0f+camZ,0,0,0,1.0,0,0);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cloudtx);
	cloud();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass);
	background();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, road);
	ground();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	building();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	building2();
	glDisable(GL_TEXTURE_2D);

	

	tracklight();

	plain();

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


	if (x >= -10.0f) {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		moveX = 0.010f;
		moveY = 0.005f;
		moveZ = 0.005f;
		x += moveX;
		y += moveY;
		z += moveZ;
		glutPostRedisplay();
		glutTimerFunc(60, Timer, 5);
	}

	glutPostRedisplay();
	glutTimerFunc(60, Timer, 1);
}

void display() {

	if (count == 0) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		front();
		glutSwapBuffers();
	}
	else {
		display1();
	}

}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		moveZ += 1;

	if (key == GLUT_KEY_DOWN)
		moveZ -= 1;

	if (key == GLUT_KEY_LEFT)
		rotY += 5.0;

	if (key == GLUT_KEY_RIGHT)
		rotY -= 5.0;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (count == 0) {
		count = 1;
		glutPostRedisplay();
	}
	else
	{
			display1();
			if (key == 'b')
				glutTimerFunc(60, Timer, 15);
		
	}
		
	if (key == 'w')
		camY += 0.5;
	if (key == 's')
		camY -= 0.5;

	if (key == 'c')
		glPolygonMode(GL_BACK, GL_LINE);
	// glPolygonMode(GL_FRONT, GL_FILL);
	if (key == 'C')
		glPolygonMode(GL_BACK, GL_FILL);

	if (key == 'k')
		glDisable(GL_LIGHT0);
	if (key == 'K')
		glEnable(GL_LIGHT0);

	glutPostRedisplay();

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

	//gluPerspective(120.00, aspect_ratio, -120, 10);
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
	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	init();
	glutMainLoop();

	return 0;
}