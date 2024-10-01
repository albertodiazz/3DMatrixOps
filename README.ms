# Proejeciton Matrix

# Perspective projection

Esta es la formula general de lo que nos espera en el documento. Basicamente de esta manera sacamos nuestra perspectiva. 

| (h/w) * (1 / tan(θ/2))     0                 0                    0           							|
|       0            (1 / tan(θ/2))            0                    0           						  | 
|       0                   0           zfar / (zfar - znear)   - (zfar * znear) / (zfar - znear) |   
|       0                   0                  1                    0           							| 


# Estos son los pasos para implementar un Projection Matrix
1.-Tenemos que tomar encuenta el aspect ratio
2.- Field of view angulo de cuanto abre la camara es basicamente cuanto vemos 
3.- Normalization x,y,z tenemos que normalizar los valores de nuestros objectos ya que tienen diferentes posiciones los vertices esto se realiza ocupando el rango entre -1 y 1

# Aspect ratio
|x|    |a x|
|y| -> |y  |
|z|    |z  |

## Formula
	a = h/w

# Field of View
Como regla general a mayor apertura de field view caben mas objetos en el campo de vision pero nuestros objetos se vuelven mas pequennos, a menor apertura del field of view mas grande son los objetos. Esto se debe a que al tener muy abierto el field of view tenemos que procesar mas informacion y hay que recordar que al trabajar con valores normalizados vamos a tener mas informacion de datos.

						  Camara
                |
                |
               \|/
               fov -> Angulo de apertura
                ^
               / \
              /   \
     (-1)    /  |  \   (+1)
            /   |   \
           /    |    \
          /     |     \
         /      |      \
        /       |       \
     (-1)    adjacent   (+1)
       Eye               Screen

## Formula
	f = 1 / tan(0/2)

#### Donde:
- f es el factor de proyección o distancia focal.
- θ es el ángulo de campo de visión (FOV).
- tan(θ/2) es la tangente de la mitad del ángulo de FOV, que define la relación entre la distancia al plano de proyección y el ancho de la vista proyectada. Esto nos da la escala

Estos calculos sucedes solo en X y Y como podemos observar abajo, para Z ocupamos la normalization.

|x|    |a f x|
|y| -> |  f y|
|z|    |		z|

# Normalization
El termino de normalizacion es para ver cuales son nuestros objetos mas cercanos en base a nuestro ojo en z.

1.- λ (lambda):
	* En este contexto, lambda es una constante que se utiliza para normalizar las coordenadas en el eje Z en gráficos 3D, especialmente durante la transformación de proyección. Este valor permite escalar y ajustar las coordenadas de profundidad (Z) para que los objetos que están entre los planos cercanos y lejanos (znear y zfar) puedan ser correctamente representados en un sistema de coordenadas normalizado.

2. - zfar y znear:
	* zfar: Es el plano más lejano en la escena que puede ser visualizado por la cámara.
  * znear: Es el plano más cercano que puede ser visualizado por la cámara.
  * La diferencia zfar - znear es importante porque define el rango de profundidad que se normaliza.

				 Eye
					|
					V 0
				 / \
				/   \
			 /-----\ znear
			/       \
		 /         \
		/           \
	 1 __________  1 
				 zfar

## Formula
	lambda = (zfar / (zfar - znear)) - (zfar / (zfar - znear) * znear)

|x|    |a f x|
|y| -> |  f y|
|z|    |lambd|


# Matrix conversion
Esto es pasar lo anterior ya a matrices para la su transformacion.
--------------------------------------------------
|x|    |(formual A) (Formula F) * x|
|y| -> |            (formula F) * y|
|z|    |				Funciona lambda * z|
--------------------------------------------------
| afx |   =  | (h/w) * (1 / tan(θ/2)) * x |
| fy  |      | (1 / tan(θ/2)) * y         |
| λz - λ * znear |  | ((zfar / (zfar - znear)) * z) - ((zfar / (zfar - znear)) * znear) |
--------------------------------------------------


|x|    |a f x|
|y| -> |  f y|
|z|    |lambd|
|1| -> Aqui es donde guardamos nuestro valor z no normalizado de 3,2.

# Perspective ortographic 
 
# Generales

##  Radianes vs Grados:
Cuando hacemos uso de radianes en los calculos con funciones trigometricas en C++ como (tan, sin, cos) estas funciones esperan que los angulos esten en radiantes, no en grados.

* Grados: Son una unidad tradicional para medir ángulos, donde un círculo completo tiene 360 grados.
* Radianes: Es la unidad "natural" para medir ángulos en matemáticas y física. En radianes, un círculo completo tiene 
2 𝜋 radianes, lo que significa que 180∘ es igual a 𝜋 radianes.

radianes = grados * (pi / 180)
