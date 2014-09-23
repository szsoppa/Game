#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <gl\gl.h>			
#include <gl\glu.h>			
#include <gl\glaux.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tga.h"

#define SIZE 2.0f

#define SCENE_WIDTH 20
#define SCENE_DEPTH 20

#define SCENE_LEVELS 4

#define CUBE_SIZE 4.0

#define CUBES_NUMBER_LEVEL1 180
#define CUBES_NUMBER_LEVEL2 100

#define RAMPS_NUMBER_LEVEL1 20
#define RAMPS_NUMBER_LEVEL2 20
	
static float cubeSideVertex[12] = {
		-SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, -SIZE, SIZE,
		-SIZE, -SIZE, SIZE
	};
static float cubeSideNormal[12] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};
static float cubeTexCoord[8] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};
    
static float rampMainVertex[4][3] = {
		{-SIZE, SIZE, -SIZE},
		{SIZE, SIZE, -SIZE},
		{SIZE, -SIZE, SIZE},
		{-SIZE, -SIZE, SIZE}
	};
static float rampMainNormal[4][3] = {
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f}
	};

static float rampMainCoord[4][2] = {
		{0.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f}
	};

static float rampLeftVertex[3][3] = {
		{-SIZE, SIZE, -SIZE},
		{-SIZE, -SIZE, -SIZE},
		{-SIZE, -SIZE, SIZE}
	};

static float rampLeftNormal[3][3] = {
		{-1.0f, 1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f, 1.0f}
	};
static float rampLeftCoord[3][2] = {
		{0.0f, 1.0f},
		{1.0f, 1.0f},
		{1.0f, 0.0f}
	};

static float rampRightVertex[3][3] = {
		{SIZE, SIZE, -SIZE},
		{SIZE, -SIZE, -SIZE},
		{SIZE, -SIZE, SIZE}
	};
static float rampRightNormal[3][3] = {
		{1.0f, 1.0f, -1.0f},
		{1.0f, -1.0f, -1.0f},
		{1.0f, -1.0f, 1.0f}
	};
static float rampRightCoord[3][2] = {
		{1.0f, 1.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f}
	};


typedef enum objectType{
	Cube,
	Ramp
} objectType;

#endif