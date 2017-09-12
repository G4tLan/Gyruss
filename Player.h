#ifndef PLAYER_H
#define PLAYER_H
#include  <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include "Weapon.h"
#include <iostream>


using namespace std;

class Player
{
public:
	//sf::Time timeP;
	sf::Clock clockP;
	const float PI = 4*atan(1);
	
	Player(sf::Vector2u screenSize,float refX,float refY);
	sf::Vector2f getPlayerPosition(){return _playerSprite.getPosition();}
	float getPlayerRotation(){return _playerSprite.getRotation();}
	float getAngle(){return _angle;}
	float getRadius(){return _radius;}
	void update(sf::RenderWindow& window,int& countFrames);
	~Player();
private:
	float _radius;
	float _angle;
	float _refX;
	float _refY;
	Weapon _gun;
	sf::Texture _playerTexture;
	sf::Sprite _playerSprite;

};

#endif // PLAYER_H
