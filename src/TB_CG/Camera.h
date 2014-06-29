#pragma once
#include "Vehiculo.h"

//esta clase es una camara que persigue a un objeto 
class CCamera
{
public:
	Vector3 pos;
	float distObjCam; //distacia entre el objeto y la camara. Se usa como radio para determinar la posicion de la camara; 
	float anguloCam; //angulo en el que la camara mira al objeto que esta siguiendo
	float efectoCam;
public:
	CCamera();
	~CCamera();

	void seguirA(CVehiculo* playerVehiculo);
};
