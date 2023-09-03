#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Niveau.h"
using namespace sf;
using namespace std;
class Monstre
{
private:
	Sprite spriteMonstre;
	Texture textureMonstre;
	int lastPosX;
	int lastPosY;

	int posMonstreX;
	int posMonstreY;
	int posMonstreXLast;
	int posMonstreYLast;
	int randDirection;

public:
	Monstre(int x, int y);

	void move(int x, int y);
	void setPosition(int x, int y);

	double getXMin();
	double getXMax();
	double getYMin();
	double getYMax();

	Sprite getSprite();
	void draw(RenderWindow &window);
	void move(Niveau niveau);
};

