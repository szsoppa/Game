#include "obiekt5.h" 

Obiekt5::Obiekt5() : Obiekt(0.0f, 0.0f, 0.0f) 
{ 
	typ = 5;
}

Obiekt5::Obiekt5(float X, float Y, float Z) : Obiekt(X, Y, Z) 
{ 
	typ = 5;
}

float Obiekt5::getY(float bx) 
{
	return y + bx - x;
}

void Obiekt5::draw(void) {
    glPushMatrix();
    glTranslatef(x, y, z);
        glCallList(16);
     
        glCallList(8);

        glCallList(16);
    
        glCallList(15);
   
        glCallList(16);
     
        glCallList(18);
    
    glPopMatrix();
}
