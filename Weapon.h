#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <deque>
#include <cmath>
#include "Collider.h"
#include <iostream>
using namespace std;
class Player;
class GyrussEnemy;
class Weapon
{
public:
	Weapon();
	void playerShoot(Player& player, string name);
	void enemyShoot(GyrussEnemy& enemy, string name);
	void weaponUpdate(sf::RenderWindow& window, sf::Vector2f, float bulletDir);
	vector<Collider> getBulletCollider();
	~Weapon();
private:
	sf::Sprite _bulletPrefab;
	sf::Texture _bulletTexture;
	struct Bullet{
		sf::Sprite bullet;
		float xPos;
		float yPos;
		float angle;
		float radius;
		float xScale,yScale;
		Collider bulletCollider;
		Bullet(sf::Sprite bulletSprite, sf::Vector2f position, float rotation, float dist, string name = "bullet"): 
		bullet{bulletSprite}, angle{rotation}, radius{dist}
		{
			bullet.setPosition(position);
			bullet.setRotation(rotation);
			bulletCollider.setTag(name);
			xScale = bullet.getScale().x;
			yScale = bullet.getScale().y;
		}
		void updatePosition(sf::Vector2f refPoint){
			xPos = radius*cos(angle) + refPoint.x;
			yPos = radius*sin(angle) + refPoint.y;
			bullet.setPosition(xPos,yPos);
			bullet.setScale(xScale*radius/200, yScale*radius/200);
			bulletCollider.update(bullet.getGlobalBounds());
			//cout << bulletCollider.getTag() << " radius " << radius << " angle " << angle << endl;
		}
	};
	deque<Weapon::Bullet> _allBullets;
	vector<Collider> bulletColliders;
};

#endif // WEAPON_H
