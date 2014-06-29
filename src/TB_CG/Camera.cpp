#include "Util.h"
#include "Camera.h"

CCamera::CCamera()
{
	pos = Vector3(0, 0, 0);
	distObjCam = 20.0f;
	anguloCam = 75.0f; // -90 (frente) <= anguloCam <= 90 (atras)
	efectoCam = 0.0f;
}

CCamera::~CCamera()
{
}

void CCamera::seguirA(CVehiculo* playerVehiculo){
	
	float dx, dy, dz;
	dx = playerVehiculo->vDireccion->x;
	dy = playerVehiculo->vDireccion->y;
	dz = playerVehiculo->vDireccion->z;

	//evita division entre 0
	if (dx == 0)	dx = 0.000001;
	if (dy == 0)	dy = 0.000001;
	if (dz == 0)	dz = 0.000001;

	//redondea a 4 cifras
	GLfloat tetha = redondear(atan(dx / dz) * 1000) / 1000;
	if ((dx > 0 && dz > 0) || (dx < 0 && dz > 0))
		tetha += PI;
	

	GLfloat phi = anguloCam * PI / 180;

	

	//printf("angulo: %.2f rads: %.2f \n", tetha * 180/PI, tetha);

	//esta parte de codigo le da un efecto agradable de estar girando
	if (tetha < 0) tetha += 2 * PI;

	if (playerVehiculo->bIzquierda || efectoCam > 0){
		tetha -= (PI / 18) * efectoCam;
		if (playerVehiculo->bIzquierda && efectoCam < 1) {
			efectoCam += 0.2;
			//if (efectoCam > 1)
				//efectoCam = 1;
		}
	}
	if (playerVehiculo->bDerecha || efectoCam < 0){
		tetha += (PI / 18) * (efectoCam*-1);
		if (playerVehiculo->bDerecha && efectoCam > -1) {
			efectoCam -= 0.2;
			//if (efectoCam < -1)
				//efectoCam = -1;
		}
			
	}
	if (efectoCam > 0) {
		efectoCam -= 0.1;
		if (efectoCam < 0)
			efectoCam = 0;
	}

	if (efectoCam < 0) {
		efectoCam += 0.1;
		if (efectoCam > 0)
			efectoCam = 0;
	}
	if (playerVehiculo->bRetrocediendo && playerVehiculo->getaceleracion() < 0){
		tetha -= PI;
	}

	//printf("%.2f \n", tetha * 180/PI);

	//encontrar nuevas posiciones de la camara
	pos.x = playerVehiculo->getx() + distObjCam * sin(tetha) * sin(phi);
	pos.y = playerVehiculo->gety() + distObjCam * cos(phi);
	pos.z = playerVehiculo->getz() + distObjCam * cos(tetha) * sin(phi);

	gluLookAt(pos.x, pos.y, pos.z, //posicion de la camara
		playerVehiculo->getx(), playerVehiculo->gety(), playerVehiculo->getz(), //posicion a donde se quiere mirar
		0.0f, 1.0f, 0.0f); //direccion de la imagen (y = 1 imagen normal, y = -1 imagen invertida)
}
