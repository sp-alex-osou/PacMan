#pragma once

#include "Character.h"

class Ghost : public Character
{
public:
	Ghost(World* world);
	virtual ~Ghost(void) = 0;

	virtual void draw();
	virtual bool update(float elapsed);

	const static int STATE_PURSUIT = 0;
	const static int STATE_PATROL = 1;
protected:
	void setEyes(CL_StringRef name);
	void patrol();

	CL_Sprite eyes;
	int state;
	
	int pursuitTime;
	int patrolTime;
	float elapsedTime;

	int pursuitSpeed;
	int patrolSpeed;
};

