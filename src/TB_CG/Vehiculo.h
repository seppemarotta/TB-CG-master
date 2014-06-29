#pragma once
#include "Object.h"
#include "Disparo.h"
#include "3ds.h"
#include "TextureObjects.h"

//3DS Variable Information
//#define FILE_TEXTURE_3DS "granada.3DS"
#define FILE_TEXTURE_3DS "data/vehiculo1.3DS"
//#define FILE_TEXTURE_3DS "data/sweeetTooth.3DS"


//este define te crea los metodos get y set automaticamente
#define			property(Type, Variable) private: Type Variable; \
				public: const Type##& get##Variable() const { return Variable; }; \
				void set##Variable(const Type& Variable##_) { Variable = Variable##_;}

#define gravedad 9.81
#define maxAceleracion 10
#define maxVelocidad 100
#define coefRozamiento 0.1
#define acelXSeg 1.0
#define Freno 10 //fuerza del freno


class CVehiculo: public CObject
{
//private:
public:
	property(float, masa);
	property(float, velocidad); property(float, aceleracion);
	float fFreno; //porcentaje del freno que se encuentra apretado

	float angulo;

	int vidas;

	//vectores
	Vector3 *vDireccion;

	//arreglo de disparos
	vector<CDisparo*> disparos;
	CDisparo* dispa;
	bool btest;
	//estados
	bool bMovimiento;	//Si el vehiculo esta en movimiento
	bool bAcelerando;	//Si el vehiculo se encuentra acelerando
	bool bFrenando;		//Si el vehiculo esta frenando
	bool bRetrocediendo;//Si el vehiculo esta en retroceso	
	bool bIzquierda;	//Si se encuentra volteando a la izquierda
	bool bDerecha;		//Si se encuentra volteando a la derecha


	//cargar modelo|-------
	int   g_ViewMode;
	CLoad3DS g_Load3ds;								// This is 3DS class.  This should go in a good model class.
	t3DModel g_3DModel;								// This holds the 3D Model info that we load in
	UINT g_Texture[10];						// This holds the texture info, referenced by an ID

	//set up a structure for the texture system
	CTextures Textures;

	void _Load_3DS_Object();
	void _Draw_3DS_Object(int pX, int pY, int pZ, int pSize);
	void _actualizarComportamiento();

public:
	CVehiculo(void);
	~CVehiculo(void);

	void dibujarVehiculo();
	void moverVehiculo(int control);
	void disparar();
	// si el vehiculo choca con algo.
	void colision();
	vector<CDisparo*> getDisparos();
};
