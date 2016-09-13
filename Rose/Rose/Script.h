#pragma once
#include "Object.h"
class Script
{
public:

	bool condition();
	void action();

	Object *source, *target;

	Script(Object * s, Object* t);
	~Script();

};

