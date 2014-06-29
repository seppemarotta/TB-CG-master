#include "Util.h"
#include "PlayerController.h"

CPlayerController::CPlayerController(void)
{
}

CPlayerController::~CPlayerController(void)
{
}

void CPlayerController::asignarVehiculo(CVehiculo* pVehiculo){
	vehiculoControl = pVehiculo;
}

void CPlayerController::moverVehiculo(int direccion){
	vehiculoControl->moverVehiculo(direccion);
}

void CPlayerController::disparar(){
	vehiculoControl->disparar();
}