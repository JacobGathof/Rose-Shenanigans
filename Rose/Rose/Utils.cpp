#include "Utils.h"



Vector2f Utils::toScreenCoordinates(float x, float y){
	return Vector2f(x*SCALEFACTOR / 64, y*SCALEFACTOR / 64);
}

Utils::Utils()
{
}


Utils::~Utils()
{
}
