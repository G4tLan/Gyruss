#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include <iostream>
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
			mainPlayer.update(window,countFrames);
		}
		
		//mainPlayer.weaponUpdate(window);
        window.display();
		countFrames++;
    }
    return 0;
}

