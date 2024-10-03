/*#include <GL/glext.h>*/
#define GL_GLEXT_PROTOTYPES
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>

#define MIN(a,b) ( ((a) < (b)) ? (a) : (b) )
#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )

struct vec2d{
	float x, y;
};

GLuint vbo, vbo2;

void display(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glPointSize(10.0f);
	glLineWidth(1.0f);

	vec2d vertices[3] = {
		// Triangulo
		{-0.3f, -0.3f},
		{0.0f, 0.5f},
		{0.3f,-0.3f}
	};

	/*float x_min = std::min(vertices[0].x, vertices[1].x, vertices[2].x);*/

	//Esto es pura inicializacion del buffer para dibujar sobre el GPU
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY); // Habilitar el uso de un array de vértices
	glVertexPointer(2, GL_FLOAT, sizeof(vec2d), 0); // Especificar el formato de los datos de vértices
																																					 //
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawArrays(GL_POINTS, 0, sizeof(vertices) / sizeof(vertices[0])); 

	glDisableClientState(GL_VERTEX_ARRAY);

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
