#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "ExplosionEntity.h"
#include "Niveau.h"
using namespace sf;
using namespace std;


class Niveau
{
private:
	int levelMatrice[20][10];
	
	Texture wallT;
	Sprite wallS;

	Texture keyT;
	Sprite keyS;

	Texture escapeT;
	Sprite escapeS;

	Texture groundT;
	Sprite groundS;

	Texture breakableT;
	Sprite breakableS;

	Texture textureRangeBonus;

	vector<Sprite> vectCollect;
	vector<Sprite> vectCollectRange;
	Texture textureBombBonus;
	int nbrBombBonus;
	int numeroNiveau;
	int nbrBonusRange;

	int AskYUp(Vector2i position, int delta);
	int AskYDown(Vector2i position, int delta);
	int AskXLeft(Vector2i position, int delta);
	int AskXRight(Vector2i position, int delta);

	bool keyRecolted;
	bool escape;

	SoundBuffer bufferAmbiance;
	Sound ambiance;

	SoundBuffer bufferVictory;
	Sound victory;

	SoundBuffer bufferDeafeat;
	Sound defeat;

public:
	Niveau(int unNbrBombBonus, int unNbrBonusRange, int uneMatrice[20][10]);
	void draw(RenderWindow &window);
	int getNbrBomb();
	vector<Sprite> getVectCollect();
	vector<Sprite> getVectCollectRange();
	void supBomb(int i);
	void supBonusRange(int i);
	struct ExplosionEntity GetExplosionEntity(Vector2i, int range);
	int GetTypeBlockLevel(double, double);
	int GetTypeBlockLevel(int, int);
	Sprite getKey();
	Sprite getEscape();
	void setKeyRecolt(bool unBool);
	bool getKeyRecolt();
	void setEscapeOpen(bool unbool);
	bool getEscapeOpen();
	int getNbrBonusRange();
	void PlayMusic(bool music);
	void PlayMusicVictory(bool victory);
};

