/*****************************************************************************/
// DAVID VARGAS CARRILLO
// https://github.com/dvcarrillo
//
// Declaración de la clase Matriz2D
//
// Fichero: Matriz2D.h
/*****************************************************************************/

#ifndef MATRIZ_2D
#define MATRIZ_2D

typedef double TipoBase;

/*****************************************************************************/
/*****************************************************************************/

class Matriz2D
{

private:

	// Los datos se almacenan en filas independientes.
	// Cada fila es accesible desde un vector de punteros.
	// "datos" contiene la dirección de memoria del primer elemento del vector
	// dinámico de punteros.
	// Para acceder a una fila: datos [i]		= > 	int *
	// Para acceder a un dato:	datos [i][j]	= >		int 

	TipoBase ** datos;

	// Datos que almacenan el número de filas y columnas de la matriz dinámica
	// PRE: 0 <= filas
	// PRE: 0 <= columnas

	int filas;
	int columnas;

public:

	///////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORES Y DESTRUCTOR

/***************************************************************************/
	// Constructor sin argumentos: crea una matriz vacía.	
	Matriz2D (void);

/***************************************************************************/
	// Constructor con un argumento: crea una matriz cuadrada "n x n".
	Matriz2D (int n);

/***************************************************************************/
	// Constructor con dos argumentos: crea una matriz rectangular "f x c"
	Matriz2D (int f, int c);

/***************************************************************************/
	// Constructor de copia: copia a la matriz actual la recibida como arg.
	Matriz2D (const Matriz2D & otro);

/***************************************************************************/
	// Destructor: se encarga de liberar la memoria
	~Matriz2D (void);

	//////////////////////////////////////////////////////////////////////////
	// MÉTODOS PARA TRATAR CON FICHEROS
	//
	// IMPORTANTE: FORMATO DEL FICHERO BINARIO:
	// Dos números enteros (int) que indican el número de filas y de columnas
	// que contiene la matriz, respectivamente. Los siguen el resto de números
	// reales (double) que compondrán la matriz

/***************************************************************************/
	// Lee datos de un fichero binario y los guarda en la matriz
	void LeeFichero (const char * nombre_fichero);

/***************************************************************************/
	// Escribe los datos de la matriz en un fichero binario
	void EscribeFichero (const char * nombre_fichero);

	//////////////////////////////////////////////////////////////////////////
	// MÉTODOS PROPIOS DE LA MATRIZ

/***************************************************************************/
	// Rellena todas las casillas de la matriz con el valor indicado
	void Inicializar (const TipoBase num);

/***************************************************************************/
	// Consulta si la matriz está vacía
	bool EstaVacia (void) const;

/***************************************************************************/
	// Consulta el número de filas y columnas de la matriz
	int Filas (void) const;
	int Columnas (void) const;

	//////////////////////////////////////////////////////////////////////////
	// MÉTODOS APLICADOS A LOS OPERADORES

/***************************************************************************/
	// Método de acceso individual a los elementos de la matriz
	// Método de lectura/escritura
	TipoBase & operator () (const int fila, const int columna);
	TipoBase & operator () (const int fila, const int columna) const;

/***************************************************************************/
	// Operador de asignación
	Matriz2D & operator = (const Matriz2D & otro);
	Matriz2D & operator = (const TipoBase & valor);

/***************************************************************************/
	// Operadores == y !=
	// Comparan el contenido de las matrices
	bool operator == (const Matriz2D otro);
	bool operator != (const Matriz2D otro);

private:

	///////////////////////////////////////////////////////////////////////////
	// FUNCIONES DE GESTIÓN DE MEMORIA

/***************************************************************************/
	// Función que reserva memoria en el heap para la matriz
	void ReservarMemoria (int filas, int columnas);

/***************************************************************************/
	// Función que libera la memoria ocupada por la matriz
	void LiberarMemoria (void);

/***************************************************************************/
	// Copia los datos de otro objeto al objeto actual
	void CopiarDatos (const Matriz2D & otro);
};

///////////////////////////////////////////////////////////////////////////////
// FUNCIONES NO PERTENECIENTES A LA CLASE

/*****************************************************************************/
// Muestra por la salida estándar los valores que contiene la matriz dada
// como argumento junto con el mensaje indicado
void MuestraMatriz (const Matriz2D & m, const char * const msg);

#endif
