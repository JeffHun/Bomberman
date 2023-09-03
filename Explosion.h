#pragma once
#include <SFML/Graphics.hpp>
#include "ExplosionEntity.h"

class Explosion
{
private:
	sf::Clock clock;

	sf::Sprite s1;
	sf::Texture t1;

	sf::Sprite s2;
	sf::Texture t2;

	sf::Sprite s3;
	sf::Texture t3;

	int animState = 0;
	struct ExplosionEntity entity;



public:
	Explosion();

	void Explode(ExplosionEntity);
	bool Update();
	void draw(sf::RenderWindow& window);
};

