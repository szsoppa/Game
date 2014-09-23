#include ".\scena.h"

#include <math.h>
#include <windows.h>
#include <fstream>

using namespace std;

const double pi = 3.1415 / 180.0;

Scena::Scena(void)
{

	hangle = 0.0; 
	calcCamera(); // ustawia pozycje kamery
	ox = oz = 0.0;
	oy = 3.0;
	for (int i = 0; i < SCENE_WIDTH; i++)
		for (int j = 0; j < SCENE_DEPTH; j++)
			for (int k = 0; k < SCENE_LEVELS; k++)
				tab[i][j][k] = NULL;
	generator();
}

Scena::~Scena(void)
{
	for (int i = 0; i < SCENE_WIDTH; i++)
		for (int j = 0; j < SCENE_DEPTH; j++)
			for (int k = 0; k < SCENE_LEVELS; k++)
				if (tab[i][j][k] != NULL) delete tab[i][j][k];
}


void Scena::draw(glm::mat4 ModelView)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glTranslated(2.0, 0.0, 2.0);
	for (int i = 0; i < SCENE_WIDTH; i++)
		for (int j = 0; j < SCENE_DEPTH; j++)
			for (int k = 0; k < SCENE_LEVELS; k++)
			{
				if (tab[i][j][k] != NULL)
					tab[i][j][k]->draw(ModelView);
			}
	glDisable(GL_TEXTURE_2D);
}

bool Scena::wsp(int a, int b, int c) // sprawdza, czy w sasiedztwie punktu a,b,c jest jakas cube
{
	if (tab[a-1][b-1][c] != NULL) return true;
	if (tab[a-1][b][c] != NULL) return true;
	if (tab[a-1][b+1][c] != NULL) return true;

	if (tab[a][b+1][c] != NULL) return true;
	if (tab[a][b-1][c] != NULL) return true;

	if (tab[a+1][b-1][c] != NULL) return true;
	if (tab[a+1][b][c] != NULL) return true;
	if (tab[a+1][b+1][c] != NULL) return true;
	return false;
}

int Scena::checkIfRampPossible(int a, int b, int c) // sprawdza, czy mozna pochylnie postawic
{
	int odp = 0;
	if (tab[a-1][b][c] != NULL) 
	{
		if ((tab[a-1][b][c]->type != Ramp)&&(tab[a-1][b][c+1] == NULL)&&(tab[a+1][b][c] == NULL))
		odp = 4;
		if (c > 1)
		if (tab[a-1][b][c-1]->type != Cube)
		odp = 0;
	}
	if (tab[a][b+1][c] != NULL) 
	{
		if ((tab[a][b+1][c]->type != Ramp)&&(tab[a][b+1][c+1] == NULL)&&(tab[a][b-1][c] == NULL))
		odp = 1;
		if (c > 1)
		if (tab[a][b+1][c-1]->type != Cube)
		odp = 0;
	}
	if (tab[a][b-1][c] != NULL)
	{
		if ((tab[a][b-1][c]->type != Ramp)&&(tab[a][b-1][c+1] == NULL)&&(tab[a][b+1][c] == NULL))
		odp = 3;
		if (c > 1)
		if (tab[a][b-1][c-1]->type != Cube)
		odp = 0;
	}
	if (tab[a+1][b][c] != NULL) 
	{
		if ((tab[a+1][b][c]->type != Ramp)&&(tab[a+1][b][c] == NULL)&&(tab[a-1][b][c] == NULL))
		odp = 2;
		if (c > 1)
		if (tab[a+1][b][c-1]->type != Cube)
		odp = 0;
	}
	return odp;
}

void Scena::generateCubes_1lvl(){
	for (int i = 0; i < CUBES_NUMBER_LEVEL1; i++) // randomly generate cubes at 1st level
	{
		int a = 1, b = 1;
		while ((tab[a][b][1] != NULL)||(!wsp(a,b,1)))
		{
			a = rand()%(SCENE_WIDTH-2) + 1;
			b = rand()%(SCENE_DEPTH-2) + 1;
		}
		tab[a][b][1] = new cube(a, 1, b);
	}
}

void Scena::generateCubes_2lvl(){
	for (int i = 0; i < CUBES_NUMBER_LEVEL2; i++) // randomly generate cubes at 2nd level
	{
		int a = 0, b = 0;
		while ((tab[a][b][2] != NULL)||(tab[a][b][1] == NULL)||(!wsp(a,b,2)))
		{
			a = rand()%20;
			b = rand()%20;
		}
		tab[a][b][2] = new cube(a, 2, b);
	}
}

void Scena::rampDirection(int checkDirection, Obiekt *ramp){
	
	switch(checkDirection){
		case 1:
				ramp->direction[0] = 0;
				ramp->direction[1] = 1;
				break;

		case 2:
				ramp->direction[0] = -1;
				ramp->direction[1] = 0;
				break;
				
		case 3:
				ramp->direction[0] = 0;
				ramp->direction[1] = -1;
				break;

		case 4:
				ramp->direction[0] = 1;
				ramp->direction[1] = 0;
				break;
	}
}

void Scena::generateRamps_1lvl(){
	for (int i = 0; i < RAMPS_NUMBER_LEVEL1; i++) // randomly generate ramps on 1st level
	{
		int a = 1, b = 1;
		while ((tab[a][b][3] != NULL)||(tab[a][b][2] != NULL)||(tab[a][b][1] != NULL)
			||(checkIfRampPossible(a, b, 1) == 0))
		{
			a = rand()%(SCENE_WIDTH-2) + 1;
			b = rand()%(SCENE_DEPTH-2) + 1;
		}
		tab[a][b][1] = new ramp(a, 1, b);
		rampDirection(checkIfRampPossible(a, b, 1), tab[a][b][1]);
	}
}

void Scena::generateRamps_2lvl(){
	for (int i = 0; i < RAMPS_NUMBER_LEVEL2; i++)
	{
		int a = 1, b = 1;
		while ((tab[a][b][1] == NULL)||(tab[a][b][1]->type != Cube)||(tab[a][b][2] != NULL)||(tab[a][b][3] != NULL)
			||(checkIfRampPossible(a, b, 2) == 0))
		{
			a = rand()%(SCENE_WIDTH-2) + 1;
			b = rand()%(SCENE_DEPTH-2) + 1;
		}
		tab[a][b][2] = new ramp(a, 2, b);
		rampDirection(checkIfRampPossible(a, b, 2), tab[a][b][2]);
	}
}

void Scena::generateCubes(){
	generateCubes_1lvl();
	generateCubes_2lvl();
}

void Scena::generateRamps(){
	generateRamps_1lvl();
	generateRamps_2lvl();
}

void Scena::generateFloor(){

	for (int x = 0; x < SCENE_WIDTH; x++) {
		for (int y = 0; y < SCENE_DEPTH; y++)
		{
			tab[x][y][0] = new cube(x,0,y);
		}
	}
}


void Scena::generator(void)
{
	generateFloor();
	tab[1][18][1] = new cube(1, 1, 18);
	tab[10][10][2] = new cube(10, 2, 10);
	generateCubes();
	generateRamps();
	
}

int Scena::LoadGLTextures(int index, char *Filename)
{
	if (texture[index].Load(Filename)==IMG_OK) {
  glGenTextures(1,&tex[index]); //Zainicjuj uchwyt tex
  glBindTexture(GL_TEXTURE_2D,tex[index]); //Przetwarzaj uchwyt tex
  if (texture[index].GetBPP()==24) //Obrazek 24bit
   glTexImage2D(GL_TEXTURE_2D,0,3,texture[index].GetWidth(),texture[index].GetHeight(),0,
    GL_RGB,GL_UNSIGNED_BYTE,texture[index].GetImg());
  else if (texture[index].GetBPP()==32) //Obrazek 32bit
   glTexImage2D(GL_TEXTURE_2D,0,4,texture[index].GetWidth(),texture[index].GetHeight(),0,
    GL_RGBA,GL_UNSIGNED_BYTE,texture[index].GetImg());
  else {
	  abort();
  }
  } else {
	  abort();
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  return TRUE;
}

void Scena::loadTexture(void) 
{
	LoadGLTextures(0, "mur.tga");
}

void Scena::step(int i)
{
	double tx, tz;
	double dox, doz;
	dist = 0.1;
    tx = dist * sin(hangle * pi);
	tz = dist * cos(hangle * pi);
	dox = ox + 2*(i * tx);
	doz = oz + 2*(i * tz);
	
	int nx = (int)(dox / CUBE_SIZE);
	int nz = (int)(doz / CUBE_SIZE);

	if ((dox >= 0) && (doz >=0) && (dox <= 80) && (doz <= 80))
	{
		if ((oy >= 3.0) && (oy < 6.5))
		{
			// on the floor, on ramp
			if ((tab[nx][nz][1]!= NULL)&&(tab[nx][nz][1]->type==Ramp))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}

			// on the floor, nothing ahead
			if (tab[nx][nz][1] == NULL)
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}
		}

		if ((oy >= 6.5) && (oy < 10.5))
		{
			// on 1st floor, on ramp
			if ((tab[nx][nz][2]!= NULL)&&(tab[nx][nz][2]->type==Ramp))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}

			// 1st floor, nothing ahead
			if ((tab[nx][nz][2] == NULL)&&(tab[nx][nz][1] != NULL))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}
		}

		if ((oy >= 10.5))
		{

			// 2nd floor, nothing ahead
			if ((tab[nx][nz][3] == NULL)&&(tab[nx][nz][2] != NULL))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}
		}
	}
	nx = (int)(ox / CUBE_SIZE);
	nz = (int)(oz / CUBE_SIZE);

	if (tab[nx][nz][3] != NULL) 
	{
		oy = 4*CUBE_SIZE-1 + tab[nx][nz][3]->getY(ox, oz);
	} else
	if (tab[nx][nz][2] != NULL) 
	{
		oy = 3*CUBE_SIZE-1 + tab[nx][nz][2]->getY(ox, oz);
	} else
	if (tab[nx][nz][1] != NULL) 
	{
		oy = 2*CUBE_SIZE-1 + tab[nx][nz][1]->getY(ox, oz);
	} else
		oy = CUBE_SIZE-1;

}

void Scena::calcCamera(void) 
{
    cz = sin(hangle * pi);
	cx =  cos(hangle * pi);
}


void Scena::addHangle(double h) 
{ 
	hangle+=h; 
	calcCamera(); 
};
