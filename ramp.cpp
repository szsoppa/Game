#include "ramp.h" 

ramp::ramp() : Obiekt(0.0f, 0.0f, 0.0f) 
{ 
	type = Ramp;
	kierunek[0] = -1;
	kierunek[1] = 0;
}

ramp::ramp(int X, int Y, int Z) : Obiekt(X*CUBE_SIZE, Y*CUBE_SIZE, Z*CUBE_SIZE) 
{ 
	type = Ramp;
	kierunek[0] = -1;
	kierunek[1] = 0;
}

double ramp::getY(float ox, float oz)
{
	int nx = (int)(ox / CUBE_SIZE);
	int nz = (int)(oz / CUBE_SIZE);
	float y = 0;
	if (kierunek[1] == 0)
	{
		if (kierunek[0] == 1)
		{
			y = CUBE_SIZE + (-1)*(ox - CUBE_SIZE * nx);	
		}
		if (kierunek[0] ==-1)
		{
			
			y = ox - CUBE_SIZE * nx;
		}
	}

	if (kierunek[0] == 0)
	{
		if (kierunek[1] == 1)
		{
			y = oz - CUBE_SIZE * nz;
		}
		if (kierunek[1] ==-1)
		{
			y = CUBE_SIZE + (-1)*(oz - CUBE_SIZE * nz);
		}
	}

	return y - CUBE_SIZE;
}

void ramp::draw(void) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glPushMatrix();
	if (kierunek[1] == 1)
	{
		glRotatef(180.0, 0.0, 1.0, 0.0);
	}

	if (kierunek[0] == 1)
	{
		glRotatef(90.0, 0.0, 1.0, 0.0);
	}

	if (kierunek[0] == -1)
	{
		glRotatef(270.0, 0.0, 1.0, 0.0);
	}

    glCallList(13);

    glPushMatrix();
    glRotatef(90.f, 1.0f, 0.0f, 0.0f);
    glCallList(1);
    glPopMatrix();

    glCallList(14);
    
    glCallList(15);

    glCallList(13);

    glPushMatrix();
    glRotatef(180.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();
    
    glPopMatrix();
}

