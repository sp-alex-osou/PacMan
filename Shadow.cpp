#include "Shadow.h"
#include "World.h"

Shadow::Shadow(World *world) : Ghost(world)
{
	setBody("Shadow");
	init(CL_Point(world->getLevel().getLevelSize().width - 2, 1));
	pursuitSpeed = 130;
}

// siehe Character Klasse
void Shadow::arrivedAtField()
{
	if (state == STATE_PURSUIT)
		// zu PacMan bewegen
		goTo(world->getPacMan().getPosition());
	else if (state == STATE_PATROL)
		patrol();
}