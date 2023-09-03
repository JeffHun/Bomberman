#include "Monstre.h"
#include "BlockType.h"
using namespace sf;
using namespace std;

Monstre::Monstre(int x, int y)
{
	if (!textureMonstre.loadFromFile("img/monstre.png"))
	{
		cout << "Texture Hero introuvable";
	}

	spriteMonstre.setTexture(textureMonstre);
	spriteMonstre.setPosition(x, y);

    posMonstreX = x/64;
    posMonstreY = y/64;
    posMonstreXLast = x/64;
    posMonstreYLast = y/64;
}

void Monstre::setPosition(int x, int y)
{
	spriteMonstre.setPosition(x, y);
}

Sprite Monstre::getSprite()
{
	return spriteMonstre;
}

void Monstre::draw(RenderWindow& window)
{
	window.draw(spriteMonstre);
}

double Monstre::getXMin()
{
	return spriteMonstre.getPosition().x;
}

double Monstre::getXMax()
{
	return spriteMonstre.getPosition().x + (double)textureMonstre.getSize().x - 16;
}

double Monstre::getYMin()
{
	return spriteMonstre.getPosition().y;
}

double Monstre::getYMax()
{
	return spriteMonstre.getPosition().y + (double)textureMonstre.getSize().y - 16;
}

void Monstre::move(Niveau niveau)
{
    vector<Vector2i>tabMoveMonstre;
    if (niveau.GetTypeBlockLevel(posMonstreX + 1, posMonstreY) == BlockType::Ground)
        tabMoveMonstre.push_back(Vector2i(posMonstreX + 1, posMonstreY));

    if (niveau.GetTypeBlockLevel(posMonstreX - 1, posMonstreY) == BlockType::Ground)
        tabMoveMonstre.push_back(Vector2i(posMonstreX - 1, posMonstreY));

    if (niveau.GetTypeBlockLevel(posMonstreX, posMonstreY - 1) == BlockType::Ground)
        tabMoveMonstre.push_back(Vector2i(posMonstreX, posMonstreY - 1));

    if (niveau.GetTypeBlockLevel(posMonstreX, posMonstreY + 1) == BlockType::Ground)
        tabMoveMonstre.push_back(Vector2i(posMonstreX, posMonstreY + 1));

    if (tabMoveMonstre.size() == 1)
    {
        posMonstreXLast = posMonstreX;
        posMonstreYLast = posMonstreY;
        setPosition(tabMoveMonstre[0].x * 64, tabMoveMonstre[0].y * 64);
        posMonstreX = tabMoveMonstre[0].x;
        posMonstreY = tabMoveMonstre[0].y;
    }
    else if (tabMoveMonstre.size() > 1)
    {
        for (int i = 0; i < tabMoveMonstre.size(); i++)
        {
            if (tabMoveMonstre[i].x == posMonstreXLast && tabMoveMonstre[i].y == posMonstreYLast)
            {
                tabMoveMonstre.erase(tabMoveMonstre.begin() + i);
            }
        }
        randDirection = rand() % tabMoveMonstre.size();
        posMonstreXLast = posMonstreX;
        posMonstreYLast = posMonstreY;
        setPosition(tabMoveMonstre[randDirection].x * 64, tabMoveMonstre[randDirection].y * 64);
        posMonstreX = tabMoveMonstre[randDirection].x;
        posMonstreY = tabMoveMonstre[randDirection].y;
    }
}