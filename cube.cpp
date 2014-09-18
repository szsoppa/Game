#include "cube.h" 

cube::cube() : Obiekt(0.0f, 0.0f, 0.0f)
{ 
	type = Cube;
}

cube::cube(int X, int Y, int Z) : Obiekt(X*CUBE_SIZE, Y*CUBE_SIZE, Z*CUBE_SIZE) 
{ 
	type = Cube;
}

double cube::getY(float x, float z)
{
	return 0.0;
}

void cube::draw(void) {
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
