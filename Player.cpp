#include "Player.h"


Player::Player(sf::Vector2u screenSize, float refX, float refY)
:_radius{200.0f}, _angle{PI/2}, _refX{refX}, _refY{refY}
{
	if(!_playerTexture.loadFromFile("textures/player.png")){
		cout << "player texture not found in dir textures" << endl;
	} else {
		_playerSprite.setTexture(_playerTexture);
		float scaleFactor = 10;
		_playerSprite.setScale(500/(scaleFactor * (float)_playerSprite.getTextureRect().width),
								500/(scaleFactor*(float)_playerSprite.getTextureRect().height));
		_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
		_playerSprite.setRotation(_angle*180/PI - 90);
	}
}

Player::~Player()
{
}

void Player::update(sf::RenderWindow& window){
	sf::Time timeP = clockP.getElapsedTime();
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		_angle -= PI*timeP.asMilliseconds()/600;
		_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
		_playerSprite.setRotation(_angle*180/PI - 90);
		cout << _playerSprite.getPosition().x << " -,- " << _playerSprite.getPosition().y << endl;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		_angle += PI*timeP.asMilliseconds()/600;
		_playerSprite.setPosition(_refX + _radius*cos(_angle), _refY + _radius*sin(_angle));
		_playerSprite.setRotation(_angle*180/PI - 90);
		cout << _playerSprite.getPosition().x << " -,- " << _playerSprite.getPosition().y << endl;
	}
	 
	timeP = clockP.restart();
	window.draw(_playerSprite);
}