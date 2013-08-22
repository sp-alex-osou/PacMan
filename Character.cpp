#include "Character.h"
#include "World.h"
#include "Level.h"

Character::Character(World *world) : GameObject(world), animationPos(0), animationSpeed(10.0f), moveDirection(1), newDirection(1)
{
}

Character::~Character(void)
{
}

// Character am Anfangsfeld initialisieren
void Character::init(const CL_Point& field)
{
	position = world->getLevel().getCoordinates(field);
	currentField = field;
	arrivedAtField();
	homeField = field;
}

void Character::draw()
{
	drawSprite(body);
}

// Sprite an aktueller Position zeichnen
void Character::drawSprite(CL_Sprite& sprite)
{
	sprite.draw(world->get_gc(), position.x - sprite.get_width() / 2, position.y - sprite.get_height() / 2);
}

// verkleinertes Sprite an Ziel-Position zeichnen
void Character::drawTarget(CL_Sprite& sprite)
{
	CL_Pointf position = world->getLevel().getCoordinates(targetField);

	sprite.set_scale(0.5f, 0.5f);
	sprite.draw(world->get_gc(), position.x - sprite.get_width() / 4, position.y - sprite.get_height() / 4);
	sprite.set_scale(1.0f, 1.0f);
}

// Position in aktueller Richtung um angegebene Distanz verändern
void Character::move(float distance)
{
	position += (CL_Vec2<float>)getDirectionVector(moveDirection) * distance;
}

bool Character::update(float elapsed)
{
	// zurückzulegende Distanz berechnen
	float distance = speed * elapsed;

	// aktuelle Animationsposition berechnen und setzen
	animationPos += elapsed * animationSpeed;

	while (animationPos >= animationLength)
		animationPos -= animationLength;

	body.set_frame(getAnimationPos());

	const Level& level = world->getLevel();

	// nächstes Feld in Bewegungsrichtung abrufen
	CL_Point nextField = getNextField(moveDirection);

	// wenn Richtung geändert werden soll und nächste Feld nicht frei ist
	if (moveDirection != newDirection && !level.isFreeField(nextField))
	{
		// Richtung ändern
		moveDirection = newDirection;

		// nächstes Feld in neuer Richtung abrufen
		nextField = getNextField(moveDirection);
	}

	CL_Pointf coordinates = level.getCoordinates(nextField);

	// Distanz zum Mittelpunkt des nächsten Feldes berechnen
	float distanceToField = abs(position.x - coordinates.x) + abs(position.y - coordinates.y);

	// solange nächstes Feld frei und zurückzulegende Distanz größer als Distanz zum Mittelpunkt
	while (level.isFreeField(nextField) && distance > distanceToField)
	{
		// zum Mittelpunkt des nächsten Feldes gehen
		move(distanceToField);

		// aktuelles Feld ändern
		currentField = nextField;

		// Benachrichtigung für Subklassen (zur Pfadfindung)
		arrivedAtField();

		// zurückzulegende Distanz verringern
		distance -= distanceToField;

		// wenn nächstes Feld in gewünschter Richtung
		if (level.isFreeField(getNextField(newDirection)))
			// zur gewünschten Richtung
			moveDirection = newDirection;

		// nächstes Feld abrufen
		nextField = getNextField(moveDirection);

		// Distanz zum nächsten Feld berechnen
		coordinates = level.getCoordinates(nextField);		
		distanceToField = abs(position.x - coordinates.x) + abs(position.y - coordinates.y);
	}

	// wenn nächstes Feld frei
	if (level.isFreeField(nextField))
		// Restdistanz in Bewegungsrichtung zurücklegen
		move(distance);

	return true;
}

// legt das Körper-Sprite des Characters fest
void Character::setBody(CL_StringRef name, int animationGroups)
{
	body = CL_Sprite(world->get_gc(), name, &world->resources);
	animationLength = body.get_frame_count() / animationGroups;
}

// liefert nächstes Feld in angegebener Richtung
CL_Point Character::getNextField(int direction) const
{
	return currentField + getDirectionVector(direction);
}

// liefert Vektor zur angegebenen Richtung
CL_Vec2<int> Character::getDirectionVector(int direction) const
{
	switch (direction)
	{
		case 0: return CL_Vec2<int>(0, -1); break;
		case 1: return CL_Vec2<int>(1, 0); break;
		case 2: return CL_Vec2<int>(0, 1); break;
		case 3: return CL_Vec2<int>(-1, 0); break;
	}

	return 0;
}

// bestimmt die Richtung anhand eines Ziel-Felds
void Character::goTo(const CL_Point& field, bool force)
{
	// Abstand zum Ziel berechnen
	CL_Vec2<int> delta = currentField - field;
	CL_Vec2<int> direction;

	// Richtungen in x und y Richtung bestimmen
	direction.x = (delta.x != 0) ? 2 + delta.x / abs(delta.x) : 1;
	direction.y = (delta.y != 0) ? 1 - delta.y / abs(delta.y) : 0;

	// Richtung mit der größeren Entfernung wählen
	targetDirection = (abs(delta.x) > abs(delta.y)) ? direction.x : direction.y;
	targetField = field;
	newDirection = targetDirection;

	// umliegende Felder abrufen
	CL_Point moveField = getNextField(moveDirection);
	CL_Point rightField = getNextField((moveDirection + 1) % 4);
	CL_Point leftField = getNextField((moveDirection - 1) % 4);

	const Level& level = world->getLevel();

	// wenn umliegende Felder (vorne, links, rechts) nicht frei
	if (!level.isFreeField(moveField) && !level.isFreeField(leftField) && !level.isFreeField(rightField))
		// umdrehen
		newDirection = (moveDirection + 2) % 4;
	// wenn Feld in gewünschter Richtung nicht frei
	else if (!level.isFreeField(getNextField(newDirection)) || (abs(newDirection - moveDirection) == 2 && !force))
	{
		// Richtung mit der kleineren Entfernung wählen
		newDirection = (newDirection == direction.x) ? direction.y : direction.x;

		// solange Feld in gewünschter Richtung nicht frei
		while (!level.isFreeField(getNextField(newDirection)) || (abs(newDirection - moveDirection) == 2 && !force))
			// im Uhrzeigersinn drehen
			newDirection = (newDirection + 1) % 4;
	}
}