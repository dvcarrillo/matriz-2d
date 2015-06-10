/*****************************************************************************/
// DAVID VARGAS CARRILLO
// https://github.com/dvcarrillo
//
// Demostración de la funcionalidad de la clase Matriz2D
//
// USO: 
// El programa recibe 2 argumentos en su ejecucion:
//
// $ ./DemoMatriz2D <Fichero_E> <Fichero_S>
// 
// Donde <Fichero_E> es el fichero de entrada, que se copiará a la matriz
// y <Fichero_S> es el fichero de salida, donde se copiará la matriz del 
// objeto
//
// Fichero: DemoMatriz2D.cpp
/*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "Matriz2D.h"

using namespace std;

int main(int argc, char const *argv[])
{
	// Comprobación de los argumentos dados y apertura de los flujos

	if (argc != 3)
	{
		cerr << "ERROR: número de argumentos introducidos inválido\n";
		cerr << "Uso: ./DemoMatriz2D <Fichero_E> <Fichero_S>\n";
		cerr << "<FicheroE>: fichero de entrada\n";
		cerr << "<FicheroS>: fichero de salida\n";
		cerr << endl;
		exit(1);
	}

	ifstream fi (argv[1], ios::binary);
	if (!fi)
	{
		cerr << "ERROR: imposible abrir " << argv[1] << endl;
		exit (1);
	}

	ofstream fo (argv[2], ios::binary);
	if (!fo)
	{
		cerr << "ERROR: imposible crear " << argv[2] << endl;
		exit(1);
	}

	// Creación de la matriz y comprobación de los métodos
	// aplicados a los ficheros

	Matriz2D m;

	m.LeeFichero(argv[1]);
	MuestraMatriz(m, "nueva matriz");
	m.EscribeFichero(argv[2]);

	// Cierre de flujos

	fi.close();
	fo.close();

	return 0;
}
