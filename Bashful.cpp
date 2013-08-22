#include "Bashful.h"
#include "World.h"

Bashful::Bashful(World* world) : Ghost(world)
{
	setBody("Bashful");
	init(CL_Point(world->getLevel().getLevelSize().width - 2, world->getLevel().getLevelSize().height - 2));
	pursuitSpeed = 140;
}

// siehe Character Klasse
void Bashful::arrivedAtField()
{
	if (state == STATE_PURSUIT)
	{
		PacMan& pacMan = world->getPacMan();
		Shadow& shadow = world->getShadow();

		// zukünftige Position von PacMan berechnen
		CL_Point futurePacMan = pacMan.getPosition() + getDirectionVector(pacMan.getDirection()) * 2;

		// versuchen, PacMan den Weg abzuschneiden
		goTo(shadow.getPosition() + (futurePacMan - shadow.getPosition()) * 2);
	}
	else if (state == STATE_PATROL)
		patrol();
}