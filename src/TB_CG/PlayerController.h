#pragma once
#include "Vehiculo.h"

class CPlayerController
{
private:
	CVehiculo * vehiculoControl; //vehiculo que controla el jugador
public:
	CPlayerController(void);
	~CPlayerController(void);

	void asignarVehiculo(CVehiculo* pVehiculo); //le asigna un vehiculo que podra controllar
	void moverVehiculo(int direccion); //0 = adelante, 1= derecha, 2= atras, 3=izquierda 
	void disparar();

};
