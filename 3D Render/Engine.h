#pragma once
#include "support.h"

class RenderEngine {
public:
	static unsigned int projectLines(Line3D lines[], unsigned int nOfLines, Line2D transformedLines[], float fov);
	static int indeces[10];
};