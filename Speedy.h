#pragma once

#include "Ghost.h"

class Speedy :	public Ghost
{
public:
	Speedy(World* world);
protected:
	void arrivedAtField();
};

