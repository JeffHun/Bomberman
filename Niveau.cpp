#include "Niveau.h"
#include "BlockType.h"

using namespace sf;
using namespace std;

Niveau::Niveau(int unNbrBombDispo, int unNbrBonusRange, int modelMatrice[20][10])
{
	if (wallT.loadFromFile("img/mur.png"))
	{
		wallS.setTexture(wallT);
	}
	if (breakableT.loadFromFile("img/murCassable.png"))
	{
		breakableS.setTexture(breakableT);
	}
	if (groundT.loadFromFile("img/sol.png"))
	{
		groundS.setTexture(groundT);
	}
	if (!textureBombBonus.loadFromFile("img/bombBonus.png"))
	{
		cout << "Texture bomb bonus introuvable";
	}
	if (!textureRangeBonus.loadFromFile("img/rangeBonus.png"))
	{
		cout << "Texture range bonus introuvable";
	}

	for (int i =0; i<20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			levelMatrice[i][j] = modelMatrice[i][j];
		}
	}

	int nbrBombBonusArchive = unNbrBombDispo;
	nbrBombBonus = unNbrBombDispo;

	while (nbrBombBonus > 0)
	{
		nbrBombBonus--;
		Sprite uneBombBonnus;
		uneBombBonnus.setTexture(textureBombBonus);
		vectCollect.push_back(uneBombBonnus);
	}
	nbrBombBonus = nbrBombBonusArchive;


	int nbrRand;
	while (nbrBombBonus>0)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				nbrRand = rand()%10;
				if (nbrBombBonus > 0 && levelMatrice[i][j] == BlockType::Ground && nbrRand==1)
				{
					vectCollect[nbrBombBonus - 1].setPosition(64 * i, 64 * j);
					nbrBombBonus--;
				}
			}
		}
	}
	nbrBombBonus = nbrBombBonusArchive;

	int nbrBonusRangeArchive = unNbrBonusRange;
	nbrBonusRange = unNbrBonusRange;

	while (nbrBonusRange > 0)
	{
		nbrBonusRange--;
		Sprite unBonnusRange;
		unBonnusRange.setTexture(textureRangeBonus);
		vectCollectRange.push_back(unBonnusRange);
	}
	
	nbrBonusRange = nbrBonusRangeArchive;
	while (nbrBonusRange > 0)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				nbrRand = rand() % 10;
				if (nbrBonusRange > 0 && levelMatrice[i][j] == BlockType::Destroyable && nbrRand == 1)
				{
					vectCollectRange[nbrBonusRange - 1].setPosition(64 * i, 64 * j);
					nbrBonusRange--;
				}
			}
		}
	}

	nbrBonusRange = nbrBonusRangeArchive;

	if (keyT.loadFromFile("img/key.png")){keyS.setTexture(keyT);}
	bool keyActive = false;
	keyRecolted = false;
	while (keyActive == false)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				nbrRand = rand() % 10;
				if (levelMatrice[i][j] == BlockType::Destroyable && nbrRand == 1)
				{
					keyS.setPosition(64*i,64*j);
					keyActive = true;
				}
			}
		}
	}

	if (escapeT.loadFromFile("img/exit.png")) { escapeS.setTexture(escapeT); }
	bool escape = false;
	while (escape == false)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				nbrRand = rand() % 10;
				if (levelMatrice[i][j] == BlockType::Ground && nbrRand == 1)
				{
					escapeS.setPosition(64 * i, 64 * j);
					escape = true;
				}
			}
		}
	}

	if (!bufferAmbiance.loadFromFile("audio/Music.wav")) { cout << "Son ambiance non charg�"; }
	ambiance.setBuffer(bufferAmbiance);

	if (!bufferVictory.loadFromFile("audio/Victory.wav")) { cout << "Son victory non charg�"; }
	victory.setBuffer(bufferVictory);

	if (!bufferDeafeat.loadFromFile("audio/Defeat.wav")) { cout << "Son defeat non charg�"; }
	defeat.setBuffer(bufferDeafeat);

	ambiance.setLoop(true);
}

Sprite Niveau::getKey()
{
	return keyS;
}

void Niveau::setKeyRecolt(bool unBool)
{
	keyRecolted = unBool;
}

bool Niveau::getKeyRecolt()
{
	return keyRecolted;
}

void Niveau::setEscapeOpen(bool unBool)
{
	escape = unBool;
}

bool Niveau::getEscapeOpen()
{
	return escape;
}

Sprite Niveau::getEscape()
{
	return escapeS;
}

vector<Sprite> Niveau::getVectCollect()
{
	return vectCollect;
}

vector<Sprite> Niveau::getVectCollectRange()
{
	return vectCollectRange;
}

void Niveau::draw(RenderWindow &window)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (keyS.getPosition().x/64 == i && keyS.getPosition().y / 64 == j && levelMatrice[i][j] == BlockType::Destroyable)
			{
				window.draw(keyS);
			}
			for (int k = 0; k < vectCollectRange.size(); k++)
			{
				if (vectCollectRange[k].getPosition().x/64 == i && vectCollectRange[k].getPosition().y / 64 == j && levelMatrice[i][j] == BlockType::Destroyable)
				{
					window.draw(vectCollectRange[k]);
				}
			}
			switch (levelMatrice[i][j])
			{
				case BlockType::IndestructibleWall:
					wallS.setPosition(i * 64, j * 64);
					window.draw(wallS);
					break;
				case BlockType::Ground:
					groundS.setPosition(i * 64, j * 64);
					window.draw(groundS);
					break;
				case BlockType::Destroyable:
					breakableS.setPosition(i * 64, j * 64);
					window.draw(breakableS);
					break;
			}
			if (keyS.getPosition().x / 64 == i && keyS.getPosition().y / 64 == j && levelMatrice[i][j] == BlockType::Ground && getKeyRecolt() == false)
			{
				window.draw(keyS);
			}
			for (int k = 0; k < vectCollectRange.size(); k++)
			{
				if (vectCollectRange[k].getPosition().x / 64 == i && vectCollectRange[k].getPosition().y / 64 == j && levelMatrice[i][j] == BlockType::Ground)
				{
					window.draw(vectCollectRange[k]);
				}
			}
		}
	}
	if (getEscapeOpen() == true)
	{
		if (escapeT.loadFromFile("img/exitOpen.png")) { escapeS.setTexture(escapeT); }
	}
	window.draw(escapeS);
	for (int i = 0; i < vectCollect.size(); i++) window.draw(vectCollect[i]);
}

int Niveau::getNbrBonusRange()
{
	return nbrBonusRange;
}

int Niveau::getNbrBomb()
{
	return nbrBombBonus;
}

void Niveau::supBomb(int i)
{
	vectCollect[i].setPosition(-64,-64);
}

void Niveau::supBonusRange(int i)
{
	vectCollectRange[i].setPosition(-64, -64);
}

int Niveau::AskYUp(Vector2i position, int delta)
{
	if (levelMatrice[position.x][position.y - 1] == BlockType::IndestructibleWall)
	{
		return delta;
	}
	else if (levelMatrice[position.x][position.y - 1] == BlockType::Destroyable)
	{
		levelMatrice[position.x][position.y - 1] = BlockType::Ground;
		return delta - 1;
	}
	delta -= 1;
	if (delta == 0)
		return 0;

	position.y -= 1;
	return AskYUp(position, delta);
}

int Niveau::AskYDown(Vector2i position, int delta)
{
	if (levelMatrice[position.x][position.y + 1] == BlockType::IndestructibleWall)
	{
		return delta;
	}
	else if (levelMatrice[position.x][position.y + 1] == BlockType::Destroyable)
	{
		levelMatrice[position.x][position.y + 1] = BlockType::Ground;
		return delta - 1;
	}
	delta -= 1;
	if (delta == 0)
		return 0;

	position.y += 1;
	return AskYDown(position, delta);
}

int Niveau::AskXLeft(Vector2i position, int delta)
{
	if (levelMatrice[position.x - 1][position.y] == BlockType::IndestructibleWall)
	{
		return delta;
	}
	else if (levelMatrice[position.x - 1][position.y] == BlockType::Destroyable)
	{
		levelMatrice[position.x - 1][position.y] = BlockType::Ground;
		return delta - 1;
	}
	delta -= 1;
	if (delta == 0)
		return 0;

	position.x -= 1;
	return AskXLeft(position, delta);
}

int Niveau::AskXRight(Vector2i position, int delta)
{
	if (levelMatrice[position.x + 1][position.y] == BlockType::IndestructibleWall)
	{
		return delta;
	}
	else if (levelMatrice[position.x + 1][position.y] == BlockType::Destroyable)
	{
		levelMatrice[position.x + 1][position.y] = BlockType::Ground;
		return delta - 1;
	}
	delta -= 1;
	if (delta == 0)
		return 0;

	position.x += 1;
	return AskXRight(position, delta);
}

struct ExplosionEntity Niveau::GetExplosionEntity(Vector2i position, int range)
{
	ExplosionEntity entity;

	entity.centerId = position;
	entity.xRight = range - AskXRight(position, range);
	entity.xLeft = range - AskXLeft(position, range);
	entity.yUp = range - AskYUp(position, range);
	entity.yDown = range - AskYDown(position, range);
	

	return entity;
}

int Niveau::GetTypeBlockLevel(double x, double y)
{
	int xI = x / 64;
	int yI = y / 64;
	return levelMatrice[xI][yI];
}

int Niveau::GetTypeBlockLevel(int x, int y)
{
	return levelMatrice[x][y];
}

void Niveau::PlayMusic(bool music)
{
	if (music == true)
	{
		ambiance.play();
	}
	else
	{
		ambiance.stop();
	}
}

void Niveau::PlayMusicVictory(bool aVictory)
{
	if (aVictory == true)
	{
		victory.play();
	}
	else
	{
		defeat.play();
	}
}