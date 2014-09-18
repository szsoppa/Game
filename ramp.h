#ifndef ramp_H
#define ramp_H

#include "obiekt.h" 

class ramp : public Obiekt
{
	public:
        ramp();
        ramp(int X, int Y, int Z);
        void draw(void);
		double getY(float x, float z);
};

#endif 
