#pragma once

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <stdio.h>
#include <fstream>

#include "cube.h"
#include "ramp.h"

using namespace std;

class Scena
{
private:
	TGAImg texture[1];
	GLuint tex[2];

	(Obiekt *) tab[20][20][4]; //plansza

	int LoadGLTextures(int index, char *Filename);

	
	double hangle;
	double dist;
	void calcCamera(void);

	double angle;

	bool wsp(int a, int b, int c); //sasiedztwa od planszy
	int checkIfRampPossible(int a, int b, int c); // od pochylni

	void rampDirection(int checkDirection, Obiekt *ramp);

	void generateRamps_1lvl();
	void generateCubes_1lvl();
	void generateRamps_2lvl();
	void generateCubes_2lvl();

	void generateRamps();
	void generateCubes();

	void generateFloor();

public:
	Scena(void);
	~Scena(void);
	void draw(glm::mat4 ModelView);
	void loadTexture(void);
	
	double cx, cy, cz; //punkt na ktory, patrzy kamera
	double ox, oy, oz; //pozycja obserwatora

	void addHangle(double h); // zmiana konta patrzenia kamery

	void generator(void); //generator planszy
	
	void step(int i);// przesuwa obserwatora o 1 krok
};
