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

void Obiekt::setWsp(int i) // ustawia wsp zniszczenia
{
    wsp = i;
}

bool Obiekt::decWsp(int i) // dekrementuje wsp zniszczenia
{
    if (!fall)
	{
		wsp -= i;
		if (wsp > 0) return false;
	} else return false;
	return true;
}

void Obiekt::draw(void) { }

void Obiekt::startFall(float az)
{
	fall = true;
	ny = az;
}

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
