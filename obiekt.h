#ifndef OBIEKT_H
#define OBIEKT_H

#include <windows.h>
#include <gl/gl.h>
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
		
		void setWsp(int i);
		bool decWsp(int i);

		void startFall(float nz);
		void calc(void);

		int typ;
		virtual float getY(float x, float z) { return 0; };

		int kierunek[2];
};

#endif
