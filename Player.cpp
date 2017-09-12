#include "Player.h"

Player::Player(){
	
}

Player::Player(sf::Vector2u screenSize):_radius{200.0f}, _angle{-PI}
{
	if(!_playerTexture.loadFromFile("textures/player.png")){
		cout << "player texture not found in dir textures" << endl;
	} else {
		_playerSprite.setTexture(_playerTexture);
		 cout << screenSize.x << " " << screenSize.y << endl;
		 float scaleFactor = 10;
		 float screenWidth = (float)screenSize.x;
		 float screenHeight = (float)screenSize.y;
		 _playerSprite.setScale(screenWidth/(scaleFactor * (float)_playerSprite.getTextureRect().width),
								screenHeight/(scaleFactor*(float)_playerSprite.getTextureRect().height));
		 _refX = screenWidth/2;
		 _refY = screenHeight/2;
		_playerSprite.setPosition(_refX, _refY + _radius);
		
		//_playerSprite.setOrigin(playerWidth/2,playerHeight/2);
	}
}

Player::~Player()
{
}

sf::Sprite Player::getPlayerSprite(){
	return _playerSprite;
}

void Player::update(sf::RenderWindow& window){
	timeP = clockP.getElapsedTime();
	
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