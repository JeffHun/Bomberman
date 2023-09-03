#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "ExplosionEntity.h"
using namespace sf;
using namespace std;

class Hero
{
private:
	Sprite spriteHero;
	Texture textureHero;
	IntRect sp_rect;

	bool invincible;
	int nbrVie;
	bool dead;
	int startBomb;
	int nbBomb;
	int range;

	SoundBuffer bufferDegat;
	Sound sonDegat;

	SoundBuffer bufferObjet;
	Sound objet;

	SoundBuffer bufferKey;
	Sound key;

	Text txtNbrVie;
	Text txtNbrBomb;
	Text txtInstruction;
	Font font;

	Clock timerinvincible;

public:
	Hero(int x, int y);

	void move(int x, int y);
	void setColor(Color uneCouleur);
	
	void prendDegat();
	void afficheVie();
	void anim(string);
	void afficheNbrBomb();

	double getXMin();
	double getXMax();
	double getYMin();
	double getYMax();
	Sprite getSprite();
	int getVie();
	bool getInvincible();
	int getNbrBomb();
	int GetRange();
	void IncreaseRange();

	void AddBomb();
	void RemoveBomb();
	void setVie(int n);
	void setInvincible(bool unBool);
	void UpdateInvicible();
	void CheckDamageBomb(ExplosionEntity);

	void draw(RenderWindow &window);
	void PlayObjectSound();
	void PlayKeySound();

	void MoveTxt(string direction, int speed);
};

