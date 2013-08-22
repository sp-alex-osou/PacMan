#pragma once

#include "Character.h"

class PacMan : public Character
{
public:
	PacMan(World *world);
	void toggleAutoPilot() { autoPilot = !autoPilot; }
	void changeDirection(int direction);
protected:
	void draw();
	int getAnimationPos() const;
	void arrivedAtField();
	bool autoPilot;
private:
	bool isBetween(int i, int a, int b);
};

