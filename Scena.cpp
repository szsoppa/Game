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
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			for (int k = 0; k < 4; k++)
				tab[i][j][k] = NULL;
	generator();
}

Scena::~Scena(void)
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			for (int k = 0; k < 4; k++)
				if (tab[i][j][k] != NULL) delete tab[i][j][k];
}


void Scena::draw(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(2.0, 0.0, 2.0);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			for (int k = 0; k < 4; k++)
			{
				if (tab[i][j][k] != NULL)
					tab[i][j][k]->draw();
			}
	glDisable(GL_TEXTURE_2D);
}

bool Scena::wsp(int a, int b, int c) // sprawdza, czy w sasiedztwie punktu a,b,c jest jakas kostka
{
	bool odp = false;
	if (tab[a-1][b-1][c] != NULL) odp = true;
	if (tab[a-1][b][c] != NULL) odp = true;
	if (tab[a-1][b+1][c] != NULL) odp = true;

	if (tab[a][b+1][c] != NULL) odp = true;
	if (tab[a][b-1][c] != NULL) odp = true;

	if (tab[a+1][b-1][c] != NULL) odp = true;
	if (tab[a+1][b][c] != NULL) odp = true;
	if (tab[a+1][b+1][c] != NULL) odp = true;
	return odp;
}

int Scena::wsp2(int a, int b, int c) // sprawdza, czy mozna pochylnie postawic
{
	int odp = 0;
	if (tab[a-1][b][c] != NULL) 
	{
		if ((tab[a-1][b][c]->typ != 4)&&(tab[a-1][b][c+1] == NULL)&&(tab[a+1][b][c] == NULL))
		odp = 4;
		if (c > 1)
		if (tab[a-1][b][c-1]->typ != 1)
		odp = 0;
	}
	if (tab[a][b+1][c] != NULL) 
	{
		if ((tab[a][b+1][c]->typ != 4)&&(tab[a][b+1][c+1] == NULL)&&(tab[a][b-1][c] == NULL))
		odp = 1;
		if (c > 1)
		if (tab[a][b+1][c-1]->typ != 1)
		odp = 0;
	}
	if (tab[a][b-1][c] != NULL)
	{
		if ((tab[a][b-1][c]->typ != 4)&&(tab[a][b-1][c+1] == NULL)&&(tab[a][b+1][c] == NULL))
		odp = 3;
		if (c > 1)
		if (tab[a][b-1][c-1]->typ != 1)
		odp = 0;
	}
	if (tab[a+1][b][c] != NULL) 
	{
		if ((tab[a+1][b][c]->typ != 4)&&(tab[a+1][b][c] == NULL)&&(tab[a-1][b][c] == NULL))
		odp = 2;
		if (c > 1)
		if (tab[a+1][b][c-1]->typ != 1)
		odp = 0;
	}
	return odp;
}

void Scena::generator(void)
{
	float x = 0;
	float y = 0;
	for (int i = 0; i < 20; i++) { //dol
		for (int j = 0; j < 20; j++)
		{
			tab[i][j][0] = new Obiekt1(x,0.0,y);
			x += 4.0;
		}
		y+=4.0;
		x=0.0;
	}

	tab[1][1][1] = new Obiekt1(1*4, 4, 1*4);
	tab[18][1][1] = new Obiekt1(18*4, 4, 1*4);
	tab[18][18][1] = new Obiekt1(18*4, 4, 18*4);
	tab[10][10][1] = new Obiekt1(10*4, 4, 10*4);
	tab[1][18][1] = new Obiekt1(1*4, 4, 18*4);
	for (int i = 0; i < 180; i++) // 180 na 1
	{
		int a = 13, b = 12;
		while ((tab[a][b][1] != NULL)||(!wsp(a,b,1)))
		{
			a = rand()%18 + 1;
			b = rand()%18 + 1;
		}
		tab[a][b][1] = new Obiekt1(a * 4, 4, b * 4);
	}
	tab[1][1][2] = new Obiekt1(1*4, 8, 1*4);
	tab[18][1][2] = new Obiekt1(18*4, 8, 1*4);
	tab[18][18][2] = new Obiekt1(18*4, 8, 18*4);
	tab[1][18][2] = new Obiekt1(1*4, 8, 18*4);
	tab[10][10][2] = new Obiekt1(10*4, 8, 10*4);
	for (int i = 0; i < 100; i++) // 100 na 2.
	{
		int a = 0, b = 0;
		while ((tab[a][b][2] != NULL)||(tab[a][b][1] == NULL)||(!wsp(a,b,2)))
		{
			a = rand()%20;
			b = rand()%20;
		}
		tab[a][b][2] = new Obiekt1(a * 4, 8, b * 4);
	}
	
	
	for (int i = 0; i < 40; i++) // pochylnie na poziomie 1.
	{
		int a = 0, b = 0;
		while ((tab[a][b][3] != NULL)||(tab[a][b][2] != NULL)||(tab[a][b][1] != NULL)
			||(wsp2(a, b, 1) == 0))
		{
			a = 1 + rand()%18;
			b = 1 + rand()%18;
		}
		int tmp = wsp2(a, b, 1);
		tab[a][b][1] = new Obiekt4(a * 4, 4, b * 4);
		if (tmp == 1)
		{
			tab[a][b][1]->kierunek[0] = 0;
			tab[a][b][1]->kierunek[1] = 1;
		}

		if (tmp == 4)
		{
			tab[a][b][1]->kierunek[0] = 1;
			tab[a][b][1]->kierunek[1] = 0;
		}

		if (tmp == 3)
		{
			tab[a][b][1]->kierunek[0] = 0;
			tab[a][b][1]->kierunek[1] = -1;
		}

		if (tmp == 2)
		{
			tab[a][b][1]->kierunek[0] = -1;
			tab[a][b][1]->kierunek[1] = 0;
		}
	}

	for (int i = 0; i < 20; i++) // pochylnie na poziomie 2.
	{
		int a = 0, b = 0;
		while ((tab[a][b][1] == NULL)||(tab[a][b][1]->typ != 1)||(tab[a][b][2] != NULL)||(tab[a][b][3] != NULL)
			||(wsp2(a, b, 2) == 0))
		{
			a = 1 + rand()%18;
			b = 1 + rand()%18;
		}
		int tmp = wsp2(a, b, 2);
		tab[a][b][2] = new Obiekt4(a * 4, 8, b * 4);
		if (tmp == 1)
		{
			tab[a][b][2]->kierunek[0] = 0;
			tab[a][b][2]->kierunek[1] = 1;
		}

		if (tmp == 4)
		{
			tab[a][b][2]->kierunek[0] = 1;
			tab[a][b][2]->kierunek[1] = 0;
		}

		if (tmp == 3)
		{
			tab[a][b][2]->kierunek[0] = 0;
			tab[a][b][2]->kierunek[1] = -1;
		}

		if (tmp == 2)
		{
			tab[a][b][2]->kierunek[0] = -1;
			tab[a][b][2]->kierunek[1] = 0;
		}
	}
}

AUX_RGBImageRec * Scena::LoadBMP(char *Filename)
{
	FILE *File=NULL;
	if (!Filename)
	{
		return NULL;
	}
	File=fopen(Filename,"r");
	if (File)
	{
		fclose(File);
		return auxDIBImageLoad(Filename);
	}
	return NULL;
}

int Scena::LoadGLTextures(int index, char *Filename)
{
	int Status=FALSE;
	AUX_RGBImageRec *TextureImage[1];
	memset(TextureImage,0,sizeof(void *)*1);
	if (TextureImage[0]=LoadBMP(Filename))
	{
		Status=TRUE;
		glGenTextures(1, &texture[index]);
		glBindTexture(GL_TEXTURE_2D, texture[index]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}
	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
	}
	return Status;	
}

void Scena::loadTexture(void) 
{
	LoadGLTextures(0, "mur.bmp");
}

void Scena::step(int i)
{
	double tx, tz;
	double dox, doz;
	dist = 0.25;
    tx = dist * sin(hangle * pi);
	tz = dist * cos(hangle * pi);
	dox = ox + 2*(i * tx);
	doz = oz + 2*(i * tz);
	
	int nx = (int)(dox / 4.0);
	int nz = (int)(doz / 4.0);

	if ((dox >= 0) && (doz >=0) && (dox <= 80) && (doz <= 80))
	{
		if ((oy >= 3.0) && (oy < 6.5))
		{
			// jest na 0 i jest przed nim pochylnia
			if ((tab[nx][nz][1]!= NULL)&&(tab[nx][nz][1]->typ==4))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}

			// jest na 0 i nie ma przed nim nic
			if (tab[nx][nz][1] == NULL)
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}
		}

		if ((oy >= 6.5) && (oy < 10.5))
		{
			// jest na 1 i jest przed nim pochylnia
			if ((tab[nx][nz][2]!= NULL)&&(tab[nx][nz][2]->typ==4))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}

			// jest na 1 i nie ma przed nim nic
			if ((tab[nx][nz][2] == NULL)&&(tab[nx][nz][1] != NULL))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}
		}

		if ((oy >= 10.5))
		{

			// jest na 2 i nie ma przed nim nic
			if ((tab[nx][nz][3] == NULL)&&(tab[nx][nz][2] != NULL))
			{
				ox = dox - (i * tx);
				oz = doz - (i * tz);
			}
		}
	}
	nx = (int)(ox / 4.0);
	nz = (int)(oz / 4.0);

	if (tab[nx][nz][3] != NULL) 
	{
		oy = 15.0 + tab[nx][nz][3]->getY(ox, oz);
	} else
	if (tab[nx][nz][2] != NULL) 
	{
		oy = 11.0 + tab[nx][nz][2]->getY(ox, oz);
	} else
	if (tab[nx][nz][1] != NULL) 
	{
		oy = 7.0 + + tab[nx][nz][1]->getY(ox, oz);
	} else
		oy = 3.0;

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
