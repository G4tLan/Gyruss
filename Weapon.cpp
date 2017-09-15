#include "Weapon.h"
#include "Player.h"
#include "GyrussEnemy.h"
#include <cstdlib>

Weapon::Weapon()
{
	if(_bulletTexture.loadFromFile("textures/bullet.png")){
		_bulletPrefab.setTexture(_bulletTexture);
		_bulletPrefab.setScale(0.075f,0.075f);
	}
	else{
		//cout << "bullet texture not found" << endl;
	}
}

Weapon::~Weapon()
{
}

void Weapon::playerShoot(Player& playerObject, string name){
	//spawns bullet and stores it in array
	Weapon::Bullet bulletSpawn(_bulletPrefab, playerObject.getPlayerPosition(), playerObject.getPlayerRotation(),playerObject.getRadius(),name);
		//cout << "bullet pos " << bulletSpawn.bullet.getPosition().x << " " << bulletSpawn.bullet.getPosition().y << endl;
	bulletSpawn.angle = playerObject.getAngle();
	_allBullets.push_back(bulletSpawn);
}
void Weapon::enemyShoot(GyrussEnemy& enemyObject, string name){
	//spawns bullet and stores it in array
	Weapon::Bullet bulletSpawn(_bulletPrefab, enemyObject.getEnemyPosition(), enemyObject.getEnemyRotation(),enemyObject.getEnemyRadius(),name);
		//cout << "bullet pos " << bulletSpawn.bullet.getPosition().x << " " << bulletSpawn.bullet.getPosition().y << endl;
	bulletSpawn.angle = enemyObject.getEnemyAngle();
	_allBullets.push_back(bulletSpawn);
}

void Weapon::weaponUpdate(sf::RenderWindow& window, sf::Vector2f refPoint, float bulletDir){
	///for each bullet object move it 
	for(auto j = 0; j < _allBullets.size() ; j++){
		_allBullets.at(j).radius += 8*bulletDir;
		_allBullets.at(j).updatePosition(refPoint);
		window.draw(_allBullets.at(j).bullet);
		if(_allBullets.at(j).radius < 0 || _allBullets.at(j).radius > 500){
			_allBullets.pop_front();			
		}
	}
	//system("pause");
}

vector<Collider> Weapon::getBulletCollider(){
	for(auto bullet:_allBullets){
		bulletColliders.push_back(bullet.bulletCollider);
	}
	return bulletColliders;
}