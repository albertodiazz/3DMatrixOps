#include <cmath>
#include <cstdlib>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 40;
const int SCREEN_HEIGHT = 20;
const char EMPTY_CHAR = '-';
const char TRIANGLE_CHAR = '*';

struct vec4D {
	float x, y, z, w;
};

struct mat4x4 {
	float mat[4][4];
};

struct triangulo {
	vec4D vertices[3] = {
		{-0.2f, 0.0f, 0.0f, 1.0f},  // Cambié w a 1.0f
		{0.0f, 0.5f, 0.0f, 1.0f},  // Cambié w a 1.0f
		{0.2f, 0.0f, 0.0f, 1.0f}   // Cambié w a 1.0f
	};
};

// Multiplicación de un vector por una matriz
// En este punto es donde aplicamos la matriz de proyeccion a nuestras vertices
// m es la projectionPerspective
// i es nuestro mesh o triangulos
/*⎡ o_x ⎤   ⎡ i_x ⋅ m_00 + i_y ⋅ m_10 + i_z ⋅ m_20 + i_w ⋅ m_30 ⎤*/
/*⎢ o_y ⎥ = ⎢ i_x ⋅ m_01 + i_y ⋅ m_11 + i_z ⋅ m_21 + i_w ⋅ m_31 ⎥*/
/*⎢ o_z ⎥   ⎢ i_x ⋅ m_02 + i_y ⋅ m_12 + i_z ⋅ m_22 + i_w ⋅ m_32 ⎥*/
/*⎣ o_w ⎦   ⎣ i_x ⋅ m_03 + i_y ⋅ m_13 + i_z ⋅ m_23 + i_w ⋅ m_33 ⎦*/
vec4D multiplyMatrixVector(const vec4D& i, const mat4x4& m) {
	vec4D o;
	o.x = i.x * m.mat[0][0] + i.y * m.mat[1][0] + i.z * m.mat[2][0] + i.w * m.mat[3][0];
	o.y = i.x * m.mat[0][1] + i.y * m.mat[1][1] + i.z * m.mat[2][1] + i.w * m.mat[3][1];
	o.z = i.x * m.mat[0][2] + i.y * m.mat[1][2] + i.z * m.mat[2][2] + i.w * m.mat[3][2];
	o.w = i.x * m.mat[0][3] + i.y * m.mat[1][3] + i.z * m.mat[2][3] + i.w * m.mat[3][3];
	return o;
}

mat4x4 projectionPerspective(float width, float height) {
	float aspect = width / height;
	float fov = 90.0f;
	float fovRadians = fov * (3.14159f / 180.0f); 
	float znear = 1.1f;
	float zfar = 1000.0f;

	mat4x4 m = {{{0}}};
	m.mat[0][0] = aspect * (1.0f / tan(fovRadians / 2.0f));
	m.mat[1][1] = (1.0f / tan(fovRadians / 2.0f));
	m.mat[2][2] = zfar / (zfar - znear);
	m.mat[2][3] = - (zfar * znear) / (zfar - znear);
	// Esto es mas que nada para el buffering o cosas mas complejas
	// hay que estudiar esta parte
	m.mat[3][2] = 1.0f;

	return m;
}

// Función para imprimir la "pantalla" en ASCII
void drawScreen(char screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			printf("%c", screen[y][x]);
		}
		printf("\n");
	}
}

// Función para proyectar las coordenadas a la pantalla ASCII
void drawTriangleOnScreen(triangulo& t, mat4x4& projectionMatrix) {
	char screen[SCREEN_HEIGHT][SCREEN_WIDTH];

	// Inicializar la pantalla vacía
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			screen[y][x] = EMPTY_CHAR;
		}
	}

	// Proyectar los vértices del triángulo
	for (int i = 0; i < 3; i++) {
		vec4D projected = multiplyMatrixVector(t.vertices[i], projectionMatrix);

		// Normalización por w
		// Projection divide
		if (projected.w != 0.0f) {
			projected.x /= projected.w;
			projected.y /= projected.w;
			projected.z /= projected.w;
		}

		// Imprimir las coordenadas proyectadas antes de la conversión a la pantalla ASCII
		printf("Vértice %d proyectado: x = %f, y = %f, z = %f, w = %f\n", i+1, projected.x, projected.y, projected.z, projected.w);

		// Convertir las coordenadas a la escala de la pantalla ASCII
		int screenX = (int)((projected.x + 1.0f) * 0.5f * (float)SCREEN_WIDTH);
		int screenY = (int)((1.0f - (projected.y + 1.0f) * 0.5f) * (float)SCREEN_HEIGHT);

		// Asegurarse de que los puntos estén dentro de los límites de la pantalla
		if (screenX >= 0 && screenX < SCREEN_WIDTH && screenY >= 0 && screenY < SCREEN_HEIGHT) {
			screen[screenY][screenX] = TRIANGLE_CHAR;
		}
	}

	// Dibujar la pantalla en ASCII
	drawScreen(screen);
}

int main() {

	triangulo t;
	mat4x4 projectionMatrix = projectionPerspective(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Dibujar el triángulo proyectado en la pantalla ASCII
	drawTriangleOnScreen(t, projectionMatrix);

	return EXIT_SUCCESS;
}
