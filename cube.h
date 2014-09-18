#ifndef cube_H
#define cube_H

#include "obiekt.h" 

class cube : public Obiekt
{
	public:
        cube();
        cube(int X, int Y, int Z);
        void draw(void);
		double getY(float x, float z);
};

#endif 
