#pragma once

#include "Ghost.h"

class Bashful : public Ghost
{
public:
	Bashful(World* world);
protected:
	void arrivedAtField();
};

