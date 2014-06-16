#ifndef OBIEKT3_H
#define OBIEKT3_H

#include "obiekt.h" 

class Obiekt3 : public Obiekt
{
	public:
        Obiekt3();
        Obiekt3(float X, float Y, float Z);
        void draw(void);
		float getY(float y);
};

#endif
