#include "Pokey.h"
#include "World.h"

Pokey::Pokey(World* world) : Ghost(world)
{
	setBody("Pokey");
	init(CL_Point(1, world->getLevel().getLevelSize().height - 2));
	pursuitSpeed = 100;
}

// siehe Character Klasse
void Pokey::arrivedAtField()
{
	if (state == STATE_PURSUIT)
	{
		PacMan& pacMan = world->getPacMan();

		// Entfernung zu PacMan berechnen
		CL_Vec2<int> delta = currentField - pacMan.getPosition();

		// wenn Entfernung größer als 8
		if (abs(delta.x) + abs(delta.y) > 8)
			// zu PacMan bewegen
			goTo(pacMan.getPosition());
		else
			// zum Startpunkt bewegen
			goTo(CL_Point(1, world->getLevel().getLevelSize().height - 2));
	}
	else if (state == STATE_PATROL)
		patrol();
}