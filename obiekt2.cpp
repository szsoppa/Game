#include "obiekt2.h" 

Obiekt2::Obiekt2() : Obiekt(0.0f, 0.0f, 0.0f) 
{ 
	typ = 2;
}

Obiekt2::Obiekt2(float X, float Y, float Z) : Obiekt(X, Y, Z) 
{ 
	typ = 2;
}

float Obiekt2::getY(float bx) 
{
	return y + bx - x;
}


void Obiekt2::draw(void) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glCallList(7);
    
    glCallList(8);

    glCallList(9);

    glPushMatrix();
    glRotatef(90.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();

    glCallList(9);

    glPushMatrix();
    glRotatef(180.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();

    glPopMatrix();
}
