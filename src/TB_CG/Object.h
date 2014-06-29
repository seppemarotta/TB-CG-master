#pragma once



//este define te crea los metodos get y set automaticamente
#define			property(Type, Variable) private: Type Variable; \
				public: const Type##& get##Variable() const { return Variable; }; \
				void set##Variable(const Type& Variable##_) { Variable = Variable##_;}



//Clase General de Cualquier Objeto que ocupa un lugar en el espacio.
class CObject
{
	//private:
protected:
	property(float, x); property(float, y); property(float, z);//posicion centro pegado al lado de abajo del Object (cambiar por un vector posicion)
	property(float, largo);property(float, ancho);
	
public:
	CObject(void);
	~CObject(void);
	virtual void colision() const{}

};
