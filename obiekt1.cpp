#include "obiekt1.h" 

Obiekt1::Obiekt1() : Obiekt(0.0f, 0.0f, 0.0f)
{ 
	typ = 1;
}

Obiekt1::Obiekt1(float X, float Y, float Z) : Obiekt(X, Y, Z) 
{ 
	typ = 1;
}

float Obiekt1::getY(float x, float z)
{
	return 0.0;
}

void Obiekt1::draw(void) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glPushMatrix();
    glRotatef(90.f, 1.0f, 0.0f, 0.0f);
    glCallList(1);
    glPopMatrix();
    glPushMatrix();
    glRotatef(270.f, 1.0f, 0.0f, 0.0f);
    glCallList(1);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();
    glPushMatrix();
    glRotatef(270.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();
    glCallList(1);
    glPushMatrix();
    glRotatef(180.f, 0.0f, 1.0f, 0.0f);
    glCallList(1);
    glPopMatrix();
    glPopMatrix();
}
