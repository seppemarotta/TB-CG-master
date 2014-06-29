#include "Util.h"
#include "Mapa.h"

CMapa::CMapa(char* archivoMapa)
{
	mapa = NULL;
	filas = columnas = 0;
	
	_lectura(archivoMapa);

	texture = NULL;
	texture = new Texture("data/asfalto.tga", "Textura asfalto");

}

CMapa::~CMapa(void)
{
}

void CMapa::_lectura(char* archivoMapa){
	char letra;
	freopen(archivoMapa,"rt",stdin);

	scanf_s("%d %d%*c",&filas,&columnas); 

	mapa = new map();
	mapa->resize(filas);
	for(int i = 0; i < filas; i++)
		(*mapa)[i].resize(columnas);

	for(int i = 0; i<filas; i++)
	{
		for(int j = 0; j<columnas; j++)
		{
			if(j == columnas-1)
				scanf_s("%c%*c", &letra);
			else
				scanf_s("%c", &letra);

			(*mapa)[i][j].first = letra;
		}
	}
}

void CMapa::dibujarMapa()
{
	//se resetea el color a estos valores para no afectar el color de la textura
	glColor3f(1.0f, 1.0f, 1.0f);

	//se activan las texturas
	glEnable(GL_TEXTURE_2D);

	int escala = 10;
	for(int i = 0; i<filas; i++)
	{
		for(int j = 0; j<columnas; j++)
		{
			if( (*mapa)[i][j].first == PISO){
				//se elige que texturas se van a utilizar
				glBindTexture(GL_TEXTURE_2D, texture->textures[0]->texID);

				//se elige el modo a dibujar
				glBegin(GL_QUADS);
					glTexCoord2f(1.0f * escala, 1.0f * escala); glVertex3f(  25.0f+ (j*50), 0.0f, -25.0f + (i*50));
					glTexCoord2f(0.0f, 1.0f * escala);			glVertex3f( -25.0f+ (j*50), 0.0f, -25.0f + (i*50));
					glTexCoord2f(0.0f, 0.0f);					glVertex3f( -25.0f+ (j*50), 0.0f,  25.0f + (i*50));
					glTexCoord2f(1.0f * escala, 0.0f);			glVertex3f(  25.0f+ (j*50), 0.0f,  25.0f + (i*50));
				glEnd();
			}
		}
	}

}
