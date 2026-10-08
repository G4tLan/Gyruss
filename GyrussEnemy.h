#ifndef GYRUSSENEMY_H
#define GYRUSSENEMY_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <deque>
#include "Weapon.h"
#include "Collider.h"
#include <iostream>

using namespace std;
enum class EnemyType{
	ships = 0, satellites, asteroids, laser, generator
};

class GyrussEnemy
{
public:
    sf::Clock clockE;
	GyrussEnemy();
	GyrussEnemy(sf::Vector2f initPos,EnemyType enemyType);
	void enemySetup(sf::Texture texture,sf::Vector2f initialPosition, sf::Vector2f scale);
	sf::Vector2f getEnemyPosition(){return EnemySprite.getPosition();}
	float getEnemyRotation(){return EnemySprite.getRotation();}
	float getEnemyRadius(){ return _radius;}
	float getEnemyAngle(){return _dTheta;}
	vector<Collider> getEnemyBullets(){return _enemyWeapon.getBulletCollider();}
	bool isEnemyDead(){return _isDead;}
	void move() ; 
	void updateScreen( sf::RenderWindow &window, vector<Collider> playerBullets); //remove later
	void updateScreen( sf::RenderWindow &window, deque<Bullet>& playerBullets);
	float getX() {return _x ; }
	float getY() {return _y ; }   
	
	
	~GyrussEnemy(){}
	
private:
		sf::Texture EnemyTexture ; 		
		sf::Sprite  EnemySprite ; 
		int length{500}; 
		int width{500}; 
		float _radius{100.0f};
		float _dTheta{0.0f};
		int _Maxenemy{0}  ; 
		float _x{0}, _y{0},  _dx{0} , _dy{0} , _xRefPoint{250.0f}, _yRefPoint{250.0f};
		bool _isDead{false};
		EnemyType _enemyType{EnemyType::ships};
		Weapon _enemyWeapon;
		Collider _enemyCollider;
};

#endif // GYRUSSENEMY_H
