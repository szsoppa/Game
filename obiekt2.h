#ifndef OBIEKT2_H
#define OBIEKT2_H

#include "obiekt.h" 

class Obiekt2 : public Obiekt
{
	public:
        Obiekt2();
        Obiekt2(float X, float Y, float Z);
        void draw(void);
		float getY(float y);
};

#endif 
