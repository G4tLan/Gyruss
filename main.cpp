#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "GyrussEnemy.h"
#include <iostream>
#include <vector>
#include <list>
#include "Weapon.h"
using namespace std;

int main()
{   
	//////////////////for checking frame rate
    sf::Clock clock;
    sf::Time time;
	auto countFrames = 0;
	bool playGame = false;
	//Weapon weapon;
    /////////////////////////////
    sf::RenderWindow window(sf::VideoMode(500,500), "Try Game");
    window.setFramerateLimit(60);
	
	///Background
		sf::Texture backgroundTexture;
		if(backgroundTexture.loadFromFile("textures/background.jpg")){
			cout << "backgrund loaded" << endl;
		}
		sf::Sprite background(backgroundTexture);
		background.setPosition(0,0);
		//background.setScale(500/( (float)background.getTextureRect().width),500/((float)background.getTextureRect().height));
	//Splash screen
	sf::Texture spT1,spT2;
	spT1.loadFromFile("textures/splash1.png");
	spT2.loadFromFile("textures/splash2.png");
	
	//////Enemy ??????????
	
	//list<GyrussEnemy> a(3); 
	vector<GyrussEnemy> enemies(1);
	GyrussEnemy testEnemy;
	////////////////////////////
    Player mainPlayer(window.getSize(),250,250);
	
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
					playGame = true;
					background.setTexture(backgroundTexture);
					background.setScale(500/( (float)background.getTextureRect().width),500/((float)background.getTextureRect().height));
				}
            }
        }
        window.clear();
		
		if(!playGame){
			//Splash screen animation
			if(countFrames < 20){
				background.setTexture(spT1);
				background.setScale(500*3.8/( (float)background.getTextureRect().width),500*2.17/((float)background.getTextureRect().height));
			} else {
				background.setTexture(spT2);
				background.setScale(500*3.8/( (float)background.getTextureRect().width),500*2.17/((float)background.getTextureRect().height));
			
				if(countFrames > 40)
					countFrames = 0;
			}
			window.draw(background);
			//////
		} else {
			window.draw(background);
			int i = 0;
			for(auto it = enemies.begin(); (it != enemies.end()) && !enemies.empty(); it++){
				auto &enemy = *it;
				mainPlayer.update(window,countFrames,enemy.getEnemyBullets());
				enemy.updateScreen(window,mainPlayer.getPlayerBullets()) ;
				
				if(enemy.isEnemyDead()){
					enemies.erase(it);
					break;
				}
			}
			if(enemies.empty()){
				mainPlayer.update(window,countFrames,testEnemy.getEnemyBullets());
			}
			
		}
		
        window.display();
		countFrames++;
    }
    return 0;
}


/*
//////////////////////////////////////////////////////////////enemy
#include <SFML/Graphics.hpp>
#include "GyrussEnemy.h"
#include "Player.h"
#include "iostream"


using namespace std ; 
using namespace sf ; 

int main()
{
	
	//////Create Player ///////
	Player player(sf::Vector2<unsigned int> (500,500), 250,250);
	
	/////////////////////////
	
	srand(time(0)) ; 
	const int width  = 500 , length = 500;
    sf::RenderWindow window(sf::VideoMode(width, length ), "Gyruss");
	window.setFramerateLimit(60);
	
	Texture EnemyTexture ; 
	EnemyTexture.loadFromFile("textures/enemy.png") ;
	Sprite sEnemy(EnemyTexture) ;  
	
	sEnemy.setOrigin(20,20) ; 
	int enemyCount = 1 ; 
	GyrussEnemy a[1] ; 
	
	
	//int x = 0 , y = 0 ,dx = 0 , dy = 0 ; 
	//float timer=0 , delay = 0.07 ;
	Clock clock ; 
   
    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds() ; 
		clock.restart() ;
		timer +=time ;		
		Event event  ; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear() ; 

		 
		for(int i = 0 ; i < enemyCount ; i++)
		{
			a[i].updateScreen(window) ; 
		}

        window.display();
    }

    return 0;
}
*/