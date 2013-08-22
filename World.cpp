#include "GameObject.h"
#include "World.h"
#include "PacMan.h"
#include "Shadow.h"
#include "Speedy.h"
#include "Bashful.h"
#include "Pokey.h"
#include "Level.h"

#include <list>

#include <ClanLib/core.h>
#include <ClanLib/display.h>

World::World(CL_DisplayWindow &displayWindow) : window(displayWindow), quit(false), pause(false)
{
	graphicContext = window.get_gc();

	// Resource Datei laden
	resources = CL_ResourceManager("resources.xml");

	// Level erstellen
	level = new Level(this, "Resources/Level.txt", window.get_viewport());

	// PacMan und Geister erstellen
	pacMan = new PacMan(this);
	shadow = new Shadow(this);
	pokey = new Pokey(this);
	speedy = new Speedy(this);
	bashful = new Bashful(this);

	// Geister in Liste einfügen
	ghosts.push_back(shadow);
	ghosts.push_back(speedy);
	ghosts.push_back(bashful);
	ghosts.push_back(pokey);

	// Level zur Welt hinzufügen
	addObject(level);

	// Geister zur Welt hinzufügen
	for (std::list<Ghost*>::iterator it = ghosts.begin(); it != ghosts.end(); ++it)
		addObject(*it);

	// PacMan zur Welt hinzufügen
	addObject(pacMan);
}

World::~World(void)
{
	// Löschen aller GameObjects
	std::list<GameObject*>::iterator it;
	for(it = objects.begin(); it != objects.end(); ++it)
		delete (*it);
}

// Hinzufügen eines GameObject zur Collection
void World::addObject(GameObject *object)
{
	objects.push_back(object);
}

// Programmschleife
void World::run()
{
	// Input Ereignisse einhängen
	CL_Slot slotQuit = window.sig_window_close().connect(this, &World::onWindowClose);
	CL_Slot slotKeyDown = window.get_ic().get_keyboard().sig_key_down().connect(this, &World::onKeyDown);

	//Bei Escape Schleife abbrechen und Programm beenden
	while (!window.get_ic().get_keyboard().get_keycode(CL_KEY_ESCAPE))
	{
		if (quit)
			break;

		update();
		draw();

		window.flip(1);
		CL_KeepAlive::process();
	}
}

//Updates ausführen
void World::update()
{	
	//Spiel vorbei
	//if (gameOver)
	//	return;

	//Vergangene Zeit berechnen
	float elapsed = getElapsedTime();

	if (pause)
		return;

	//Update aller GameObjects aufrufen
	std::list<GameObject *>::iterator it;
	for (it = objects.begin(); it != objects.end(); )
	{
		//Liefert ein Objekt "false" zurück, wird dieses gelöscht
		if (!(*it)->update(elapsed))
		{
			delete (*it);
			it = objects.erase(it);
		}
		else
			++it;
	}
}

// Zeichnen aller Komponenten
void World::draw()
{
	CL_Draw::fill(graphicContext, window.get_viewport(), CL_Colorf::black);

	std::list<GameObject *>::iterator it;
	for(it = objects.begin(); it != objects.end(); ++it)
		(*it)->draw();
}

// Vergangene Zeit berechnen
float World::getElapsedTime()
{
	static unsigned int lastTime = 0;

	unsigned int newTime = CL_System::get_time();

	if (lastTime == 0)
		lastTime = newTime;

	int deltaTime = (newTime - lastTime);

	lastTime = newTime;

	return deltaTime * 0.001f;
}

void World::onWindowClose()
{
	quit = true;
}

void World::onKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{
	switch (key.id)
	{
		case CL_KEY_W: case CL_KEY_UP:		pacMan->changeDirection(0); break;
		case CL_KEY_D: case CL_KEY_RIGHT:	pacMan->changeDirection(1); break;
		case CL_KEY_S: case CL_KEY_DOWN:		pacMan->changeDirection(2); break;
		case CL_KEY_A: case CL_KEY_LEFT:		pacMan->changeDirection(3); break;
		case CL_KEY_SPACE: pause = !pause;
		case CL_KEY_P: pacMan->toggleAutoPilot();
	}
}
