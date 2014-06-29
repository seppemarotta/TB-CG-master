#include "Disparo.h"

CDisparo::CDisparo(float x, float y, float z, Vector3* pvDireccion)
{
	vPosicionInicial = Vector3(x,y,z);
	vPosicion = Vector3(x,y,z);
	vDireccion = (*pvDireccion);//Vector3(pvDireccion->x, pvDireccion->y, pvDireccion->z);

	rango = 100;
	velocidad = 150;

	bActivo = 1;
}


CDisparo::~CDisparo(void)
{
}

Vector3 CDisparo::getPos()
{
	return vPosicion;
}
void CDisparo::colision(){
	bActivo=false;
	printf("colision\n----------------\n");
}
void CDisparo::mover(){
	vPosicion += vDireccion * velocidad *dTiempo;

	if(vPosicionInicial.Distance(vPosicion) > rango)
		bActivo = false;
}

void CDisparo::dibujar(){
	if(!bActivo)
		return;

	//Hallar angulo formado por el vector direccion
	float dx, dy, dz;
	dx = vDireccion.x;
	dy = vDireccion.y;
	dz = vDireccion.z;

	//evita division entre 0
	if (dx == 0)	dx = 0.000001;
	if (dy == 0)	dy = 0.000001;
	if (dz == 0)	dz = 0.000001;

	//redondea a 4 cifras
	GLfloat tetha = redondear(atan(dx / dz) * 1000) / 1000;
	if ((dx > 0 && dz > 0) || (dx < 0 && dz > 0))
		tetha += PI;

	

	glBindTexture(GL_TEXTURE_2D, 0); 
	glColor3f(1.0f, 0.0f, 0.0f);
	
	glTranslatef(vPosicion.x, vPosicion.y+3, vPosicion.z );
	glRotatef( tetha*180 / PI, 0, 1, 0); 

	glBegin(GL_QUADS);
		glVertex3f(  1.0f, 0.0f, -1.0f);
		glVertex3f( -1.0f, 0.0f, -1.0f);
		glVertex3f( -1.0f, 0.0f,  1.0f);
		glVertex3f(  1.0f, 0.0f,  1.0f);
	glEnd();

	glRotatef(-tetha * 180 / PI, 0, 1, 0);
	glTranslatef(-vPosicion.x, -(vPosicion.y+3), -vPosicion.z );

	mover();
}