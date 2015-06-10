/*****************************************************************************/
// DAVID VARGAS CARRILLO
// https://github.com/dvcarrillo
//
// Implementación de la clase Matriz2D
//
// Fichero: Matriz2D.cpp
/*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "Matriz2D.h"

using namespace std;

/*****************************************************************************/
// Constructor sin argumentos
// Crea una matriz vacía

Matriz2D :: Matriz2D (void) : filas(0), columnas(0), datos(0) {}

/*****************************************************************************/
// Constructor con un argumento
// Crea una matriz cuadrada "n x n"

Matriz2D :: Matriz2D (int n) : filas (n), columnas(n)
{
	ReservarMemoria (filas, columnas);
}

/*****************************************************************************/
// Constructor con dos argumentos
// Crea una matriz rectangular "f x c"

Matriz2D :: Matriz2D (int f, int c) : filas (f), columnas(c)
{
	ReservarMemoria (filas, columnas);
}

/*****************************************************************************/
// Constructor de copia
// Recibe un objeto de Matriz2D y lo copia a la matriz actual

Matriz2D :: Matriz2D (const Matriz2D & otro)
{
	// Reserva memoria para los datos a copiar
	ReservarMemoria (otro.filas, otro.columnas);

	// Copia los datos de una matriz a la otra
	CopiarDatos (otro);
}

/*****************************************************************************/
// Destructor
// Libera la memoria ocupada por la matriz

Matriz2D :: ~Matriz2D (void)
{
	LiberarMemoria();
}

/*****************************************************************************/
// Lee datos de un fichero binario y los guarda en la matriz
//
// ¡IMPORTANTE! FORMATO DEL FICHERO BINARIO:
// Dos números enteros (int) que indican el número de filas y de columnas
// que contiene la matriz, respectivamente. Los siguen el resto de números
// reales (double) que compondrán la matriz

void Matriz2D :: LeeFichero (const char * nombre_fichero)
{
	// Se libera la memoria que ocupa la matriz, ya que puede haber otra
	// almacenada anteriormente
	LiberarMemoria();

	// Variables que almacenarán las filas y columnas leídas del fichero
	int filas_fichero, columnas_fichero;

	// Apertura en binario del fichero indicado mediante un flujo de entrada
	ifstream fi (nombre_fichero, ios::binary);

	if (!fi)
	{
		cerr << "ERROR: imposible abrir " << nombre_fichero << endl;
		exit(1);
	}

	// Lectura del número de filas y columnas y almacenamiento en las variables
	fi.read(reinterpret_cast <char *> (&filas_fichero), sizeof(int));
	fi.read(reinterpret_cast <char *> (&columnas_fichero), sizeof(int));

	cout << "Se ha encontrado una matriz de dimensiones " << filas_fichero;
	cout << " x " << columnas_fichero << endl;

	// Conocidos dichos datos, ya se puede leer la matriz del fichero

	double numero;

	for (int fil = 0; fil < filas_fichero; ++fil)
	{
		for (int col = 0; col < columnas_fichero; ++col)
		{
			fi.read(reinterpret_cast <char *> (&numero), sizeof(double));
			(*this) (fil, col) = numero;
		}
	}

	cout << "Datos escritos correctamente" << endl;

	fi.close();
}

/*****************************************************************************/
// Escribe los datos de la matriz en un fichero binario
//
// ¡IMPORTANTE! FORMATO DEL FICHERO BINARIO:
// Dos números enteros (int) que indican el número de filas y de columnas
// que contiene la matriz, respectivamente. Los siguen el resto de números
// reales (double) que compondrán la matriz

void Matriz2D :: EscribeFichero (const char * nombre_fichero)
{	
	// Apertura en binario del fichero indicado mediante un flujo de salida
	ofstream fo (nombre_fichero, ios::binary);

	if (!fo)
	{
		cerr << "ERROR: imposible crear " << nombre_fichero << endl;
		exit (1);
	}

	// Se escriben los dos primeros enteros en binario, que indicarán el
	// número de filas y columnas de la matriz
	fo.write(reinterpret_cast <char *> (&filas), sizeof(int));
	fo.write(reinterpret_cast <char *> (&columnas), sizeof(int));

	cout << "Se copiarán " << columnas << " columnas y " << filas << "filas ";
	cout << " al fichero" << endl;

	// Escribe en el fichero el resto de numeros reales en binario de la matriz

	double numero;

	for (int fil = 0; fil < filas; ++fil)
	{
		for (int col = 0; col < columnas; ++col)
		{
			numero = (*this) (fil, col);
			fo.write(reinterpret_cast <const char *> (&numero), sizeof(double));
		}
	}

	cout << "Datos escritos correctamente" << endl;

	fo.close();
}

/*****************************************************************************/
// Rellena todas las casillas de la matriz con el valor indicado
void Matriz2D :: Inicializar (const TipoBase num)
{
	for (int fil = 0; fil < filas; ++fil)
		for (int col = 0; col < columnas; ++col)
			(*this) (fil,col) = num;
}

/*****************************************************************************/
// Consulta si la matriz está vacía
bool Matriz2D :: EstaVacia (void) const
{
	return (datos == 0);
}

/*****************************************************************************/
// Consulta el número de filas de la matriz
int Matriz2D :: Filas (void) const
{
	return(filas);
}

/*****************************************************************************/
// Consulta el número de columnas de la matriz
int Matriz2D :: Columnas (void) const
{
	return(columnas);
}

/*****************************************************************************/
// Métodos de acceso individual a los elementos de la matriz: operador ()
// Métodos de lectura/escritura
// PRE: 0 <= posicion < usados
TipoBase & Matriz2D :: operator () (const int fila, const int columna)
{
	return(datos[fila][columna]);
}

TipoBase & Matriz2D :: operator () (const int fila, const int columna) const
{
	return(datos[fila][columna]);
}

/*****************************************************************************/
// Operador de asignación
// Recibe otra matriz, por lo que la copiará en la actual
Matriz2D & Matriz2D :: operator = (const Matriz2D & otro)
{
	if ((*this) != otro)
	{
		// Libera la memoria que pudiera ya ocupar el objeto implícito
		LiberarMemoria();

		// Se hace una nueva reserva de memoria para la nueva matriz
		ReservarMemoria(otro.filas, otro.columnas);

		// Copia de datos de la matriz explícita a la implícita
		CopiarDatos(otro);
	}

	return (*this);
}

/*****************************************************************************/
// Operador de asignación
// Recibe un número de tipo TipoBase, por lo que inicializa toda la matriz
// a el valor indicado
Matriz2D & Matriz2D :: operator = (const TipoBase & valor)
{
	// Escribe "valor" en todas las casillas
	Inicializar(valor);

	return (*this);
}

/*****************************************************************************/
// Operador ==
// Comprueba si dos matrices son iguales
bool Matriz2D :: operator == (const Matriz2D otro)
{
	// Se compara si tienen el mismo tamaño
	bool iguales = ((filas == otro.filas) && (columnas == otro.columnas));

	// En el caso de que tengan el mismo tamaño, se hace una comparación
	// valor a valor
	if (iguales)
	{
		for (int fil = 0; fil < filas; ++fil)
		{
			for (int col = 0; col < columnas; ++col)
			{
				if (datos[fil][col] != otro.datos[fil][col])
					iguales = false;
			}
		}
	}

	return (iguales);
}

/*****************************************************************************/
// Operador !=
// Comprueba si dos matrices son diferentes
bool Matriz2D :: operator != (const Matriz2D otro)
{
	return !((*this) == otro);
}

/*****************************************************************************/
// Función que reserva memoria en el heap para la matriz
void Matriz2D :: ReservarMemoria (int filas, int columnas)
{
	// Reserva memoria para el vector de punteros
	datos = new TipoBase * [filas];

	// Reserva memoria para cada fila
	for (int i = 0; i < filas; ++i)
		datos[i] = new TipoBase [columnas];
}

/*****************************************************************************/
// Función que libera la memoria ocupada por la matriz
void Matriz2D :: LiberarMemoria (void)
{
	// Se ejecutará si la matriz no es vacía (puntero "datos" no nulo)
	if (datos)
	{
		// Eliminación de las filas
		for (int i = 0; i < filas; ++i)
		{
			delete [] datos[i];
		}

		// Eliminación del vector de punteros
		delete [] datos;

		// Establece el puntero nulo
		datos = 0;
	}
}

/*****************************************************************************/
// Copia los datos de otro objeto al objeto actual
void Matriz2D :: CopiarDatos (const Matriz2D & otro)
{
	// Se copian los campos privados del número de filas y columnas
	filas = otro.filas;
	columnas = otro.columnas;

	// Se copian los bloques de memoria que representan cada fila
	for (int i = 0; i < filas; ++i)
	{
		memcpy (datos[i], otro.datos[i], columnas * sizeof(TipoBase));
	}
} 

/*****************************************************************************/
// Muestra por la salida estándar los valores que contiene la matriz dada
// como argumento junto con el mensaje indicado
void MuestraMatriz (const Matriz2D & m, const char * const msg)
{
	cout << "Mostrando: " << msg << endl << endl;

	for (int fil = 0; fil < m.Filas(); ++fil)
	{
		for (int col = 0; col < m.Columnas(); ++col)
		{
			cout << setw(4) << m(fil,col) << "  ";
		}

		cout << endl;
	}

	cout << endl;
}
