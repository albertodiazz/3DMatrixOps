/*#include <GL/glext.h>*/
#define GL_GLEXT_PROTOTYPES
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <cstdlib>
/*#include <stdio.h>*/
/*#include <algorithm>*/

#define MIN(a,b) ( ((a) < (b)) ? (a) : (b) )
#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )
#define NORM(x, xmin, xmax) ( 2.0f * ( (x - xmin) / (xmax - xmin) ) -1.0f )

struct vec2d{
	float x, y;
};

GLuint vbo, vbo2;

void drawCuadriculaX(float spacing, int w, vec2d *v){
	for (int i = 0; i < w; i ++){
		if (i%2 == 0){
			v[i].x = NORM(i * spacing, 0.0f, w); 
			v[i+1].x = NORM(i * spacing, 0.0f, w);
		}
		if (i%2 == 1){
			v[i].y =  1; 
		}else{
			v[i].y =  -1; 
		}
	};
};

void drawCuadriculaY(float spacing, int h, vec2d *v){
	for (int i = 0; i < h; i ++){
		if (i%2 == 0){
			v[i].y = NORM(i * spacing, 0.0f, h); 
			v[i+1].y = NORM(i * spacing, 0.0f, h);
		}
		if (i%2 == 1){
			v[i].x =  1; 
		}else{
			v[i].x =  -1; 
		}
	};
};

void display(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	const int w = glutGet(GLUT_INIT_WINDOW_WIDTH);
	const int h = glutGet(GLUT_INIT_WINDOW_HEIGHT);

	vec2d lineasX[w], lineasY[h]; 
	float spacing = 10.0f;

	drawCuadriculaX(spacing, w, lineasX);
	drawCuadriculaY(spacing, h, lineasY);


	/*__asm__("int3");*/

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f,0.0f,0.0f);
	for(const auto& vertex : lineasX){
		glVertex2d(vertex.x, vertex.y);
	}
	for(const auto& vertex : lineasY){
		glVertex2d(vertex.x, vertex.y);
	}
	glEnd();

	glFlush();
};

int main(int arg, char **argv){
	// Inicializacion de mi ventana de trabajo
	glutInit(&arg, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("alffy");
	glutDisplayFunc(display);
	glutMainLoop();
	return EXIT_SUCCESS;

};
