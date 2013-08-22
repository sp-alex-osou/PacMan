#pragma once

#include "Ghost.h"

class Pokey : public Ghost
{
public:
	Pokey(World* world);
protected:
	void arrivedAtField();
};

