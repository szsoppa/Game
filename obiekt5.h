#ifndef OBIEKT5_H
#define OBIEKT5_H

#include "obiekt.h" 

class Obiekt5 : public Obiekt
{
	public:
        Obiekt5();
        Obiekt5(float X, float Y, float Z);
        void draw(void);
		float getY(float y);
};

#endif 
