#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Level.h"
#include "World.h"

using std::string;
using std::istringstream;
using std::ifstream;
using std::map;
using std::pair;

Level::Level(World* world, string filename, CL_Rect viewPort) :GameObject(world), viewPort(viewPort)
{
	textures = map<char, CL_Texture>();

	CL_GraphicContext gc = world->get_gc();

	// Tile-Map initialisieren
	textures.insert(pair<char, CL_Texture>('1', CL_Texture("outerWallTop", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('2', CL_Texture("outerWallRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('3', CL_Texture("outerWallBottom", &world->resources,gc)));
	textures.insert(pair<char, CL_Texture>('4', CL_Texture("outerWallLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('5', CL_Texture("outerCornerTopLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('6', CL_Texture("outerCornerTopRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('7', CL_Texture("outerCornerBottomRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('8', CL_Texture("outerCornerBottomLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('(', CL_Texture("outerCornerNarrowTopLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>(')', CL_Texture("outerCornerNarrowTopRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('[', CL_Texture("outerCornerNarrowBottomLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>(']', CL_Texture("outerCornerNarrowBottomRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('>', CL_Texture("gateLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('<', CL_Texture("gateRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('-', CL_Texture("door", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('A', CL_Texture("wallTop", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('B', CL_Texture("wallRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('C', CL_Texture("wallBottom", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('D', CL_Texture("wallLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('E', CL_Texture("cornerTopLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('F', CL_Texture("cornerTopRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('G', CL_Texture("cornerBottomLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('H', CL_Texture("cornerBottomRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('a', CL_Texture("outerNoseTopLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('b', CL_Texture("outerNoseTopRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('c', CL_Texture("outerNoseRightTop", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('d', CL_Texture("outerNoseRightBottom", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('e', CL_Texture("outerNoseBottomLeft", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('f', CL_Texture("outerNoseBottomRight", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('g', CL_Texture("outerNoseLeftTop", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('h', CL_Texture("outerNoseLeftBottom", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('.', CL_Texture("dot", &world->resources, gc)));
	textures.insert(pair<char, CL_Texture>('*', CL_Texture("bigDot", &world->resources, gc)));

	initLevel(filename);
}

Level::~Level(void)
{
}

// Datei einlesen und Level erstellen
void Level::initLevel(string filename)
{
	ifstream iFile(filename);
	levelSize = CL_Sizex<int>(0, 0);
	levelFields = "";

	// wenn Datei geöffnet
	if(iFile.is_open())
	{
		string line;
		bool levelComplete = true;
		
		// solange Datei nicht am Ende
		while(iFile.good())
		{
			// wenn Level noch nicht vollständig geladen wurde
			if(!levelComplete || line.substr(0,8).compare("LEVEL_A=") == 0)
			{
				unsigned int firstDoubleQuote = line.find('"',0);
				unsigned int secondDoubleQuote = line.find('"', firstDoubleQuote+1);

				if(line.length() > secondDoubleQuote + 1)
					levelComplete = line.at(secondDoubleQuote + 1) == ';';

				if(levelSize.width == 0)
					levelSize.width = secondDoubleQuote - firstDoubleQuote - 1;

				levelSize.height++;

				levelFields += line.substr(firstDoubleQuote + 1, levelSize.width);
			}
			// PacMan Startposition X
			else if(line.substr(0,17).compare("LEVEL_A_PACMAN_X=") == 0)
			{
				istringstream isst;
				isst.str(line.substr(17));
				isst >> startPosition.x;
			}
			// PacMan Startposition Y
			else if(line.substr(0,17).compare("LEVEL_A_PACMAN_Y=") == 0)
			{
				istringstream isst;
				isst.str(line.substr(17));
				isst >> startPosition.y;
			}
			std::getline(iFile, line);
		}

		iFile.close();
	}

	fieldSize = CL_Sizex<float>(viewPort.get_width() / (float)levelSize.width, viewPort.get_height() / (float)levelSize.height); 
}

void Level::setViewPort(int width, int height)
{
	viewPort.set_width(width);
	viewPort.set_height(height);
	fieldSize.width = width / (float)levelSize.width;
	fieldSize.height = height / (float)levelSize.height;
}

// überprüft, ob angegebenes Feld frei ist
bool Level::isFreeField(const CL_Point& field) const
{
	char c = levelFields.at(levelSize.width * field.y + field.x);

	return c == ' ' || c == '.' || c == '*';
}

// einen Punkt "fressen"
void Level::takeDotOnField(const CL_Point& field)
{
	int position = levelSize.width * field.y + field.x;
	levelFields[position] = ' ';
}

void Level::draw()
{
	CL_Quadf textureQuad;
	CL_Rectf textureRectangle;
	CL_GraphicContext graphicContext;
	char field;

	graphicContext = world->get_gc();

	for(int i = 0; i < levelSize.width; ++i)
	{
		for(int j = 0; j < levelSize.height; ++j)
		{
			field = levelFields.at(j * levelSize.width + i);

			textureRectangle = CL_Rectf(i*fieldSize.width, j*fieldSize.height, fieldSize);
			textureQuad = CL_Quadf(textureRectangle);
			CL_Draw::texture(graphicContext, textures[field], textureQuad);
		}
	}
}

bool Level::update(float elapsed)
{
	return true;
}

// liefert Pixel-Koordinaten eines Feldes
CL_Pointf Level::getCoordinates(const CL_Point& field) const
{
	return CL_Pointf(field.x * fieldSize.width + fieldSize.width / 2, field.y * fieldSize.height + fieldSize.height / 2);
}

// liefert Level-Koordinaten eines Feldes
CL_Point Level::getIndices(const CL_Pointf& field) const
{
	return CL_Point((int)(field.x / fieldSize.width), (int)(field.y / fieldSize.height));
}