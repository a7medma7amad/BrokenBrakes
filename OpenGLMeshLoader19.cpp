#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex;
GLuint tex2;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 1;
GLdouble zFar = 10;
GLdouble carTransX = 0;
GLdouble carTransZ = -225;
bool frozen = false;
float frozenTime=0;
float currentTime = 0;
float timout = 27000;
int level =1;
int score = 0;
bool level1Over = false;
bool changeColor = false;
//code from assign 2
//-----------------------------------

class Vector3f {

public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;
					
	
	Camera(float eyeX = 0.000000, float eyeY = 6.224399, float eyeZ = -241.346893, float centerX = 0.000000, float centerY = 6.244786, float centerZ = -240.347107, float upX = -0.000000, float upY = 0.999792, float upZ = -0.020388) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;

	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
	void look(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;
void drawTree() {
	glPushMatrix();
	glColor3d(0, 1, 0);
	glTranslated(0, 0, 0);
	glRotated(-90, 1.0, 0, 0);
	glutSolidCone(0.4, 0.3, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0, 1, 0);
	glTranslated(0, 0.2, 0);
	glRotated(-90, 1.0, 0, 0);
	glutSolidCone(0.3, 0.3, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0, 1, 0);
	glTranslated(0, 0.4, 0);
	glRotated(-90, 1.0, 0, 0);
	glutSolidCone(0.2, 0.3, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.8, 0, 0.4);
	glTranslated(0, 0.35, 0.17);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.8, 0.9, 0.1);
	glTranslated(0.15, 0.35, 0);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(1, 0.6, 0);
	glTranslated(0, 0.1, 0.3);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(1, 0.6, 1);
	glTranslated(0.3, 0.1, 0);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.6, 0.2, 0.9);
	glTranslated(0, 0.55, 0.1);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 1, 0);

	glPushMatrix();
	glColor3d(0.8, 0, 0.4);
	glTranslated(0, 0.35, 0.17);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.8, 0.9, 0.1);
	glTranslated(0.15, 0.35, 0);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(1, 0.6, 0);
	glTranslated(0, 0.1, 0.3);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(1, 0.6, 1);
	glTranslated(0.3, 0.1, 0);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.6, 0.2, 0.9);
	glTranslated(0, 0.55, 0.1);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();

	glPopMatrix();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.5;
	
	switch (key) {
		//camera views

		//top
	case't':

		camera.look(carTransX, 6.224399,carTransZ-16,  carTransX,  6.244786, carTransZ - 15, -0.000000, 0.999792, -0.020388);
		break;
		//front
	case'y':
		camera.look(carTransX,2.647265, carTransZ+3, carTransX,2.667651,  carTransZ+4,  -0.000000,  0.999792, -0.020386);
		break;

		//side
	case'u':
		camera.look(1.480090, 0.329268, 0.487120, 0.484874, 0.231999, 0.477926, -0.097367, 0.995189, 0.010927);
		break;

	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;

	case 'i':
		if (carTransZ < 225) {
			carTransZ += 0.52;
			camera.moveZ(d);
		}
		printf("transX: %f , transZ: %f \n", carTransX, carTransZ);
		break;
	case 'j':
		if (carTransX <= 14) {
			carTransX += 0.5;
			camera.moveX(d);
		}printf("transX: %f , transZ: %f \n", carTransX, carTransZ);
		break;
	case 'k':
		if (carTransZ > -225) {
			carTransZ -= 0.52;
			camera.moveZ(-d);
		}
		printf("transX: %f , transY: %f \n", carTransX, carTransZ);
		break;
	case 'l':
		if (carTransX >= -14) {
			carTransX -= 0.5;
			camera.moveX(-d);
		}
		printf("transX: %f , transY: %f \n", carTransX, carTransZ);
		break;


	
	}
	printf("eyeX=%f, eyeY=%f, eyeZ=%f, centerX=%f, centerY=%f, centerZ=%f, upX=%f, upY=%f, upZ=%f \n", camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);
	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}
void time(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{
	int timeInc = 1;
	currentTime += timeInc;
	//level @
	if (level == 1) {
		if (((timout - (currentTime * 20)) / 1000) <= 0) {
			if (carTransZ >= 220) {
				
				camera.look(0.000000, 6.224399, -241.346893, 0.000000, 6.244786, -240.347107, -0.000000, 0.999792, -0.020388);
				carTransZ = -225;
				carTransX = 0;
				currentTime = 0;
				level = 2;
			}
			else {
				/*camera.look(0.000000, 6.224399, -241.346893, 0.000000, 6.244786, -240.347107, -0.000000, 0.999792, -0.020388);
				carTransZ = -225;
				carTransX = 0;
				currentTime = 0;*/
				changeColor = true;
			}
		}

		if (carTransZ >= 220 ) {
			camera.look(0.000000, 6.224399, -241.346893, 0.000000, 6.244786, -240.347107, -0.000000, 0.999792, -0.020388);
			carTransZ = -225;
			carTransX = 0;
			currentTime = 0;
			level = 2;
		}
		
			if (frozen) {
			frozenTime += timeInc;
			if (frozenTime >= timeInc * 15) {
				frozen = false;
				frozenTime = 0;
			}
		}

		if (carTransX >= -2) {
			for (int i = 0;i < 350;) {
				if ((carTransZ + 0.1 > -175 + i) && ((carTransZ - 10 < -175 + i))) {
					printf("************************collision********************************** \n");
					carTransZ = carTransZ - 20;
					camera.moveZ(-20);
					frozen = true;
				}
				i += 80;
			}
		}
		if (carTransX <= 2) {
			for (int i = 0;i < 350;) {
				if ((carTransZ + 0.1 > -135 + i) && ((carTransZ - 10 < -135 + i))) {
					printf("************************collision********************************** \n");
					carTransZ = carTransZ - 20;
					camera.moveZ(-20);
					frozen = true;
				}
				i += 80;
			}
		}
		if (!frozen && !changeColor) {
			if (carTransZ < 225) {
				carTransZ += 0.4;
				camera.moveZ(0.385);
			}
		}
	
	}
	else {
		if (carTransX >= -2) {
			for (int i = 0;i < 350;) {
				if ((carTransZ + 0.1 > -175 + i) && ((carTransZ - 10 < -175 + i))) {
					printf("************************collision********************************** \n");
					/*camera.look(0.000000, 6.224399, -241.346893, 0.000000, 6.244786, -240.347107, -0.000000, 0.999792, -0.020388);
					carTransZ = -225;
					carTransX = 0;
					currentTime = 0;*/
					changeColor = true;
				}
				i += 80;
			}
		}
		if (carTransX <= 2) {
			for (int i = 0;i < 350;) {
				if ((carTransZ + 0.1 > -135 + i) && ((carTransZ - 10 < -135 + i))) {
					printf("************************collision********************************** \n");
					/*camera.look(0.000000, 6.224399, -241.346893, 0.000000, 6.244786, -240.347107, -0.000000, 0.999792, -0.020388);
					carTransZ = -225;
					carTransX = 0;
					currentTime = 0;*/
					changeColor = true;
				}
				i += 80;
			}
		}
		if (carTransZ < 225 && !changeColor) {
			carTransZ += 0.4;
			camera.moveZ(0.385);
			score += 1;
		}
	}
	//============


	glutPostRedisplay();
	glutTimerFunc(timeInc, time, 0);
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
/*void setupLights2() {


	GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat l0Diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat l0Spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat l0Ambient[] = { 0.1f, 0.0f, 0.0f, 1.0f };
	GLfloat l0Position[] = { 10.0f, 0.0f, 0.0f, s };
	GLfloat l0Direction[] = { -1.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);

	GLfloat l1Diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat l1Ambient[] = { 0.0f, 0.1f, 0.0f, 1.0f };
	GLfloat l1Position[] = { 0.0f, 10.0f, 0.0f, s };
	GLfloat l1Direction[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1Ambient);
	glLightfv(GL_LIGHT1, GL_POSITION, l1Position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1Direction);

	GLfloat l2Diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat l2Ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };
	GLfloat l2Position[] = { 0.0f, 0.0f, 10.0f, s };
	GLfloat l2Direction[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2Diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2Ambient);
	glLightfv(GL_LIGHT2, GL_POSITION, l2Position);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2Direction);


}*/
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
void print(int x, int y,int z, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//---------------------------------
class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_car;
Model_3DS model_fence;

// Textures
GLTexture tex_ground;
GLTexture tex_snowGround;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	if(level==1)
	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture
	
	if(level==2)
	glBindTexture(GL_TEXTURE_2D, tex_snowGround.texture[0]);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-300, 0, -300);
	glTexCoord2f(5, 0);
	glVertex3f(300, 0, -300);
	glTexCoord2f(5, 5);
	glVertex3f(300, 0, 300);
	glTexCoord2f(0, 5);
	glVertex3f(-300, 0, 300);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	setupCamera();
	//setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (level == 1) {

		if (changeColor) {
			GLfloat lightIntensity[] = { 10.7, 5.7, 0, 0.0f };
			GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		else {
			GLfloat lightIntensity[] = { 10.7, 10.7, 10.7, 0.0f };
			GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		//GLfloat lightIntensity[] = { 10.7, 10.7, 10.7, 1.0f };
	}
	else {

		GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

		GLfloat l0Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat l0Spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat l0Ambient[] = { 10.0f, 10.0f, 10.0f, 1.0f };
		GLfloat l0Ambient1[] = { 0.0f, 1.0f, 10.0f, 1.0f };
		GLfloat l0Position[] = { carTransX, 0.0f, carTransZ,1 };
		GLfloat l0Direction[] = { carTransX,0.0, carTransZ,1 };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
		if(!changeColor)
			glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
		else
			glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient1);

		glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 85.0);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);
	}
	// Draw Ground
	RenderGround();

	//------------------
	if (level == 1) {
		glPushMatrix();
		char* p1s[20];
		glScaled(1, 1, 1);
		glTranslated(carTransX, 0, carTransZ + 9);
		if (((timout - (currentTime * 20)) / 1000) > 0)
			sprintf((char*)p1s, "Time Left: %f", (timout - (currentTime * 20)) / 1000);
		else {
			sprintf((char*)p1s, "Time Left: 0");
		}
		print(0, 20, 0, (char*)p1s);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glColor3d(1, 1, 1);
		char* p1s[20];
		glScaled(1, 1, 1);
		glTranslated(carTransX, 0, carTransZ );
		
		sprintf((char*)p1s, "score: %d", score);
		print(0,4, 0, (char*)p1s);
		glPopMatrix();
	}
	//-------
	
	//Draw Tree Model
	if (level == 1) {
		int j = 0;
		while (j < 350) {
			glPushMatrix();
			glTranslatef(0, 1, -130 + j);
			glRotatef(90, 0, 0, 1);
			glScalef(1.7, 1, 1);
			model_tree.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
			j += 80;
		}
		j = 0;
		while (j < 350) {
			glPushMatrix();
			glTranslatef(0, 1, -170 + j);
			glRotatef(180, 0, 0, 1);
			glRotatef(90, 0, 0, 1);
			glScalef(1.7, 1, 1);
			model_tree.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
			j += 80;
		}
	}
	else {
		int j = 0;
		while (j < 350) {
			glPushMatrix();
			glTranslatef(0, 1, -130 + j);
			glRotatef(90, 0, 0, 1);
			glScalef(30, 28, 7);
			drawTree();
			glEnable(GL_LIGHTING);
			glPopMatrix();
			j += 80;
		}
		j = 0;
		while (j < 350) {
			glPushMatrix();
			glTranslatef(0, 1, -170 + j);
			glRotatef(180, 0, 0, 1);
			glRotatef(90, 0, 0, 1);
			glScalef(30, 28, 7);
			drawTree();
			glEnable(GL_LIGHTING);
			glPopMatrix();
			j += 80;
		}
	}
	// Draw house Model
	/*glPushMatrix();
	glRotatef(90.f, 1, 0, 0);
	model_house.Draw();
	glPopMatrix();*/

	//car model
	glPushMatrix();
	glTranslated(carTransX, 1.8, carTransZ );
	glScalef(0.2, 0.2, 0.2);
	model_car.Draw();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	
	//fence model
	int i = 250;
	while(i>-250)
	{
		glPushMatrix();
		glTranslated(-16.5, 1.8, 0+i);
		glRotated(90, 0, 1, 0);
		glScalef(0.02, 0.03, 0.02);
		model_fence.Draw();
		glEnable(GL_LIGHTING);
		glPopMatrix();
		i -= 5;
	}
	

	//-----------
	//fence model
	i = 250;
	while (i > -250)
	{
		glPushMatrix();
		glTranslated(16.5, 1.8, 0 + i);
		glRotated(180, 0, 1, 0);
		glRotated(90, 0, 1, 0);
		glScalef(0.02, 0.03, 0.02);
		model_fence.Draw();
		glEnable(GL_LIGHTING);
		glPopMatrix();
		i -= 5;
	}
	//-----------

	//sky box
	/*glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	//glTranslated(50, 0, 0);
	//glRotated(90, 1, 0, 1);
	glScaled(50,60,500);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 1, 200, 200);
	gluDeleteQuadric(qobj);
	glEnable(GL_LIGHTING);

	glPopMatrix();*/
	
	//---------

	//sky box
	glPushMatrix();

	GLUquadricObj* qobj1;
	qobj1 = gluNewQuadric();
	glTranslated(0, 0, carTransZ);
	glRotated(90, 1, 0, 1);
	//glScaled(50, 60, 1);
	if(level==1)
		glBindTexture(GL_TEXTURE_2D, tex);
	else
	glBindTexture(GL_TEXTURE_2D, tex2);
	gluQuadricTexture(qobj1, true);
	gluQuadricNormals(qobj1, GL_SMOOTH);
	gluSphere(qobj1, 65, 100, 100);
	gluDeleteQuadric(qobj1);
	glEnable(GL_LIGHTING);

	glPopMatrix();

	//---------
	//------------------------
	float thickness = 0.02;
	glPushMatrix();
	glColor3d(1.0, 1.0, 1.0);
	glTranslated(0.5, 0.5 * thickness, 220);
	glScaled(40.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();

	//------------------
	//-------

	glutSwapBuffers();
	glutPostRedisplay();
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();

}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_car.Load("Models/car/GTR.3ds");
	model_fence.Load("Models/fence/fence.3ds");

	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
	tex_snowGround.Load("Textures/snowGround.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&tex2, "Textures/nightSky.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(0, time, 0);
	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}