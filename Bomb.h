#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace sf;
using namespace std;

class Bomb
{
private:
	Sprite spriteBomb;
	Texture textureBomb;

	Sprite spriteBombRed;
	Texture textureBombRed;

	Clock timerBomb;

	Vector2i indexPosition;

	bool isBonus = true;

	SoundBuffer bufferExplosion;
	Sound explosion;

	SoundBuffer bufferPlace;
	Sound place;

public:
	Bomb();
	void placeBomb(Vector2i&);
	bool update();
	void draw(RenderWindow &window);
	void SetAsNoBonus(bool unBool);
	bool IsBonus();
	Vector2i GetPosition();
	void ExplosionSound();
};

