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
	//Weapon weapon;
    /////////////////////////////
    sf::RenderWindow window(sf::VideoMode(500,500), "Try Game");
    window.setFramerateLimit(60);
	//center point for debugging
		sf::CircleShape shape(5);
		shape.setFillColor(sf::Color(100, 250, 50));
		shape.setPosition(window.getSize().x/2,window.getSize().y/2);
		
		
	//center point ends here
	
    Player mainPlayer(window.getSize(),250,250);
	
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();
        mainPlayer.update(window);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && countFrames > 10){
			cout << "shoot" << endl;
			//mainPlayer.shoot(mainPlayer);
			countFrames = 0;
		}
		//mainPlayer.weaponUpdate(window);
		window.draw(shape);
        window.display();
		countFrames++;
    }
    return 0;
}

