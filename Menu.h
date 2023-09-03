#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
using namespace std;

using namespace sf;
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
private :
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text histoire;
	sf::Text resultat;

	SoundBuffer bufferMoveUI;
	Sound moveUI;

	Sprite controlS;
	Texture textureControl;

public :
	Menu(float width, float height);

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	void afficheHistoire(bool affiche);
	void afficheResultat(String unResultat);
};

