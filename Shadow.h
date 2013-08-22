#pragma once

#include "Ghost.h"

class Shadow : public Ghost
{
public:
	Shadow(World* world);
protected:
	void arrivedAtField();
};

