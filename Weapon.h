#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
using namespace std;
//forward declaration of player class
class Player;

class Weapon
{
public:
	Weapon();
	void shoot(Player& player);
	void weaponUpdate(sf::RenderWindow& window);
	~Weapon();
private:
	sf::Sprite _bullet;
	sf::Texture _bulletTexture;
	vector<sf::Sprite> _allPlayerBullets;
};

#endif // WEAPON_H
