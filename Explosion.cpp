#include "Explosion.h"
#include <iostream>

Explosion::Explosion()
{
	if (t1.loadFromFile("img/explosionRange1.png"))
	{
		s3.setTexture(t1);
	}

	if (t2.loadFromFile("img/explosionRange2.png"))
	{
		s2.setTexture(t2);
	}

	if (t3.loadFromFile("img/explosionRange3.png"))
	{
		s1.setTexture(t3);
	}
}

void Explosion::Explode(ExplosionEntity EE)
{
	entity.centerId = EE.centerId;
	entity.xLeft = EE.xLeft;
	entity.xRight = EE.xRight;
	entity.yDown = EE.yDown;
	entity.yUp = EE.yUp;
	clock.restart();
}

bool Explosion::Update()
{
	float animation = clock.getElapsedTime().asSeconds();

	if (animation < 0.20f)
	{
		animState = 1;
	}
	else if (animation < 0.4f)
	{
		animState = 2;
	}
	else if (animation < 0.6f)
	{
		animState = 3;
	}
	else
	{
		return true;
	}
	return false;
}

void Explosion::draw(sf::RenderWindow& window)
{
	sf::Sprite* actualSprite;
	switch (animState)
	{
	case 1:
		actualSprite = &s1;
		break;
	case 2:
		actualSprite = &s2;
		break;
	case 3:
		actualSprite = &s3;
		break;
	default:
		actualSprite = &s1;
		break;
	}

	for (int i = 0; i < 4; i++)
	{
		int tempDistance;

		switch (i)
		{
			case 0:
				tempDistance = entity.xLeft;
				break;
			case 1:
				tempDistance = entity.xRight;
				break;
			case 2:
				tempDistance = entity.yUp;
				break;
			case 3:
				tempDistance = entity.yDown;
				break;
			default:
				tempDistance = entity.xLeft;
				break;
		}


		for (int j = 1; j <= tempDistance; j++)
		{
			if (i < 2)
			{
				actualSprite->setPosition((entity.centerId.x + ((i % 2 == 0)? -j : j)) * 64, entity.centerId.y * 64);
			}
			else
			{
				actualSprite->setPosition(entity.centerId.x * 64, (entity.centerId.y + ((i % 2 == 0) ? -j : j)) * 64);
			}
			window.draw(*actualSprite);
		}
	}

	actualSprite->setPosition(entity.centerId.x * 64, entity.centerId.y * 64);
	window.draw(*actualSprite);
}