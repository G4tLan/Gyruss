
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "GyrussEnemy.h"
#include <iostream>
#include <vector>
#include "Weapon.h"
using namespace std;

int main()
{   //////////////////for checking frame rate
    sf::Clock clock;
    sf::Time time;
	auto countFrames = 0;
	bool playGame = false;
	//Weapon weapon;
    /////////////////////////////
    sf::RenderWindow window(sf::VideoMode(500,500), "Try Game");
    window.setFramerateLimit(60);
	//center point for debugging
		sf::CircleShape shape(5);
		shape.setFillColor(sf::Color(100, 250, 50));
		shape.setPosition(window.getSize().x/2,window.getSize().y/2);
	//center point ends here
	
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
	
	int enemyCount = 1 ; 
	vector<GyrussEnemy> a(3) ; 
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
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					playGame = true;
            }
        }
        window.clear();
		
		if(!playGame){
			if(countFrames < 20){
				background.setTexture(spT1);
				background.setScale(500*3.8/( (float)background.getTextureRect().width),500*2.17/((float)background.getTextureRect().height));
				window.draw(background);
			} else {
				background.setTexture(spT2);
				background.setScale(500*3.8/( (float)background.getTextureRect().width),500*2.17/((float)background.getTextureRect().height));
				window.draw(background);
				if(countFrames > 40)
					countFrames = 0;
			}
		} else {
			background.setTexture(backgroundTexture);
			background.setScale(500/( (float)background.getTextureRect().width),500/((float)background.getTextureRect().height));
			window.draw(background);
			
			for (int i = 0; i < a.size(); ++i){
				mainPlayer.update(window,countFrames,a.at(i).getEnemyBullets());
				a.at(i).updateScreen(window,mainPlayer.getPlayerBullets()) ;
				if(a.at(i).isEnemyDead()){
					cout << "enemy dead" << endl;
					std::vector<GyrussEnemy>::iterator it = a.begin();
					cout<< "lenght of vec before " << a.size() << endl;
					a.at(i).~GyrussEnemy();
					cout<< "lenght of vec after " << a.size() << endl;
				}
			}/*
				mainPlayer.update(window,countFrames,testEnemy.getEnemyBullets());
				testEnemy.updateScreen(window,mainPlayer.getPlayerBullets()) ;
				if(testEnemy.isEnemyDead()){
					cout << "enemy dead" << endl;
				}*/
		}
		
		//mainPlayer.weaponUpdate(window);
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