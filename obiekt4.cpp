#include "obiekt4.h" 

Obiekt4::Obiekt4() : Obiekt(0.0f, 0.0f, 0.0f) 
{ 
	typ = 4;
	kierunek[0] = -1;
	kierunek[1] = 0;
}

Obiekt4::Obiekt4(float X, float Y, float Z) : Obiekt(X, Y, Z) 
{ 
	typ = 4;
	kierunek[0] = -1;
	kierunek[1] = 0;
}

float Obiekt4::getY(float ox, float oz)
{
	int nx = (int)(ox / 4.0);
	int nz = (int)(oz / 4.0);
	float y = 0;
	if (kierunek[1] == 0)
	{
		if (kierunek[0] == 1)
		{
			y = 4.0 + (-1)*(ox - 4.0 * nx);	
		}
		if (kierunek[0] ==-1)
		{
			
			y = ox - 4.0 * nx;
		}
	}

	if (kierunek[0] == 0)
	{
		if (kierunek[1] == 1)
		{
			y = oz - 4.0 * nz;
		}
		if (kierunek[1] ==-1)
		{
			y = 4.0 + (-1)*(oz - 4.0 * nz);
		}
	}

	return y - 4.0;
}

void Obiekt4::draw(void) {
    glPushMatrix();
    glTranslatef(x, y, z);
    //glPushMatrix();
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

