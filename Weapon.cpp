#include "Weapon.h"
#include "Player.h"
#include <cstdlib>

Weapon::Weapon()
{
	if(_bulletTexture.loadFromFile("textures/bullet.png")){
		_bulletPrefab.setTexture(_bulletTexture);
		_bulletPrefab.setScale(0.075f,0.075f);
	}
	else{
		cout << "bullet texture not found" << endl;
	}
}

Weapon::~Weapon()
{
}

void Weapon::shoot(Player& playerObject){
	//spawns bullet and stores it in array
	Weapon::Bullet bulletSpawn(_bulletPrefab, playerObject.getPlayerPosition(), playerObject.getPlayerRotation(),playerObject.getRadius());
		cout << "bullet pos " << bulletSpawn.bullet.getPosition().x << " " << bulletSpawn.bullet.getPosition().y << endl;
	bulletSpawn.angle = playerObject.getAngle();
	_allPlayerBullets.push_back(bulletSpawn);
}
void Weapon::weaponUpdate(sf::RenderWindow& window, sf::Vector2f refPoint){
	///for each bullet object move it 
	for(int j = 0; j < _allPlayerBullets.size() ; j++){
		_allPlayerBullets.at(j).radius -= 2;
		_allPlayerBullets.at(j).updatePosition(refPoint);
		window.draw(_allPlayerBullets.at(j).bullet);
		if(_allPlayerBullets.at(j).radius < 0){
			_allPlayerBullets.pop_front();			
		}
	}
	//system("pause");
}

