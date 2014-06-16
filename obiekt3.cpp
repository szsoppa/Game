#include "obiekt3.h" 

Obiekt3::Obiekt3() : Obiekt(0.0f, 0.0f, 0.0f) 
{ 
	typ = 3;
}

Obiekt3::Obiekt3(float X, float Y, float Z) : Obiekt(X, Y, Z) 
{ 
	typ = 3;
}

float Obiekt3::getY(float bx) 
{
	return y - bx + x;
}

void Obiekt3::draw(void) {
    glPushMatrix();
    glTranslatef(x, y, z);
    
    glCallList(10);
    
    glCallList(11);

    glPushMatrix();
    glRotatef(270.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();

    glCallList(12);

    glCallList(12);

    glPushMatrix();
    glRotatef(180.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();
    
    glPopMatrix();
}
