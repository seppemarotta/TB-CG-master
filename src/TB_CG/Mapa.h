#pragma once
#include <stdio.h>
#include <vector>
#include <queue>
#include "Texture.h"

#define PISO 'O'

using namespace std;
//el primer char guarda el tipo de piso y el segundo si hay algun objeto encima   
typedef pair<char,char> casilla;
typedef vector < vector < casilla > > map;

class CMapa
{
private:
	int filas,columnas;
	map *mapa;

	Texture *texture;

	void _lectura(char* archivoMapa);
public:
	CMapa(char* archivoMapa);
	~CMapa(void);
	void dibujarMapa();

};
