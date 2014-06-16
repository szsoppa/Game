#ifndef OBIEKT6_H
#define OBIEKT6_H

#include "obiekt.h" 

class Obiekt6 : public Obiekt
{
	public:
        Obiekt6();
        Obiekt6(float X, float Y, float Z);
        void draw(void);
		float getY(float y);
};

#endif 
