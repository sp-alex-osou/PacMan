#include "Speedy.h"
#include "World.h"

Speedy::Speedy(World* world) : Ghost(world)
{
	setBody("Speedy");
	init(CL_Point(1, 1));
	pursuitSpeed = 135;
}

// siehe Character Klasse
void Speedy::arrivedAtField()
{
	if (state == STATE_PURSUIT)
		// zu Feld bewegen, das sich 4 Felder vor PacMan befindet
		goTo(world->getPacMan().getPosition() + getDirectionVector(world->getPacMan().getDirection()) * 4);
	else if (state == STATE_PATROL)
		patrol();
}
