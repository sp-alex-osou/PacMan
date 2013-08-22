#ifndef _WORLD_H_
#define _WORLD_H_

#include <list>

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "PacMan.h"
#include "Shadow.h"
#include "Pokey.h"
#include "Speedy.h"
#include "Bashful.h"
#include "Level.h"

class World
{
//Construction
public:
	World(CL_DisplayWindow &display_window);
	~World(void);

//Attributes
public:
	CL_ResourceManager resources;
	CL_GraphicContext get_gc() { return graphicContext; }
	Level& getLevel() const { return *level; }
	PacMan& getPacMan() const { return *pacMan; }
	Shadow& getShadow() const { return *shadow; }
	Pokey& getPokey() const { return *pokey; }
	Speedy& getSpeedy() const { return *speedy; }
	Bashful& getBashful() const { return *bashful; }
	std::list<Ghost*> getGhosts() const { return ghosts; }

//Operations
public:
	void run();

	void addObject(GameObject *object);

//Implementation
private:
	void draw();
	void update();

	float getElapsedTime();

	void onWindowClose();
	void onWindowResize(int width, int height);
	void onMouseDown(const CL_InputEvent &key, const CL_InputState &state);
	void onMouseMove(const CL_InputEvent &key, const CL_InputState &state);
	void onKeyDown(const CL_InputEvent &key, const CL_InputState &state);

	CL_DisplayWindow window;
	CL_GraphicContext graphicContext;

	std::list<GameObject*> objects;
	std::list<Ghost*> ghosts;

	PacMan* pacMan;
	Shadow* shadow;
	Pokey* pokey;
	Speedy* speedy;
	Bashful* bashful;
	Level* level;

	bool quit;
	bool pause;
};

#endif

