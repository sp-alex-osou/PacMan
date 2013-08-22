#include "Ghost.h"
#include "World.h"

Ghost::Ghost(World* world) : Character(world), state(STATE_PURSUIT), patrolTime(30), pursuitTime(30), elapsedTime(0)
{
	setEyes("Eyes");
	patrolSpeed = 70;
}

Ghost::~Ghost(void)
{
}

void Ghost::draw()
{
	Character::draw();
	drawSprite(eyes);

	drawTarget(body);
	drawTarget(eyes);
}

bool Ghost::update(float elapsed)
{
	// vergangene Zeit erhöhen
	elapsedTime += elapsed;

	// überprüfen, ob Zustand gewechselt werden muss
	if (state == STATE_PATROL && elapsedTime > patrolTime)
	{	
		state = STATE_PURSUIT; 
		elapsedTime -= patrolTime;
	}
	else if (state == STATE_PURSUIT && elapsedTime > pursuitTime)
	{ 
		state = STATE_PATROL; 
		elapsedTime -= pursuitTime; 
	}

	// Geschwindigkeit anhand des aktuellen Zustands festlegen
	speed = (state == STATE_PATROL) ? patrolSpeed : pursuitSpeed;

	// Augen auf Ziel-Feld ausrichten
	eyes.set_frame(targetDirection);

	return Character::update(elapsed);
}

// legt das Augen-Sprite des Geists fest
void Ghost::setEyes(CL_StringRef name)
{
	eyes = CL_Sprite(world->get_gc(), name, &world->resources);
}

// Patroulieren
void Ghost::patrol()
{
	// in Richtung des Startfeldes bewegen
	goTo(homeField);
}