#ifndef cube_H
#define cube_H

#include "obiekt.h" 

class cube : public Obiekt
{
	public:
        cube();
        cube(int X, int Y, int Z);
        void draw(glm::mat4 ModelView);
		void side();
		double getY(float x, float z);
};

#endif 
