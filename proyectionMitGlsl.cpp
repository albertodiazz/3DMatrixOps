#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>  

float angle = 90.0f;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffer

    glPushMatrix();

    // Mueve el cubo en el eje Z para que esté en una posición visible
    glTranslatef(0.0f, 0.0f, -1.0f);
		/*glRotatef(angle,1.0f,0.2f,0.2f);*/

    // Escala el cubo
    /*glScalef(-1.0f, 8.0f, 1.0f);  // Scale to -1 on x-axis, 8 on y-axis, 1 on z-axis*/

    // Dibuja un cubo sólido
    glutWireCube(1.0);  // Crea un cubo de tamaño 1.0

    glPopMatrix();

    glFlush();  // Render now
}

void update(int value){
	angle += 2.0f;
	if (angle > 360){
		angle -= 360;
	}
	glutPostRedisplay();  // Marca la ventana actual para que se vuelva a dibujar
	glutTimerFunc(16, update, 0);  // Llama a esta función de nuevo después de 16 ms (aproximadamente 60 FPS)
}

int main(int argc, char** argv) {
	float width = 320;
	float height = 320;

	float fov = 90.0f;
	float fovRadians = fov * (3.14159f / 180.0f );
	float aspect = width / height;
	float zfar = 1000.0f;
	float znear = 1.0f;

	const float test[16] = {
		aspect * (1.0f / tanf(fovRadians / 2.0f)), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / tanf(fovRadians / 2.0f), 0.0f, 0.0f,
		0.0f, 0.0f, (zfar + znear) / (znear - zfar), (2.0f * zfar * znear) / (znear - zfar),
		0.0f, 0.0f, -1.0f, 0.0f
	};

	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(width, height);     // Set the window's initial width & height
	glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
	glEnable(GL_DEPTH_TEST);               // Enable depth testing

	// Switch to projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset projection matrix

	// Load the custom projection matrix
	glLoadMatrixf(test);

	// Switch back to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset modelview matrix

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutTimerFunc(16, update, 0);
	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}
