/*#include <GL/glext.h>*/
#include <csignal>
#include <cstdio>
#include <vector>
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
#define CX(x1, x2) ( (x1 + x2) / 2 )
#define CY(y1, y2) ( (y1 + y2) / 2 )

struct vec2d{
	float x, y;
};

GLuint vbo, vbo2;

void drawCuadriculaX(float spacing, int w, std::vector<vec2d> &v){
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

void drawCuadriculaY(float spacing, int h, std::vector<vec2d> &v){
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

	int w = glutGet(GLUT_INIT_WINDOW_WIDTH);
	int h = glutGet(GLUT_INIT_WINDOW_HEIGHT);

	/*TODO:BUG*/
	/*	Ten cuaidado con este numero ya que causa un segmentation fault ciertos valores*/
	/*		aun no se por que pasa eso.*/
	float spacing = 15.0f;
	/*Si te quieres evitar de problemas mejor pon el el wMax y el hMax de forma manual
	 * Recuerda que esto solo lo hago para que mi vec2d sea del tamanno exacto de la venta
	 * y no me lo genera de mayor tamanno*/
	const int wMax = (w/spacing+2);
	const int hMax = (h/spacing+2);
	std::vector<vec2d> lineasX(wMax);
	std::vector<vec2d> lineasY(hMax);

	drawCuadriculaX(spacing, w, lineasX);
	drawCuadriculaY(spacing, h, lineasY);

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

	glPointSize(15.0f);
	glBegin(GL_POINTS);
	int getX = (sizeof(lineasX) / sizeof(lineasX[0])) / static_cast<int>(spacing);
	std::vector<vec2d> posCenter(getX);
	for (int i = 0; i < getX/2; i ++){
		posCenter[i].x = CX(lineasX[i].x, lineasX[i+2].x);
		posCenter[i].y = CX(lineasY[i].x, lineasY[i+2].x);
	};
	for(auto &pos : posCenter){
		glVertex2d(pos.x, pos.y);
	}
	glEnd();
	glFlush();
	/*__asm__("int3");*/
};

void exitProgram(int signum){
	glutDestroyWindow(glutGetWindow());
	printf("<<<<<<< Saliendo del programa >>>>>>>");
	exit(signum);
};

int main(int arg, char **argv){
	// Inicializacion de mi ventana de trabajo
	signal(SIGINT, exitProgram);
	glutInit(&arg, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("alffy");
	glutDisplayFunc(display);
	glutMainLoop();

	return EXIT_SUCCESS;

};
