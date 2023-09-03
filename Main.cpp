#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Hero.h"
#include "Monstre.h"
#include "Niveau.h"
#include "Bomb.h"
#include "Explosion.h"
#include "BlockType.h"
#include "Menu.h"

using namespace sf;
using namespace std;

bool perdu = true;

bool unMenu = true;

int deplacement = 4;

vector<Bomb*>poolBombs;
vector<Bomb*>activeBombs;
vector<Bomb*>noBonusBombs;

vector<Monstre> poolMonstre;

vector<Explosion*>poolExplosions;
vector<Explosion*>activeExplosions;

bool spaceBefore = false;
bool spaceCurrent = false;

bool soundVictory = true;
bool soundKey= true;

int level[20][10] =
{
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,2,1,1,1,1,0},
    {0,1,0,2,2,1,1,0,2,0},
    {0,1,1,1,2,1,1,2,1,0},
    {0,1,2,2,2,2,2,2,1,0},
    {0,2,2,1,1,1,1,2,1,0},
    {0,1,2,2,2,1,1,2,1,0},
    {0,1,0,1,2,1,2,0,1,0},
    {0,1,2,1,1,1,2,1,1,0},
    {0,1,2,2,1,1,1,2,2,0},
    {0,1,1,2,1,1,2,2,1,0},
    {0,2,2,2,2,2,2,1,1,0},
    {0,1,0,2,1,1,1,0,1,0},
    {0,1,1,2,1,2,2,2,2,0},
    {0,1,1,2,1,2,1,1,1,0},
    {0,2,2,2,2,2,1,1,1,0},
    {0,1,1,2,1,2,1,1,1,0},
    {0,1,0,2,1,2,2,0,1,0},
    {0,1,2,1,1,2,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0},
};

int getElementPixel(Niveau& niveau, double x, double y)
{
    return niveau.GetTypeBlockLevel(x, y);
}

int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(640, 640), "Bomberman");
    View view;
    view.setCenter(sf::Vector2f(320, 320));
    view.setSize(sf::Vector2f(640, 640));


    Sprite credit;
    Sprite joke;
    Texture textureCredit;
    Texture textureJoke;
    if (!textureCredit.loadFromFile("img/credit.jpg")) { cout << "Texture credit introuvable"; }
    if (!textureJoke.loadFromFile("img/joke.jpg")) { cout << "Texture joke introuvable"; }
    credit.setTexture(textureCredit);
    credit.setPosition(-64 * 4, 0);
    joke.setTexture(textureJoke);
    joke.setPosition(64 * 20, 0);

    int nbrBombBonus = 6;
    int nbrBonusRange = 3;
    int nbrMonstre = 4;

    Niveau niveau(nbrBombBonus, nbrBonusRange, level);
    Hero hero(64*5,64*4);
    Monstre monstre1(64,64);
    Monstre monstre2(64*3, 64*5);
    Monstre monstre3(64*6, 64*8);
    Monstre monstre4(64*9, 64*2);
    Menu menu(window.getSize().x, window.getSize().y);

    niveau.PlayMusic(true);
    
    poolMonstre.push_back(monstre1);
    poolMonstre.push_back(monstre2);
    poolMonstre.push_back(monstre3);
    poolMonstre.push_back(monstre4);

    for (int i = 0; i < nbrBombBonus; i++)
    {
        Bomb* bomb = new Bomb();

        if (i == 0)
            continue;

        poolBombs.push_back(bomb);

        Explosion* explosion = new Explosion();
        poolExplosions.push_back(explosion);
    }

    Bomb* bomb = new Bomb();
    bomb->SetAsNoBonus(false);
    noBonusBombs.push_back(bomb);

    Clock timerMonstre;

    while (window.isOpen())
    {
        if (unMenu == false)
        {
            if (timerMonstre.getElapsedTime().asSeconds() >= 1)
            {
                for (int i = 0; i < poolMonstre.size(); i++)
                {
                    poolMonstre[i].move(niveau);
                }
                timerMonstre.restart();
            }

            for (int i = 0; i < poolMonstre.size(); i++)
            {
                if(hero.getSprite().getGlobalBounds().intersects(poolMonstre[i].getSprite().getGlobalBounds()))
                {
                    if (hero.getInvincible() == false)
                    {
                        hero.prendDegat();
                    }
                    if (perdu == false && hero.getVie() == 0)
                    {
                        perdu = true;
                    }
                }
            }
        }

        hero.UpdateInvicible();

        if (round(hero.getSprite().getPosition().x / 64) == round(niveau.getKey().getPosition().x / 64) && round(hero.getSprite().getPosition().y / 64) == round(niveau.getKey().getPosition().y / 64))
        {
            niveau.setKeyRecolt(true);
            niveau.setEscapeOpen(true);
            if (soundKey == true)
            {
                hero.PlayKeySound();
                soundKey = false;
            }
        }

        for (int i = 0; i < niveau.getNbrBonusRange(); i++)
        {
            if (hero.getSprite().getGlobalBounds().intersects(niveau.getVectCollectRange()[i].getGlobalBounds()))
            {
                niveau.supBonusRange(i);
                hero.IncreaseRange();
                hero.PlayObjectSound();
            }
        }

        if (round(hero.getSprite().getPosition().x / 64) == round(niveau.getEscape().getPosition().x / 64) && round(hero.getSprite().getPosition().y / 64) == round(niveau.getEscape().getPosition().y / 64) && niveau.getKeyRecolt() == true)
        {
            unMenu = true;
            menu.afficheResultat("You won !! Congratulations :D\n\nNow go put your pants on! !");
            if (soundVictory == true)
            {
                niveau.PlayMusic(false);
                niveau.PlayMusicVictory(true);
                soundVictory = false;
            }
        }

        if (hero.getVie() <= 0)
        {
            unMenu = true;
            menu.afficheResultat("You lost D:\n\nIt's a shame to die naked !");
            if (soundVictory == true)
            {
                niveau.PlayMusic(false);
                niveau.PlayMusicVictory(false);
                soundVictory = false;
            }
        }

        for (int i=0; i<niveau.getNbrBomb();i++)
        {
            if (hero.getSprite().getGlobalBounds().intersects(niveau.getVectCollect()[i].getGlobalBounds()))
            {
                niveau.supBomb(i);
                hero.AddBomb();
                hero.PlayObjectSound();
            }
        }

        spaceBefore = spaceCurrent;
        spaceCurrent = false;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                while(poolBombs.size() > 0)
                {
                    Bomb* tempBomb = poolBombs[(poolBombs.size() - 1)];
                    poolBombs.pop_back();
                    free(tempBomb);
                }

                while (activeBombs.size() > 0)
                {
                    Bomb* tempBomb = activeBombs[(activeBombs.size() - 1)];
                    activeBombs.pop_back();
                    free(tempBomb);
                }

                while (poolExplosions.size() > 0)
                {
                    Explosion* tempEpl = poolExplosions[(poolExplosions.size() - 1)];
                    poolExplosions.pop_back();
                    free(tempEpl);
                }

                while (activeExplosions.size() > 0)
                {
                    Explosion* tempEpl = activeExplosions[(activeExplosions.size() - 1)];
                    activeExplosions.pop_back();
                    free(tempEpl);
                }

                window.close();
            }

            if (unMenu == true)
            {
                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            unMenu = false;
                            break;
                        case 1:
                            menu.afficheHistoire(true);
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                        break;
                    }
                    break;
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if (unMenu == false)
                {
                    switch (event.key.code)
                    {
                    case Keyboard::Right:
                        if (getElementPixel(niveau, hero.getXMax()+deplacement, hero.getYMin()) == 1 && getElementPixel(niveau, hero.getXMax() + deplacement, hero.getYMax()) == 1)
                        {
                            hero.move(deplacement, 0);
                            hero.anim("right");
                            view.move(deplacement, 0);
                            hero.MoveTxt("Right", deplacement);
                        }
                        break;
                    case Keyboard::Left:
                        if (getElementPixel(niveau, hero.getXMin() - deplacement, hero.getYMin()) == 1 && getElementPixel(niveau, hero.getXMin() - deplacement, hero.getYMax()) == 1)
                        {
                            hero.move(-deplacement, 0);
                            hero.anim("left");
                            view.move(-deplacement, 0);
                            hero.MoveTxt("Left", deplacement);
                        }
                        break;
                    case Keyboard::Down:
                        if (getElementPixel(niveau, hero.getXMax(), hero.getYMax() + deplacement) == 1 && getElementPixel(niveau, hero.getXMin(), hero.getYMax() + deplacement) == 1)
                        {
                            hero.move(0, deplacement);
                            hero.anim("down");
                        }
                        break;
                    case Keyboard::Up:
                        if (getElementPixel(niveau, hero.getXMax(), hero.getYMin() - deplacement ) == 1 && getElementPixel(niveau, hero.getXMin(), hero.getYMin() - deplacement) == 1)
                        {
                            hero.move(0, -deplacement);
                            hero.anim("up");
                        }
                        break;
                    case Keyboard::Space:
                        spaceCurrent = true;
                        if ((noBonusBombs.size() > 0 || hero.getNbrBomb() > 0) && spaceBefore == false)
                        {
                            Vector2f positionV = hero.getSprite().getPosition();
                            Vector2i positionIndex = Vector2i(round((positionV.x / 64)), round((positionV.y / 64)));

                            if (noBonusBombs.size() > 0)
                            {
                                noBonusBombs[noBonusBombs.size() - 1]->placeBomb(positionIndex);
                                activeBombs.push_back(noBonusBombs[noBonusBombs.size() - 1]);
                                noBonusBombs.pop_back();
                            }
                            else
                            {
                                hero.RemoveBomb();
                                poolBombs[poolBombs.size() - 1]->placeBomb(positionIndex);
                                activeBombs.push_back(poolBombs[poolBombs.size() - 1]);
                                poolBombs.pop_back();
                            }
                        }
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < activeBombs.size(); i++)
        {
            if (activeBombs[i]->update())
            {
                ExplosionEntity tempExplositionE = niveau.GetExplosionEntity(activeBombs[i]->GetPosition(), hero.GetRange());
                hero.CheckDamageBomb(tempExplositionE);
                activeBombs[i]->ExplosionSound();
                poolExplosions[poolExplosions.size() - 1]->Explode(tempExplositionE);
                activeExplosions.push_back(poolExplosions[poolExplosions.size() - 1]);
                poolExplosions.erase(poolExplosions.begin() + poolExplosions.size() - 1);

                if (activeBombs[i]->IsBonus())
                {
                    
                    poolBombs.push_back(activeBombs[i]);
                    activeBombs.erase(activeBombs.begin() + i);
                }
                else
                {
                    noBonusBombs.push_back(activeBombs[i]);
                    activeBombs.erase(activeBombs.begin() + i);
                } 
            }
        }

        for (int i = 0; i < activeExplosions.size(); i++)
        {
            if (activeExplosions[i]->Update())
            {
                poolExplosions.push_back(activeExplosions[i]);
                activeExplosions.erase(activeExplosions.begin() + i);
            }
        }

        window.clear(Color::Black);

        if (unMenu == false)
        {
            window.draw(credit);
            window.draw(joke);
            niveau.draw(window);
            for (int i = 0; i < activeBombs.size(); i++)
            {
                activeBombs[i]->draw(window);
            }

            for (int i = 0; i < activeExplosions.size(); i++)
            {
                activeExplosions[i]->draw(window);
            }
            hero.draw(window);

            for (int i = 0; i < poolMonstre.size(); i++)
            {
                poolMonstre[i].draw(window);
            }
        }
        else
        {
            view.setCenter(sf::Vector2f(320, 320));
            menu.Draw(window);
        }


        window.setView(view);
        window.display();
    }
    return 0;
}