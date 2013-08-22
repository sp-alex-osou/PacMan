#pragma once

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "GameObject.h"

class Character : public GameObject
{
public:
	Character(World *world);
	virtual ~Character(void) = 0;

	virtual void draw();
	virtual bool update(float elapsed);

	void goTo(const CL_Point& field, bool force = false);

	CL_Point getPosition() const { return currentField; }
	int getDirection() const { return moveDirection; }
protected:
	CL_Point getNextField(int direction) const;
	CL_Vec2<int> getDirectionVector(int direction) const;

	void setBody(CL_StringRef name, int animationGroups = 1);
	void init(const CL_Point& field);
	void drawSprite(CL_Sprite& sprite);
	void drawTarget(CL_Sprite& sprite);

	virtual int getAnimationPos() const { return (int)animationPos; }
	virtual void arrivedAtField() {};

	CL_Point homeField;
	CL_Pointf position;
	CL_Point currentField;
	CL_Point fieldSize;
	CL_Point targetField;
	CL_Sprite body;
	int speed;
	int animationLength;
	float animationPos;
	float animationSpeed;
	int moveDirection;
	int newDirection;
	int targetDirection;
private:
	void move(float distance);
};