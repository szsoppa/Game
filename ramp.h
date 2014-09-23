#ifndef ramp_H
#define ramp_H

#include "obiekt.h" 

class ramp : public Obiekt
{
	public:
        ramp();
        ramp(int X, int Y, int Z);
        void draw(glm::mat4 ModelView);
		void side();
		double getY(float x, float z);
};

#endif 
