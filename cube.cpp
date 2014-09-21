#include "cube.h" 

glm::mat4 V;

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

void wall() {
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,cubeSideVertex);
	glNormalPointer(GL_FLOAT,0,cubeSideNormal);
	glTexCoordPointer(2,GL_FLOAT,0,cubeTexCoord);
	glDrawArrays(GL_QUADS,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void cube::draw(void) {

 /*   glPushMatrix();
    glTranslatef(x, y, z);

    wall();
    glRotatef(90.f, 1.0f, 0.0f, 0.0f);

	wall();
    glRotatef(270.f, 1.0f, 0.0f, 0.0f);

	 wall();
    glRotatef(90.f, 0.0f, 1.0f, 0.0f);

	 wall();
    glRotatef(270.f, 0.0f, 1.0f, 0.0f);


   wall();

    glRotatef(180.f, 0.0f, 1.0f, 0.0f);
    wall();
     glPopMatrix();

	 */
	glLoadIdentity();
	glm::mat4 M;
	glLoadMatrixf(glm::value_ptr(V*M));
    glTranslatef(x, y, z);
    
	glPushMatrix();
	glRotatef(90.f, 1.0f, 0.0f, 0.0f);
	wall();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.f, 1.0f, 0.0f, 0.0f);	
	wall();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0.0f, 1.0f, 0.0f);
	wall();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.f, 0.0f, 1.0f, 0.0f);
	wall();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.f, 0.0f, 1.0f, 0.0f);
    wall();
	glPopMatrix();

	glPopMatrix();
	 }
