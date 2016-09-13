#include "Script.h"
#include <iostream>


bool Script::condition(){

	if (Vector2f::distance(source->position, target->position) <= 2.0f) {
		return true;
	}
	return false;
}

void Script::action()
{
	target->position = Vector2f(30, 30);
}

Script::Script(Object *s, Object *t)
{

	source = s;
	target = t;
}


Script::~Script()
{
}
