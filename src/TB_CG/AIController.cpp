#include "AIController.h"


CAIController::CAIController(void)
{
	dificultad = 0; // para implementar diferentes tipos de dificultad
}


CAIController::~CAIController(void)
{
}

void CAIController::logica(){
	switch(dificultad){
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
}
void CAIController::asignarVehiculo(CVehiculo* pVehiculo){
	vehiculoControl = pVehiculo;
}

void CAIController::moverVehiculo(int direccion){
	vehiculoControl->moverVehiculo(direccion);
}

void CAIController::disparar(){
	vehiculoControl->disparar();
}

