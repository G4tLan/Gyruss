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
class Weapon
{
public:
	Weapon();
	void shoot(Player& player, string name);
	void weaponUpdate(sf::RenderWindow& window, sf::Vector2f);
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
		Collider bulletCollider;
		Bullet(sf::Sprite bulletSprite, sf::Vector2f position, float rotation, float dist, string name = "bullet"): 
		bullet{bulletSprite}, angle{rotation}, radius{dist}
		{
			bullet.setPosition(position);
			bullet.setRotation(rotation);
			bulletCollider.setTag(name);
		}
		void updatePosition(sf::Vector2f refPoint){
			xPos = radius*cos(angle) + refPoint.x;
			yPos = radius*sin(angle) + refPoint.y;
			bullet.setPosition(xPos,yPos);
			bullet.setScale(bullet.getScale().x/1.012f,bullet.getScale().y/1.025f);
			bulletCollider.update(bullet.getGlobalBounds());
		}
	};
	deque<Weapon::Bullet> _allPlayerBullets;
};

#endif // WEAPON_H
