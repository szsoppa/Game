#ifndef OBIEKT_H
#define OBIEKT_H

#include <windows.h>
#include <gl/gl.h>
#include "global.h"

#define SIZE 2.0f

class Obiekt
{
	protected:
        float x, y, z;
        float dy;
        float ny;
        int wsp;
		bool fall;
        
    public:
		Obiekt();
		Obiekt(float X, float Y, float Z);
		void setPosition(float X, float Y, float Z);
		virtual void draw(void);
		
		void calc(void);

		objectType type;
		virtual double getY(float x, float z) { return 0; };

		int kierunek[2];
};

#endif
