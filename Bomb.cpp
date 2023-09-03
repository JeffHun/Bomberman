#include "Bomb.h"

Bomb::Bomb()
{
	if (!textureBomb.loadFromFile("img/bomb.png")){cout << "Texture bomb introuvable";}

	spriteBomb.setTexture(textureBomb);
	spriteBomb.setPosition(-64, -64);

    if (!textureBombRed.loadFromFile("img/bombRed.png")) { cout << "Texture bomb introuvable"; }

    if (!bufferExplosion.loadFromFile("audio/Explosion.wav")) { cout << "Son explosion non charg�"; }
    explosion.setBuffer(bufferExplosion);

    if (!bufferPlace.loadFromFile("audio/Place.wav")) { cout << "Son place non charg�"; }
    place.setBuffer(bufferPlace);
}

void Bomb::ExplosionSound()
{
    explosion.play();
}

void Bomb::placeBomb(Vector2i& positionIndex)
{
	spriteBomb.setPosition(positionIndex.x * 64, positionIndex.y * 64);
    timerBomb.restart();
    indexPosition = Vector2i(positionIndex);
    place.play();
}

bool Bomb::update()
{
    float elapsed = timerBomb.getElapsedTime().asSeconds();

    if (elapsed < 1.0)
    {
        spriteBomb.setTexture(textureBomb);
    }
    if (elapsed > 1.0 && elapsed < 2.0)
    {
        spriteBomb.setTexture(textureBombRed);
    }
    if (elapsed > 2.0 && elapsed < 3.0)
    {
        spriteBomb.setTexture(textureBomb);
    }
    if (elapsed > 3.0 && elapsed < 4)
    {
        spriteBomb.setTexture(textureBombRed);
    }
    if (elapsed > 4)
    {
        return true;
    }

    return false;
}

void Bomb::draw(RenderWindow &window)
{
	window.draw(spriteBomb);
}

void Bomb::SetAsNoBonus(bool unBool)
{
    isBonus = unBool;
}

bool Bomb::IsBonus()
{
    return isBonus;
}

Vector2i Bomb::GetPosition()
{
    return indexPosition;
}