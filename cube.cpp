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

void cube::side() {
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


void cube::draw(glm::mat4 ModelView) {

 /*   glPushMatrix();
    glTranslatef(x, y, z);

    side();
    glRotatef(90.f, 1.0f, 0.0f, 0.0f);

	side();
    glRotatef(270.f, 1.0f, 0.0f, 0.0f);

	 side();
    glRotatef(90.f, 0.0f, 1.0f, 0.0f);

	 side();
    glRotatef(270.f, 0.0f, 1.0f, 0.0f);


   side();

    glRotatef(180.f, 0.0f, 1.0f, 0.0f);
    side();
     glPopMatrix();

	 */
	//glLoadIdentity();
	//glm::mat4 M;
	//glLoadMatrixf(glm::value_ptr(V*M));

	glm::mat4 M;
	M = glm::translate(M, glm::vec3(x+2, y, z+2));
	M=ModelView*M;
	glLoadMatrixf(glm::value_ptr(M));

		glLoadMatrixf(glm::value_ptr(glm::rotate(M,90.f,glm::vec3(1.0f, 0.0f, 0.0f))));
		side();
	glLoadMatrixf(glm::value_ptr(M));

		glLoadMatrixf(glm::value_ptr(glm::rotate(M,270.f,glm::vec3(1.0f, 0.0f, 0.0f))));
		side();
	glLoadMatrixf(glm::value_ptr(M));
		glLoadMatrixf(glm::value_ptr(glm::rotate(M,90.f,glm::vec3( 0.0f, 1.0f, 0.0f))));
		side();
	glLoadMatrixf(glm::value_ptr(M));
		glLoadMatrixf(glm::value_ptr(glm::rotate(M,270.f,glm::vec3( 0.0f, 1.0f, 0.0f))));
		side();
	glLoadMatrixf(glm::value_ptr(M));
		glLoadMatrixf(glm::value_ptr(glm::rotate(M,180.f,glm::vec3( 0.0f, 1.0f, 0.0f))));
		side();
	glLoadMatrixf(glm::value_ptr(M));

		side();

		glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(ModelView));
}
