#include "ramp.h" 

ramp::ramp() : Obiekt(0.0f, 0.0f, 0.0f) 
{ 
	type = Ramp;
	direction[0] = -1;
	direction[1] = 0;
}

ramp::ramp(int X, int Y, int Z) : Obiekt(X*CUBE_SIZE, Y*CUBE_SIZE, Z*CUBE_SIZE) 
{ 
	type = Ramp;
	direction[0] = -1;
	direction[1] = 0;
}

double ramp::getY(float ox, float oz)
{
	int nx = (int)(ox / CUBE_SIZE);
	int nz = (int)(oz / CUBE_SIZE);
	float y = 0;
	if (direction[1] == 0)
	{
		if (direction[0] == 1)
		{
			y = CUBE_SIZE + (-1)*(ox - CUBE_SIZE * nx);	
		}
		if (direction[0] ==-1)
		{
			
			y = ox - CUBE_SIZE * nx;
		}
	}

	if (direction[0] == 0)
	{
		if (direction[1] == 1)
		{
			y = oz - CUBE_SIZE * nz;
		}
		if (direction[1] ==-1)
		{
			y = CUBE_SIZE + (-1)*(oz - CUBE_SIZE * nz);
		}
	}

	return y - CUBE_SIZE;
}

void ramp::side() {
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,rampMainVertex);
	glNormalPointer(GL_FLOAT,0,rampMainNormal);
	glTexCoordPointer(2,GL_FLOAT,0,rampMainCoord);
	glDrawArrays(GL_QUADS,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void leftside() {
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,rampLeftVertex);
	glNormalPointer(GL_FLOAT,0,rampLeftNormal);
	glTexCoordPointer(2,GL_FLOAT,0,rampLeftCoord);
	glDrawArrays(GL_TRIANGLES,0,3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void rightside() {
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,rampRightVertex);
	glNormalPointer(GL_FLOAT,0,rampRightNormal);
	glTexCoordPointer(2,GL_FLOAT,0,rampRightCoord);
	glDrawArrays(GL_TRIANGLES,0,3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ramp::draw(glm::mat4 ModelView) {
    
	glm::mat4 M;
	M = glm::translate(M, glm::vec3(x+2, y, z+2));
	M=ModelView*M;
	glLoadMatrixf(glm::value_ptr(M));

			if (direction[1] == 1)
			{
				glLoadMatrixf(glm::value_ptr(glm::rotate(M,180.0f,glm::vec3(0.0f, 1.0f, 0.0f))));
			}

			if (direction[0] == 1)
			{
				glLoadMatrixf(glm::value_ptr(glm::rotate(M,90.0f,glm::vec3(0.0f, 1.0f, 0.0f))));
			}

			if (direction[0] == -1)
			{
				glLoadMatrixf(glm::value_ptr(glm::rotate(M,270.0f,glm::vec3(0.0f, 1.0f, 0.0f))));
			}

		side();

		rightside();

		leftside();

}

