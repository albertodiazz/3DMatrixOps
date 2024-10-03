#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdio>
#include <math.h>

struct Camara{
	float view[16] = {}; 
};
struct mat4x4{
	float data[4][4];
};

void display(){
	// Aqui dibujamos
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glutWireCube(1.0f);
	/*glutWireTeapot(0.5f);*/
	glFlush();
};

Camara CustomMatrix(float w, float h){
	Camara c;
	float aspectRatio = (float) w / (float) h;
	float angle = 90.0f;
	float convertToRadians = angle * (3.14159f / 180.0f);
	float znear = 0.1f; 
	float zfar = 1.0f; 

	c.view[0] = aspectRatio * (1.0f / tan(convertToRadians / 2.0f));
	c.view[5] = (1.0f / tan(convertToRadians / 2.0f));
	c.view[10] = zfar / (zfar - znear);
	c.view[11] = -(zfar * znear)/ (zfar - znear);
	c.view[15] = 1.0f; 

	return c;
}; 

mat4x4 Homogenisacion(){
	mat4x4 v;
	return v;
};

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	/*glutInitWindowSize(, 800);*/
	glutCreateWindow("alffy");

	/*float w = glutGet(GLUT_WINDOW_WIDTH);	*/
	/*float h = glutGet(GLUT_WINDOW_HEIGHT);	*/
	float w = 400; 
	float h = 400;

	Camara c = CustomMatrix(h, w);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	glLoadMatrixf(c.view);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
										
	printf(">>>>>>>>> Deberia funcionar <<<<<<<<<<<<<<\n");
	printf("Width:%i, Height: %i \n",
			glutGet(GLUT_WINDOW_WIDTH),
			glutGet(GLUT_WINDOW_HEIGHT));


	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
