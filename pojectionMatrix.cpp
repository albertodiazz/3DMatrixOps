#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct vec3d {
    float x, y, z;
};

struct triangle {
    vec3d p[3]; // Tres vértices para un triángulo
};

struct mesh {
    vector<triangle> triangulo; // La malla contiene un conjunto de triángulos
};

struct mat4x4 {
    float m[4][4] = { 0 }; // Definimos una matriz 4x4
};

// Función para crear una matriz de proyección
void crearMatrizProyeccion(mat4x4 &matriz, float fov, float aspectRatio, float zNear, float zFar) {
    float fFovRad = 1.0f / tanf(fov * 0.5f * 3.14159f / 180.0f);
    matriz.m[0][0] = aspectRatio * fFovRad;
    matriz.m[1][1] = fFovRad;
    matriz.m[2][2] = zFar / (zFar - zNear);
    matriz.m[3][2] = (-zFar * zNear) / (zFar - zNear);
    matriz.m[2][3] = 1.0f;
    matriz.m[3][3] = 0.0f;
}

// Función para multiplicar un vector 3D por una matriz 4x4
vec3d multiplicarMatrizVector(vec3d &i, mat4x4 &m) {
    vec3d o;
    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    // Evitar la división por cero
    if (w != 0.0f) {
        o.x /= w; 
        o.y /= w; 
        o.z /= w;
    }
    return o;
}

// Asegurar que las coordenadas estén dentro de los límites de la cuadrícula
pair<int, int> convertirACoordenadaGrid(vec3d punto, int ancho, int alto) {
    int x = (int)((punto.x + 1.0f) * 0.5f * (float)ancho); // De [-1,1] a [0, ancho]
    int y = (int)((punto.y + 1.0f) * 0.5f * (float)alto);  // De [-1,1] a [0, alto]

    // Limitar los valores de x e y para que estén dentro de los límites de la cuadrícula
    if (x < 0) x = 0;
    if (x >= ancho) x = ancho - 1;
    if (y < 0) y = 0;
    if (y >= alto) y = alto - 1;

    return {x, y};
}

// Algoritmo de Bresenham para dibujar líneas en la cuadrícula ASCII
void trazarLinea(vector<vector<char>> &grid, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        grid[y0][x0] = '*'; // Dibujar el punto

        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Función para dibujar el triángulo en ASCII
void dibujarEnAscii(mesh &m, mat4x4 &matrizProyeccion, int ancho, int alto) {
    // Crear una cuadrícula vacía
    vector<vector<char>> grid(alto, vector<char>(ancho, ' '));

    // Proyectamos los vértices del triángulo
    for (auto &tri : m.triangulo) {
        vec3d p0_proyectado = multiplicarMatrizVector(tri.p[0], matrizProyeccion);
        vec3d p1_proyectado = multiplicarMatrizVector(tri.p[1], matrizProyeccion);
        vec3d p2_proyectado = multiplicarMatrizVector(tri.p[2], matrizProyeccion);

        // Convertimos los vértices proyectados a coordenadas de la cuadrícula
        auto [x0, y0] = convertirACoordenadaGrid(p0_proyectado, ancho, alto);
        auto [x1, y1] = convertirACoordenadaGrid(p1_proyectado, ancho, alto);
        auto [x2, y2] = convertirACoordenadaGrid(p2_proyectado, ancho, alto);

        // Dibujar las líneas entre los vértices del triángulo
        trazarLinea(grid, x0, y0, x1, y1);
        trazarLinea(grid, x1, y1, x2, y2);
        trazarLinea(grid, x2, y2, x0, y0);
    }

    // Imprimir la cuadrícula en la consola
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            cout << grid[y][x];
        }
        cout << endl;
    }
}

int main() {
    // Definimos la malla (con un triángulo como ejemplo)
    mesh m;
    m.triangulo = {
        { { {0.0f, 0.0f, 0.0f},
				{0.5f, -1.0f, 0.0f}, 
				{1.0f, 0.0f, 0.0f} } }
    };

    // Definimos el tamaño de la cuadrícula ASCII
    int ancho = 40;
    int alto = 35;

    // Parámetros de proyección
    float zNear = 0.1f; // Distancia mínima al plano de proyección
    float zFar = 1000.0f; // Distancia máxima
    float fov = 90.0f; // Campo de visión en grados
    float aspectRatio = (float)ancho / (float)alto; // Relación de aspecto

    // Creamos la matriz de proyección
    mat4x4 matrizProyeccion;
    crearMatrizProyeccion(matrizProyeccion, fov, aspectRatio, zNear, zFar);


    // Dibujamos el triángulo proyectado en la cuadrícula ASCII
    dibujarEnAscii(m, matrizProyeccion, ancho, alto);

    return 0;
}
