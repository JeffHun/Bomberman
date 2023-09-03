#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font/Gameplay.ttf")){}

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(64, 64);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Histoire");
	menu[1].setPosition(64, 64*2);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Quitter");
	menu[2].setPosition(64, 64*3);

	selectedItemIndex = 0;

	histoire.setFont(font);
	histoire.setFillColor(Color::White);
	histoire.setCharacterSize(20);
	histoire.setString("It's the story of a guy who\nwakes up naked in a cellar after a party.\nHe must find the key to get out\nof this place using the bomb\nand not die by the monsters.");
	histoire.setPosition(64 * 50, 64 * 4);

	resultat.setFont(font);
	resultat.setFillColor(Color::White);
	resultat.setString("Un resultat");
	resultat.setPosition(64*50,64*4);

	if (!bufferMoveUI.loadFromFile("audio/Ui.wav")) { cout << "Son ui non charg�"; }
	moveUI.setBuffer(bufferMoveUI);

	if (!textureControl.loadFromFile("img/Control.png"))
	{
		cout << "Texture control bonus introuvable";
	}
	controlS.setTexture(textureControl);

}

void Menu::afficheResultat(String unResultat)
{
	menu[0].setPosition(64 * 50, 64);
	menu[1].setPosition(64 * 50, 64);
	menu[2].setPosition(64 * 50, 64);
	histoire.setPosition(64*50, 64 * 4);
	resultat.setPosition(64, 64 * 4);
	resultat.setString(unResultat);
}

void Menu::afficheHistoire(bool affiche)
{
	if (affiche == true)
	{
		histoire.setPosition(64, 64 * 6);
		resultat.setPosition(64*50, 64 * 4);
	}
	else
	{
		histoire.setPosition(64*50, 64 * 6);
	}
}

void Menu::Draw(RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
	window.draw(controlS);
	window.draw(histoire);
	window.draw(resultat);
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >=0)
	{
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
		moveUI.play();
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 >= 0 && selectedItemIndex + 1 <= 2)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		moveUI.play();
	}
}