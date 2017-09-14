#ifndef PLAYER_H
#define PLAYER_H
#include  <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include "Weapon.h"
#include "Collider.h"
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
	vector<Collider> getPlayerBullets(){return _gun.getBulletCollider();}
	void update(sf::RenderWindow& window,int& countFrames, vector<Collider> enemyBullets);
	~Player();
private:
	float _radius;
	float _angle;
	float _refX;
	float _refY;
	Weapon _gun;
	sf::Texture _playerTexture;
	sf::Sprite _playerSprite;
	Collider _playerCollider;
};

#endif // PLAYER_H
