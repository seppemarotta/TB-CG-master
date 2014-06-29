#pragma once
#include "Object.h"
#include "Util.h"

//bala
class CDisparo
{
public: //cambiar a private luego
	int rango; //distancia que recorre antes de ser destruida
	int velocidad;
	Vector3 vPosicionInicial;
	Vector3 vPosicion;
	Vector3 vDireccion;

	bool bActivo; //revisa si el disparo un sigue funcionando o si necesita ser destruida
public:
	CDisparo(float x, float y, float z, Vector3* pvDireccion);
	~CDisparo(void);
	Vector3 getPos();
	void mover();
	void colision();
	void dibujar();
};

