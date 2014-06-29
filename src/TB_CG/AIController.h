#pragma once
#include "Vehiculo.h"

class CAIController
{
private:
	CVehiculo * vehiculoControl; //vehiculo que controla esta IA
	int dificultad;
public:
	CAIController(void);
	~CAIController(void);

	void logica(); //insertar logica aqui

	void asignarVehiculo(CVehiculo* pVehiculo); //le asigna un vehiculo que podra controllar
	void moverVehiculo(int direccion); //0 = adelante, 1= derecha, 2= atras, 3=izquierda 
	void disparar();

};

