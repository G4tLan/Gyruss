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
	Bullet bulletSpawn(_bulletPrefab, playerObject.getPlayerPosition(), playerObject.getPlayerRotation(),playerObject.getRadius(),name);
		//cout << "bullet pos " << bulletSpawn.bullet.getPosition().x << " " << bulletSpawn.bullet.getPosition().y << endl;
		
	bulletSpawn.angle = playerObject.getAngle();
	_allBullets.push_back(bulletSpawn);
}
void Weapon::enemyShoot(GyrussEnemy& enemyObject, string name){
	//spawns bullet and stores it in array
	Bullet bulletSpawn(_bulletPrefab, enemyObject.getEnemyPosition(), enemyObject.getEnemyRotation(),enemyObject.getEnemyRadius(),name);
		//cout << "bullet pos " << bulletSpawn.bullet.getPosition().x << " " << bulletSpawn.bullet.getPosition().y << endl;
	bulletSpawn.angle = enemyObject.getEnemyAngle();
	_allBullets.push_back(bulletSpawn);
}

void Weapon::updateBullets(sf::Vector2f refPoint, float bulletDir){
	///for each bullet object move it and drop the ones that left the play field
	for(auto it = _allBullets.begin(); it != _allBullets.end(); ){
		it->radius += 8*bulletDir;
		it->updatePosition(refPoint);
		if(it->radius < 0 || it->radius > 500){
			it = _allBullets.erase(it);
		} else {
			++it;
		}
	}
}

void Weapon::weaponUpdate(sf::RenderWindow& window, sf::Vector2f refPoint, float bulletDir){
	updateBullets(refPoint, bulletDir);
	for(auto& bullet : _allBullets){
		window.draw(bullet.bullet);
	}
}

vector<Collider> Weapon::getBulletCollider(){
	vector<Collider> bulletColliders;
	for(auto bullet:_allBullets){
		bulletColliders.push_back(bullet.bulletCollider);
	}
	return bulletColliders;
}