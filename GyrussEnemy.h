#ifndef GYRUSSENEMY_H
#define GYRUSSENEMY_H
#include <SFML/Graphics.hpp>
#include <cmath>
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
	void updateScreen( sf::RenderWindow &window, vector<Collider> playerBullets);
	int getX() {return _x ; }
	int getY() {return _y ; }   
	
	
	~GyrussEnemy(){cout << "enemy deleted" << endl;}//delete this;}
	
private:
		sf::Texture EnemyTexture ; 		
		sf::Sprite  EnemySprite ; 
		int length; 
		int width; 
		float _radius;
		float _dTheta;
		int _Maxenemy  ; 
		int _x, _y,  _dx , _dy , _xRefPoint, _yRefPoint;
		bool _isDead;
		EnemyType _enemyType;
		Weapon _enemyWeapon;
		Collider _enemyCollider;
};

#endif // GYRUSSENEMY_H
