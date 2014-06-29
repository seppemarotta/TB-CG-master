#include "Util.h"
#include "Vehiculo.h"

CVehiculo::CVehiculo(void)
{
	btest = false;
	velocidad = 0;
	aceleracion = 0;
	masa = 50; //kg

	fFreno = 0;

	angulo = 70.0f;
	angulo = angulo*PI / 180;

	vidas = 3;

	vDireccion = new Vector3(0,0,1);

	bMovimiento = false;
	bAcelerando = false;
	bFrenando = false;
	bRetrocediendo = false;
	bIzquierda = false;
	bDerecha = false;

	//dispa = NULL;
	//disparos.resize(100);

	//-------
	g_ViewMode	  = GL_TRIANGLES;
	g_3DModel.numOfMaterials = 0;
	g_3DModel.numOfObjects = 0;
	for(int i = 0; i<10; i++)
		g_Texture[i] = 0;

	_Load_3DS_Object();
}

CVehiculo::~CVehiculo(void)
{
}

GLvoid CVehiculo::dibujarVehiculo(GLvoid){
	//Hallar angulo formado por el vector direccion
	float dx, dy, dz;
	dx = vDireccion->x;
	dy = vDireccion->y;
	dz = vDireccion->z;
	
	//Area de Colision

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0,0,-10);
	glEnd();




	//evita division entre 0
	if (dx == 0)	dx = 0.000001;
	if (dy == 0)	dy = 0.000001;
	if (dz == 0)	dz = 0.000001;

	//redondea a 4 cifras
	GLfloat tetha = redondear(atan(dx / dz) * 1000) / 1000;
	if ((dx > 0 && dz > 0) || (dx < 0 && dz > 0))
		tetha += PI;
	
	//poner al objeto en el origen
	glTranslatef(getx(), gety(), getz());
	//rotar de acuerdo al angulo hallado
	glRotatef( tetha*180 / PI, 0, 1, 0); 
	//printf("angulo: %.2f \n", tetha * 180/PI);

	//dibuja vector direccion
	glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0,0,-10);
	glEnd();	

		
		glBegin(GL_QUADS);
		//Dibuja Area de Impacto
		//Bottom
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(   1.0f,  -1.0f, -1.0f);
		glVertex3f(  -1.0f,  -1.0f, -1.0f);
		glVertex3f(  -1.0f,  -1.0f,  1.0f);
		glVertex3f(   1.0f,  -1.0f,  1.0f);
		glEnd();
		



	////dibuja cuadrado
	//glBegin(GL_QUADS);
	//	//Top
	//	glColor3f(1.0f, 0.5f, 0.0f);
	//	glVertex3f(   1.0f,  1.0f,  -1.0f);
	//	glVertex3f(  -1.0f,  1.0f,  -1.0f);
	//	glVertex3f(  -1.0f,  1.0f,  1.0f);
	//	glVertex3f(   1.0f,  1.0f,  1.0f);
	//	//Bottom
	//	glColor3f(0.0f, 1.0f, 0.0f);
	//	glVertex3f(   1.0f,  -1.0f, -1.0f);
	//	glVertex3f(  -1.0f,  -1.0f, -1.0f);
	//	glVertex3f(  -1.0f,  -1.0f,  1.0f);
	//	glVertex3f(   1.0f,  -1.0f,  1.0f);
	//	//Front
	//	glColor3f(1.0f, 0.0f, 0.0f);
	//	glVertex3f(   1.0f,   1.0f,  1.0f);
	//	glVertex3f(  -1.0f,   1.0f,  1.0f);
	//	glVertex3f(  -1.0f,  -1.0f,  1.0f);
	//	glVertex3f(   1.0f,  -1.0f,  1.0f);
	//	//Back
	//	glColor3f(1.0f, 1.0f, 0.0f);
	//	glVertex3f(   1.0f,  1.0f,  -1.0f);
	//	glVertex3f(  -1.0f,  1.0f,  -1.0f);
	//	glVertex3f(  -1.0f, -1.0f,  -1.0f);
	//	glVertex3f(   1.0f, -1.0f,  -1.0f);
	//	//Left
	//	glColor3f(0.0f, 0.0f, 1.0f);
	//	glVertex3f( -1.0f,  1.0f,  1.0f);
	//	glVertex3f( -1.0f,  1.0f, -1.0f);
	//	glVertex3f( -1.0f, -1.0f, -1.0f);
	//	glVertex3f( -1.0f, -1.0f,  1.0f);
	//	//Right
	//	glColor3f(1.0f, 0.0f, 1.0f);
	//	glVertex3f( 1.0f,  1.0f,  1.0f);
	//	glVertex3f( 1.0f,  1.0f, -1.0f);
	//	glVertex3f( 1.0f, -1.0f, -1.0f);
	//	glVertex3f( 1.0f, -1.0f,  1.0f);

	//glEnd();
	

	//dibujar modelo
	
	////vehiculo1
	glTranslatef(-4.0, -0.37, -2.75);
	_Draw_3DS_Object(0,0,0,20);
	glTranslatef(4.0, 0.37, 2.75);
	
	//sweetTooth
	/*glTranslatef(0, -1.87, 0.0);
	Draw_3DS_Object(0,0,0,20);
	glTranslatef(0, 1.87, 0.0);*/
	//deshace rotaciones y transalaciones hechas
	glRotatef(-tetha * 180 / PI, 0, 1, 0);
	glTranslatef(-getx(), -gety(), -getz());
	
	//printf("x = %.2f, y = %.2f, z = %.2f, vel = %.2f acel = %.2f, freno = %.2f\n", getx(), gety(), getz(), getvelocidad(), getaceleracion(), fFreno);
	//printf("movimiento: %d, acelerando: %d, frenando: %d, retrocediendo: %d \n", bMovimiento, bAcelerando, bFrenando, bRetrocediendo);


	//Dibujar disparos/proyectiles|-------
	for(int i = 0; i< disparos.size(); i++){
		disparos[i]->dibujar();
		if(!disparos[i]->bActivo){
			if( i != disparos.size()-1)
				disparos[i] = disparos[disparos.size()-1];
			disparos.pop_back();
		}
	}

	_actualizarComportamiento();

}

void CVehiculo::moverVehiculo(int control){
	
	float auxX;
	float auxY;
	float auxZ;

	auxX = vDireccion->x;
	auxY = vDireccion->y;
	auxZ = vDireccion->z;

	switch(control){
		case 0:
			bAcelerando = true;

			aceleracion += acelXSeg*dTiempo;
			if(aceleracion > maxAceleracion)
				aceleracion = maxAceleracion;
			
			//la aceleracion debe ser positiva para poder avanzar
			if (aceleracion > 0)
				if (velocidad + aceleracion > 0)
					velocidad = velocidad + aceleracion;
				else
					velocidad += aceleracion;
			else
				aceleracion += 1;

			if(velocidad > maxVelocidad)
				velocidad = maxVelocidad;
			break;
		case 1:
			if (bMovimiento){
				bDerecha = true;
				vDireccion->x = ((redondear(cos(-angulo*dTiempo) * 1000) / 1000)*auxX + (redondear(sin(-angulo*dTiempo) * 1000) / 1000)*auxZ);
				vDireccion->y = gety();
				vDireccion->z = ((redondear(-sin(-angulo*dTiempo) * 1000) / 1000)*auxX + (redondear(cos(-angulo*dTiempo) * 1000) / 1000)*auxZ);
			}
			break;
		case 2:
			bFrenando = true;

			aceleracion -= acelXSeg*dTiempo;
			if (aceleracion < -maxAceleracion)
				aceleracion = -maxAceleracion;


			//la aceleracion debe ser negativa para poder avanzar
			if (aceleracion < 0)							
				if (velocidad + aceleracion < 0){
					velocidad = velocidad + aceleracion;
					bRetrocediendo = true;
					fFreno = 0;
				}
				else{
					fFreno += 1 * dTiempo;
					velocidad += aceleracion - (Freno*fFreno);
				}
			else
				aceleracion -= 1;

			if (velocidad < -maxVelocidad/4)
				velocidad = -maxVelocidad/4;			
			break;
		case 3:
			if (bMovimiento){
				bIzquierda = true;
				vDireccion->x = ((redondear(cos(angulo*dTiempo) * 1000) / 1000)*auxX + (redondear(sin(angulo*dTiempo) * 1000) / 1000)*auxZ);
				vDireccion->y = gety();
				vDireccion->z = ((redondear(-sin(angulo*dTiempo) * 1000) / 1000)*auxX + (redondear(cos(angulo*dTiempo) * 1000) / 1000)*auxZ);
			}
			break;
	}

}

void CVehiculo::disparar(){
	disparos.push_back(new CDisparo(getx(), gety(), getz(), vDireccion));
}

//metodos privados|------
void CVehiculo::_actualizarComportamiento(){
	//Comportamiento del vehiculo |-------
	
	if (!bAcelerando && !bFrenando){	//Si no esta acelerando y no esta frenando (cuando el jugador no esta presionando ni atras ni adelante)
		if (!bRetrocediendo){				//Si no esta retrocediendo
			aceleracion -= 1;						//se reduce la aceleracion
			if (aceleracion < 0)					//Si la aceleracion llega a ser menor que 0
				aceleracion = 0;						//la aceleracion se vuelve 0

			velocidad = velocidad - (coefRozamiento*masa*gravedad)* dTiempo;	//se reduce la velocidad con la formula de friccion
			if (velocidad < 0)
				velocidad = 0;
		}
		else{								//sino
			aceleracion += 1;
			if (aceleracion > 0)
				aceleracion = 0;


			velocidad = velocidad + (coefRozamiento*masa*gravedad)* dTiempo;
			if (velocidad > 0)
				velocidad = 0;
		}
	}

	if(bMovimiento){
		setx(getx() + vDireccion->x * velocidad * dTiempo);
		sety(gety()+ vDireccion->y * velocidad * dTiempo);
		setz(getz()+ vDireccion->z * velocidad * dTiempo);
	}

	if (!bFrenando){
		fFreno -= 0.1;
		if (fFreno < 0)	fFreno = 0;
	}

	//actualizar estados del carro
	if(velocidad != 0)
		bMovimiento = true;
	else
		bMovimiento = false;

	if (velocidad < 0)
		bRetrocediendo = true;
	else
		bRetrocediendo = false;

	bAcelerando = false;
	bFrenando = false;	
	bIzquierda = false;
	bDerecha = false;
}

/******************************************* Load3DSObject *******************************************/
void CVehiculo::_Load_3DS_Object()
{
	// Load the *.3DS file.  We just pass in an address to our t3DModel structure and the file name string we want to load
	g_Load3ds.Import3DS(&g_3DModel, FILE_TEXTURE_3DS);			// Load our .3DS file into our model structure

	// Depending on how many textures we found, load each one
	for(int i = 0; i < g_3DModel.numOfMaterials; i++)
	{
		// Check to see if there is a file name to load in this material
		if(strlen(g_3DModel.pMaterials[i].strFile) > 0)
		{
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
			Textures.LoadTexture(g_3DModel.pMaterials[i].strFile, g_Texture[i]);				
		}

		// Set the texture ID for this material
		g_3DModel.pMaterials[i].texureId = i;
	}
}

/******************************************* DrawObject *******************************************/
void CVehiculo::_Draw_3DS_Object(int pX, int pY, int pZ, int pSize)
{
	// We want the model to rotate around the axis so we give it a rotation
	// value, then increase/decrease it. You can rotate right of left with the arrow keys.
	glPushMatrix();

	glRotatef(0, 0, 1.0f, 0);							// Rotate the object around the Y-Axis	
	//if (g_RotateObject)	{	g_RotateX += g_RotationSpeed;	}	// Increase the speed of rotation
	
	// We have a model that has a certain amount of objects and textures.  We want to go through each object 
	// in the model, bind it's texture map to it, then render it by going through all of it's faces (Polygons).  	
	
	// Since we know how many objects our model has, go through each of them.
	for(int i = 0; i < g_3DModel.numOfObjects; i++)
	{
		// Make sure we have valid objects just in case. (size() is in the vector class)
		if(g_3DModel.pObject.size() <= 0) break;

		// Get the current object that we are displaying
		t3DObject *pObject = &g_3DModel.pObject[i];
			
		// Check to see if this object has a texture map, if so bind the texture to it.
		if(pObject->bHasTexture) 
		{
			// Turn on texture mapping and turn off color
			glEnable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);

			// Bind the texture map to the object by it's materialID
			glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);
		} 
		else 
		{
			// Turn off texture mapping and turn on color
			glDisable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);
		}

		// This determines if we are in wireframe or normal mode
		glBegin(g_ViewMode);					// Begin drawing with our selected mode (triangles or lines)

			// Go through all of the faces (polygons) of the object and draw them
			for(int j = 0; j < pObject->numOfFaces; j++)
			{
				// Go through each corner of the triangle and draw it.
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// Get the index for each point of the face
					int index = pObject->pFaces[j].vertIndex[whichVertex];
			
					// Give OpenGL the normal for this vertex.
					glNormal3f(pObject->pNormals[index].x, pObject->pNormals[index].y, pObject->pNormals[index].z);
				
					// If the object has a texture associated with it, give it a texture coordinate.
					if(pObject->bHasTexture) 
					{

						// Make sure there was a UVW map applied to the object or else it won't have tex coords.
						if(pObject->pTexVerts) 
						{
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
						}
					} 
					else 
					{
						// if the size is at > 1 and material ID != -1, then it is a valid material.
						if(g_3DModel.pMaterials.size() && pObject->materialID >= 0) 
						{
							// Get and set the color that the object is, since it must not have a texture
							BYTE *pColor = g_3DModel.pMaterials[pObject->materialID].color;

							// Assign the current color to this model
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}

					// Pass in the current vertex of the object (Corner of current face)
					glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
				}
			}

		glEnd();			// End the model drawing
	}

	glPopMatrix();
}

void CVehiculo::colision()
{
	aceleracion*=-1/0.1;
}