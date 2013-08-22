#include "PacMan.h"
#include "World.h"

PacMan::PacMan(World *world) : Character(world), autoPilot(false)
{
	setBody("PacMan", 4);
	speed = 150;

	init(world->getLevel().getStartPosition());
}

void PacMan::draw()
{
	Character::draw();
	
	if (autoPilot)
		drawTarget(body);
}

// liefert die aktuelle Animations-Position
int PacMan::getAnimationPos() const
{
	return moveDirection * animationLength + Character::getAnimationPos();
}

// siehe Character Klasse
void PacMan::arrivedAtField()
{
	// Punkt "fressen"
	world->getLevel().takeDotOnField(currentField);

	// wenn KI aktiviert
	if (autoPilot)
	{
		std::list<Ghost*> ghosts = world->getGhosts();

		CL_Size levelSize = world->getLevel().getLevelSize();

		// zum Mittelpunkt des Levels bewegen
		goTo(CL_Point(levelSize.width / 2, levelSize.height / 2));

		CL_Vec2<int> direction = getDirectionVector(newDirection);

		int minDistance = 3;
		Ghost* nextGhost = 0;

		// Geist ermitteln, der sich am nähesten befindet (maximal 3 Einheiten)
		for (std::list<Ghost*>::iterator it = ghosts.begin(); it != ghosts.end(); ++it)
		{
			Ghost& ghost = **it;

			int length = (ghost.getPosition() - currentField).length();

			if (length <= minDistance)
			{
				minDistance = length;
				nextGhost = &ghost;
			}
		}

		// wenn Geist in der Nähe, davonlaufen
		if (nextGhost != 0)
			goTo(currentField * 2 - nextGhost->getPosition(), true);
	}
}

// setzt die gewünschte Richtung
void PacMan::changeDirection(int direction)
{
	// abbrechen, wenn KI aktiviert
	if (autoPilot)
		return;

	newDirection = direction;

	// wenn gewünschte Richtung in Bewegungsrichtung oder entgegengesetzt
	if (abs(moveDirection - newDirection) == 2)
	{
		// aktuelle Bewegungsrichtung ändern
		currentField = getNextField(moveDirection);
		moveDirection = direction;
	}
}