#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

class World;

class GameObject
{
// Construction
public:
	GameObject(World *world) { this->world = world; }
	virtual ~GameObject(void) = 0;

// Attributes
public:
	
// Operations
public:
	virtual void draw() {};
	virtual bool update(float elapsed) { return false; }
	
protected:
	World *world;
};

#endif

