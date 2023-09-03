#include "Hero.h"
#include "ExplosionEntity.h"
using namespace sf;
using namespace std;

Hero::Hero(int x, int y)
{
	if (!textureHero.loadFromFile("img/hero.png"))
	{
		cout << "Texture Hero introuvable";
	}

	invincible = false;
	nbrVie = 3;
	sp_rect = IntRect(0, 0, 64, 64);

	spriteHero.setTexture(textureHero);
	spriteHero.setPosition(x,y);
	spriteHero.setScale(.75,.75);
	spriteHero.setTextureRect(sp_rect);

	if (!font.loadFromFile("font/Gameplay.ttf")) { cout << "Font non charge"; };

	txtNbrVie.setPosition(150, 20);
	txtNbrVie.setCharacterSize(20);
	txtNbrVie.setFillColor(Color::White);
	txtNbrVie.setFont(font);

	txtNbrBomb.setPosition(350, 20);
	txtNbrBomb.setCharacterSize(20);
	txtNbrBomb.setFillColor(Color::White);
	txtNbrBomb.setFont(font);

	txtInstruction.setPosition(050, 64*9+20);
	txtInstruction.setCharacterSize(20);
	txtInstruction.setFillColor(Color::White);
	txtInstruction.setFont(font);
	txtInstruction.setString("Find the golden key and go to the exit. Use your bomb for explode breakable  wall");

	startBomb = 0;
	nbBomb = 0;
	range = 1;
	afficheVie();
	afficheNbrBomb();

	if (!bufferObjet.loadFromFile("audio/Object.wav")) { cout << "Son objet non charg�"; }
	objet.setBuffer(bufferObjet);

	if (!bufferKey.loadFromFile("audio/KeyFound.wav")) { cout << "Son keyFound non charg�"; }
	key.setBuffer(bufferKey);
}

void Hero::MoveTxt(string direction, int speed)
{
	int x = txtNbrVie.getPosition().x;
	if (direction == "Right")
	{
		txtNbrVie.setPosition(x + speed, 20);
		txtNbrBomb.setPosition((x+200) + speed, 20);
	}
	if(direction == "Left")
	{
		txtNbrVie.setPosition(x - speed, 20);
		txtNbrBomb.setPosition((x+200) - speed, 20);
	}
}

void Hero::PlayObjectSound()
{
	objet.play();
}

void Hero::PlayKeySound()
{
	key.play();
}

void Hero::move(int x, int y)
{
	spriteHero.move(x, y);
}

void Hero::setColor(Color uneCouleur)
{
	spriteHero.setColor(uneCouleur);
}

Sprite Hero::getSprite()
{
	return spriteHero;
}

int Hero::getVie()
{
	return nbrVie;
}

bool Hero::getInvincible()
{
	return invincible;
}

int Hero::GetRange()
{
	return range;
}

void Hero::setVie(int n)
{
	nbrVie = n;
}

void Hero::setInvincible(bool unBool)
{
	invincible = unBool;
}

void Hero::prendDegat()
{
	if (nbrVie>0){nbrVie--;}

	if (!bufferDegat.loadFromFile("audio/sonDegat.wav")){cout << "Son degat non charg�";}
	sonDegat.setBuffer(bufferDegat);
	sonDegat.play();

	setInvincible(true);
	setColor(Color(255, 255, 255, 128));
	afficheVie();
	timerinvincible.restart();
}

void Hero::afficheVie()
{
	txtNbrVie.setString("Number life : " + to_string(getVie()));
}

void Hero::AddBomb() {
	nbBomb++;
	afficheNbrBomb();
}

void Hero::RemoveBomb() {
	nbBomb--;
	afficheNbrBomb();
}

int Hero::getNbrBomb()
{
	return nbBomb;
}

void Hero::afficheNbrBomb()
{
	txtNbrBomb.setString("Extra bomb : " + to_string(getNbrBomb()));
}

double Hero::getXMin()
{
	return spriteHero.getPosition().x;
}

double Hero::getXMax()
{
	return spriteHero.getPosition().x + 64 -16;
}

double Hero::getYMin()
{
	return spriteHero.getPosition().y;
}

double Hero::getYMax()
{
	return spriteHero.getPosition().y + 64 - 16;
}

void Hero::anim(string direction)
{
	if (direction == "right")
	{
		sp_rect.top = sp_rect.height * 2;
		sp_rect.left = sp_rect.left + sp_rect.width;
		if (sp_rect.left > 2 * sp_rect.width) sp_rect.left = 0;
		spriteHero.setTextureRect(sp_rect);
	}
	if (direction == "left")
	{
		sp_rect.top = sp_rect.height * 1;
		sp_rect.left = sp_rect.left + sp_rect.width;
		if (sp_rect.left > 2 * sp_rect.width) sp_rect.left = 0;
		spriteHero.setTextureRect(sp_rect);
	}
	if (direction == "down")
	{
		sp_rect.top = sp_rect.height * 0;
		sp_rect.left = sp_rect.left + sp_rect.width;
		if (sp_rect.left > 2 * sp_rect.width) sp_rect.left = 0;
		spriteHero.setTextureRect(sp_rect);
	}
	if (direction == "up")
	{
		sp_rect.top = sp_rect.height * 3;
		sp_rect.left = sp_rect.left + sp_rect.width;
		if (sp_rect.left > 2 * sp_rect.width) sp_rect.left = 0;
		spriteHero.setTextureRect(sp_rect);
	}
	
}

void Hero::UpdateInvicible()
{
	if (timerinvincible.getElapsedTime().asSeconds() >= 3 && getInvincible() == true)
	{
		setInvincible(false);
		setColor(Color(255, 255, 255, 255));
	}
}

void Hero::CheckDamageBomb(ExplosionEntity ee)
{
	Vector2f positionf = spriteHero.getPosition();
	Vector2i position(positionf.x / 64, positionf.y / 64);

	if (position.y == ee.centerId.y)
	{
		if (position.x >= ee.centerId.x && position.x <= ee.centerId.x + ee.xRight)
		{
			if (getInvincible() == false)
			{
				prendDegat();
			}
			return;
		}
		if (position.x <= ee.centerId.x && position.x >= ee.centerId.x - ee.xLeft)
		{
			if (getInvincible() == false)
			{
				prendDegat();
			}
			return;
		}
	}

	if (position.x == ee.centerId.x)
	{
		if (position.y >= ee.centerId.y  && position.y <= ee.centerId.y + ee.yDown)
		{
			if (getInvincible() == false)
			{
				prendDegat();
			}
			return;
		}
		if (position.y <= ee.centerId.y && position.y >= ee.centerId.y - ee.yUp)
		{
			if (getInvincible() == false)
			{
				prendDegat();
			}
			return;
		}
	}
}

void Hero::IncreaseRange()
{
	range++;
}

void Hero::draw(RenderWindow& window)
{
	window.draw(spriteHero);
	window.draw(txtNbrVie);
	window.draw(txtNbrBomb);
	window.draw(txtInstruction);
}