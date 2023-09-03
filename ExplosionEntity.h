#pragma once

typedef struct ExplosionEntity ExplosionEntity;

struct ExplosionEntity
{
public:
	int xRight;
	int xLeft;
	int yUp;
	int yDown;
	sf::Vector2i centerId;
};