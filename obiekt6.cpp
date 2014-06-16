#include "obiekt6.h" 

Obiekt6::Obiekt6() : Obiekt(0.0f, 0.0f, 0.0f) 
{ 
	typ = 6;
}

Obiekt6::Obiekt6(float X, float Y, float Z) : Obiekt(X, Y, Z) 
{ 
	typ = 6;
}

float Obiekt6::getY(float bx) 
{
	return y - bx + x;
}

void Obiekt6::draw(void) {
    glPushMatrix();
    glTranslatef(x, y, z);

        glCallList(17);
    
        glCallList(11);
   
        glCallList(14);
    
        glCallList(17);
    
        glCallList(17);
     
        glCallList(19);
    
    glPopMatrix();
}
