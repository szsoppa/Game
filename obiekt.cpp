#include "obiekt.h"

Obiekt::Obiekt()
{
	x = y = z = 0.0f;
	dy = 0.002f;
	fall = false;
	wsp = 1;
}

Obiekt::Obiekt(float X, float Y, float Z)
{
    x = X;
    y = Y;
    z = Z;
	dy = 0.005f;
	fall = false;
	wsp=1;
}

void Obiekt::setPosition(float X, float Y, float Z)
{
    x = X;
    y = Y;
    z = Z;
	dy = 0.005f;
}

void Obiekt::draw(glm::mat4 ModelView) { }

void Obiekt::side() { }


void Obiekt::calc(void)
{
	if (fall)
	{
		y -= dy;
		if (y <= ny ) 
		{
			y = ny;
			fall = false;
		}
	}
}
