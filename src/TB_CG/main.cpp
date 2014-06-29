#include "Util.h"

#include "Vehiculo.h"
#include "PlayerController.h"
#include "AIController.h"
#include "LTimer.h"
#include "Camera.h"
//#include "Texture.h"
#include "Mapa.h"

#define NOMBREMAPA "mapas/mapa1.txt"

const GLsizei windowWidth = 1280;
const GLsizei windowHeight = 720;

const GLsizei maxFPS = 60;
const GLsizei SCREEN_TICKS_PER_FRAME = 1000 / (maxFPS*2);

SDL_Window *mainWindow;
SDL_GLContext mainGLContext;

GLfloat camRotateX = 0.0f;//30.0f;
GLfloat camRotateY = 0.0f;

const Uint8 *keys = NULL;

//Texture *texture = NULL;

bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float mirarx = 0.0f;
float mirary = 0.0f;
float mirarz = 0.0f;

CVehiculo* playerVehiculo;
CPlayerController* playerController;
CVehiculo* aiVehiculo; //para hacer mas enemigo crear un vector de esta clase
CAIController* aiController; //para hacer mas enemigo crear un vector de esta clase
CCamera* camera;
CMapa* mapa;


GLvoid establishProjectionMatrix(GLsizei width, GLsizei height){
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
}

GLvoid initGL(GLsizei width, GLsizei height){
	establishProjectionMatrix(width, height);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	//especifica que caras dibujara primero | LEQUAL = Less or equal
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

	//texture = new Texture("data/asfalto.tga", "Textura asfalto");
	//texture = new Texture("data/surface2.tga", "Bottom texture");

	//glEnable(GL_LIGHT0);								// Turn on a light with defaults set
	//glEnable(GL_LIGHTING);								// Turn on lighting
	//glEnable(GL_COLOR_MATERIAL);

}

GLvoid displayFPS(GLvoid){
	static long lastTime = SDL_GetTicks();
	static long loops = 0;
	static GLfloat fps = 0.0f;

	int newTime = SDL_GetTicks();

	if (newTime - lastTime > 100){
		float newFPS = (float)loops / float(newTime - lastTime) * 1000.0f;

		fps = (fps + newFPS) / 2.0f;

		char title[80];
		sprintf_s(title, "OpenGL DEMO - %.2f", fps);

		SDL_SetWindowTitle(mainWindow, title);

		lastTime = newTime;

		loops = 0;
	}

	loops++;
}

GLvoid drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//camara
	camera->seguirA( playerVehiculo );

	playerVehiculo->dibujarVehiculo();
	aiVehiculo->dibujarVehiculo();

	////coordenadas rojo x, verde y, azul z
	//glBegin(GL_LINES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(5.0, 0.0, 0.0);

	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(0.0, 5.0, 0.0);

	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(0.0, 0.0, 5.0);
	//glEnd();

	//glTranslatef(0, -1.0f, 0.0f);

	//dibujar pista
	mapa->dibujarMapa();

	////crear pista (encontrar mejor manera)
	//glBegin(GL_QUADS);
	//glColor3f(0.9f, 0.8f, 0.0f);
	//glVertex3f(100.0f, 0.05f, -20.0f);
	//glVertex3f(-100.0f, 0.05f, -20.0f);
	//glVertex3f(-100.0f, 0.05f, -10.0f);
	//glVertex3f(100.0f, 0.05f, -10.0f);
	//
	//glEnd();

	////Empezar a usar textura de asfato
	////se resetea el color a estos valores para no afectar el color de la textura
	//glColor3f(1.0f, 1.0f, 1.0f);

	////se activan las texturas
	//glEnable(GL_TEXTURE_2D);
	////se elige que texturas se van a utilizar
	//glBindTexture(GL_TEXTURE_2D, texture->textures[0]->texID);

	////se elige el modo a dibujar
	//glBegin(GL_QUADS);
	////la escala para dibujar la textura (1 = textura al tamaño que es, >1 la textura se loopea el numero de veces que se ponga, <1 la textura aparece como si se le hiciera un zoom
	//int escala = 25;
	//for(int i = 0; i<6; i++){
	//	glTexCoord2f(1.0f * escala, 1.0f * escala); glVertex3f(  50.0f, 0.0f, -50.0f + (i*100));
	//	glTexCoord2f(0.0f, 1.0f * escala);			glVertex3f( -50.0f, 0.0f, -50.0f + (i*100));
	//	glTexCoord2f(0.0f, 0.0f);					glVertex3f( -50.0f, 0.0f,  50.0f + (i*100));
	//	glTexCoord2f(1.0f * escala, 0.0f);			glVertex3f(  50.0f, 0.0f,  50.0f + (i*100));
	//	if(i != 0){
	//		glTexCoord2f(1.0f * escala, 1.0f * escala); glVertex3f(  50.0f, 0.0f, -50.0f - (i*100));
	//		glTexCoord2f(0.0f, 1.0f * escala);			glVertex3f( -50.0f, 0.0f, -50.0f - (i*100));
	//		glTexCoord2f(0.0f, 0.0f);					glVertex3f( -50.0f, 0.0f,  50.0f - (i*100));
	//		glTexCoord2f(1.0f * escala, 0.0f);			glVertex3f(  50.0f, 0.0f,  50.0f - (i*100));
	//	}
	//}

	//for(int i = 0; i<6; i++){
	//	glTexCoord2f(1.0f * escala, 1.0f * escala); glVertex3f(  50.0f - (i*100), 0.0f, -50.0f-600);
	//	glTexCoord2f(0.0f, 1.0f * escala);			glVertex3f( -50.0f - (i*100), 0.0f, -50.0f-600 );
	//	glTexCoord2f(0.0f, 0.0f);					glVertex3f( -50.0f - (i*100), 0.0f,  50.0f-600);
	//	glTexCoord2f(1.0f * escala, 0.0f);			glVertex3f(  50.0f - (i*100), 0.0f,  50.0f-600);
	//}

	//for(int i = 0; i<7; i++){
	//	glTexCoord2f(1.0f * escala, 1.0f * escala); glVertex3f(  50.0f -600, 0.0f, -50.0f + (i*100));
	//	glTexCoord2f(0.0f, 1.0f * escala);			glVertex3f( -50.0f-600, 0.0f, -50.0f + (i*100));
	//	glTexCoord2f(0.0f, 0.0f);					glVertex3f( -50.0f-600, 0.0f,  50.0f + (i*100));
	//	glTexCoord2f(1.0f * escala, 0.0f);			glVertex3f(  50.0f-600, 0.0f,  50.0f + (i*100));
	//	if(i != 0){
	//		glTexCoord2f(1.0f * escala, 1.0f * escala); glVertex3f(  50.0f-600, 0.0f, -50.0f - (i*100));
	//		glTexCoord2f(0.0f, 1.0f * escala);			glVertex3f( -50.0f-600, 0.0f, -50.0f - (i*100));
	//		glTexCoord2f(0.0f, 0.0f);					glVertex3f( -50.0f-600, 0.0f,  50.0f - (i*100));
	//		glTexCoord2f(1.0f * escala, 0.0f);			glVertex3f(  50.0f-600, 0.0f,  50.0f - (i*100));
	//	}
	//}

	//for(int i = 0; i<7; i++){
	//	glTexCoord2f(1.0f * escala, 1.0f * escala); glVertex3f(  50.0f - (i*100), 0.0f, -50.0f+600);
	//	glTexCoord2f(0.0f, 1.0f * escala);			glVertex3f( -50.0f - (i*100), 0.0f, -50.0f+600 );
	//	glTexCoord2f(0.0f, 0.0f);					glVertex3f( -50.0f - (i*100), 0.0f,  50.0f+600);
	//	glTexCoord2f(1.0f * escala, 0.0f);			glVertex3f(  50.0f - (i*100), 0.0f,  50.0f+600);
	//}



	//glEnd();
	////se desactivan las texturas una vez que ya hayan sido usadas y dibujadas
	//glDisable(GL_TEXTURE_2D);

	/*glBegin(GL_QUADS);

	glColor3f(0.4f, 0.4f, 0.4f);

	for (int i = 1; i < 10; i++)
	{
		glVertex3f(50.0f, 0.05f, -20.0f - (50 * i));
		glVertex3f(-50.0f, 0.05f, -20.0f - (50 * i));
		glVertex3f(-50.0f, 0.05f, -10.0f - (50 * i));
		glVertex3f(50.0f, 0.05f, -10.0f - (50 * i));
	}

	for (int i = 1; i < 11; i++)
	{
		glVertex3f(50.0f, 0.05f, -20.0f + (50 * i));
		glVertex3f(-50.0f, 0.05f, -20.0f + (50 * i));
		glVertex3f(-50.0f, 0.05f, -10.0f + (50 * i));
		glVertex3f(50.0f, 0.05f, -10.0f + (50 * i));
	}
	glEnd();*/


	//creacion de ui experimental-----------------
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();        ----Not sure if I need this
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(10.0, 0.0);
	glVertex2f(10.0, 10.0);
	glVertex2f(0.0, 10.0);
	glEnd();

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();        ----and this?
	//--------------------------------------------

	glFlush();

	SDL_GL_SwapWindow(mainWindow);


	displayFPS();
	//printf("x = %.2f, y = %.2f, z = %.2f, vel = %.2f acel = %.2f, freno = %.2f\n", playerVehiculo->getx(), playerVehiculo->gety(), playerVehiculo->getz(), playerVehiculo->getvelocidad(), playerVehiculo->getaceleracion(), playerVehiculo->fFreno);
	//printf("vector direccion: x = %4.2f, y = %4.2f, z = %4.2f \n",playerVehiculo->vDireccion->x, playerVehiculo->vDireccion->y, playerVehiculo->vDireccion->z);
	//printf("x = %.2f z = %.2f z = %.2f \n", mirarx,mirary,mirarz);
}

GLboolean checkKeys(GLvoid){
	static long lastTime = SDL_GetTicks();

	const GLfloat speed = 1.0f;
	const long updateTime = 10;

	if (keys[SDL_SCANCODE_ESCAPE])
		return true;

	long newTime = SDL_GetTicks();

	/*if (newTime - lastTime > updateTime)
	{
		if (keys[SDL_SCANCODE_LEFT])
			cubeRotateY -= speed;
		if (keys[SDL_SCANCODE_RIGHT])
			cubeRotateY += speed;
		if (keys[SDL_SCANCODE_UP])
			cubeRotateX -= speed;
		if (keys[SDL_SCANCODE_DOWN])
			cubeRotateX += speed;
	}*/

	if (keys[SDL_SCANCODE_LEFT])
		playerController->moverVehiculo(3);
	if (keys[SDL_SCANCODE_RIGHT])
		playerController->moverVehiculo(1);
	if (keys[SDL_SCANCODE_UP])
		playerController->moverVehiculo(0);
	if (keys[SDL_SCANCODE_DOWN])
		playerController->moverVehiculo(2);

	if (keys[SDL_SCANCODE_SPACE])
		playerController->disparar();

	if (keys[SDL_SCANCODE_U])
		//mirarx += 0.1;
		aiController->moverVehiculo(0);
	if (keys[SDL_SCANCODE_J])
		//mirarx -= 0.1;
		aiController->moverVehiculo(2);
	if (keys[SDL_SCANCODE_H])
		//mirary += 0.1;
		aiController->moverVehiculo(3);
	if (keys[SDL_SCANCODE_K])
		//mirary -= 0.1;
		aiController->moverVehiculo(1);
	if (keys[SDL_SCANCODE_O])
		//mirarz += 0.1;
		camera->anguloCam += 1;
	if (keys[SDL_SCANCODE_L])
		//mirarz -= 0.1;
		camera->anguloCam -= 1;


	return false;
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s", SDL_GetError());
		exit(1);
	}

	if ((mainWindow = SDL_CreateWindow("My Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight,
		SDL_WINDOW_OPENGL)) == NULL)
	{
		fprintf(stderr, "Unable to to create OpenGL scene: %s", SDL_GetError());
		exit(2);
	}
	mainGLContext = SDL_GL_CreateContext(mainWindow);

	playerVehiculo = new CVehiculo();
	playerController = new CPlayerController();
	playerController->asignarVehiculo(playerVehiculo);

	aiVehiculo = new CVehiculo();
	aiController = new CAIController();
	aiController->asignarVehiculo(aiVehiculo);

	camera = new CCamera();

	mapa = new CMapa(NOMBREMAPA);

	initGL(windowWidth, windowHeight);
	playerVehiculo->setlargo(5);
	playerVehiculo->setancho(5);
	int done = 0;

	GLfloat x1 = 100.0f;
	GLfloat y1 = 150.0f;
	GLsizei rsize = 50;

	//The frames per second timer 
	LTimer fpsTimer; 
	//The frames per second cap timer 
	LTimer capTimer; 
	//Start counting frames per second 
	int countedFrames = 0; 
	fpsTimer.start();

	while (!done)
	{
		//Start cap timer 
		capTimer.start();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				done = 1;

			keys = SDL_GetKeyboardState(NULL);
		}

		if (checkKeys())
			done = 1;

		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f); 
		if (avgFPS > 2000000) { 
			avgFPS = 0; 
		}

		drawScene();
		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
	SDL_GL_DeleteContext(mainGLContext);
	SDL_DestroyWindow(mainWindow);

	SDL_Quit();

	return 1;
}

