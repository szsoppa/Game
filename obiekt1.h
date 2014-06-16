#ifndef OBIEKT1_H
#define OBIEKT1_H

#include "obiekt.h" 

class Obiekt1 : public Obiekt
{
	public:
        Obiekt1();
        Obiekt1(float X, float Y, float Z);
        void draw(void);
		float getY(float x, float z);
};

#endif 
