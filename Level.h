#pragma once

#include <string>

#include "GameObject.h"

using std::string;
using std::map;

class Level : public GameObject
{
public:
	Level(World* world, string filename, CL_Rect viewPort);
	~Level(void);

	void draw();
	bool update(float elapsed);

	void setViewPort(int width, int height);

	CL_Sizef getFieldSize() const { return fieldSize; };

	bool isFreeField(const CL_Point& field) const;
	void takeDotOnField(const CL_Point& field);

	CL_Pointf getCoordinates(const CL_Point& field) const;
	CL_Point getIndices(const CL_Pointf& field) const;
	CL_Point getStartPosition() const { return startPosition; }
	CL_Size getLevelSize() const { return levelSize; }
private:
	void initLevel(string filename);

	map<char, CL_Texture> textures;
	string levelFields;
	
	CL_Size levelSize;
	CL_Point startPosition;

	CL_Rect viewPort;
	CL_Sizef fieldSize;
};

