#ifndef OBIEKT4_H
#define OBIEKT4_H

#include "obiekt.h" 

class Obiekt4 : public Obiekt
{
	public:
        Obiekt4();
        Obiekt4(float X, float Y, float Z);
        void draw(void);
		float getY(float x, float z);
};

#endif 
