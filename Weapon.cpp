#include "Weapon.h"
#include "Player.h"

Weapon::Weapon(): _allPlayerBullets(1)
{
	if(_bulletTexture.loadFromFile("textures/bullet.png")){
		_bullet.setTexture(_bulletTexture);
		_bullet.setScale(0.025f,0.025f);
	}
	else{
		cout << "bullet texture not found" << endl;
	}
	cout << _allPlayerBullets.size() << endl;
}

Weapon::~Weapon()
{
}

void Weapon::shoot(Player& playerObject){
	//spawns bullet and stores it in array
	sf::Sprite bulletSpawn = _bullet;
	bulletSpawn.setPosition(playerObject.getPlayerPosition());
	bulletSpawn.setRotation(playerObject.getPlayerRotation());
		cout << "bullet pos " << bulletSpawn.getPosition().x << " " << bulletSpawn.getPosition().y << endl;
	_allPlayerBullets.push_back(bulletSpawn);
}
float xoff = 100, yoff = 100;
void Weapon::weaponUpdate(sf::RenderWindow& window){
	///for each bullet object move it 
	
	for(auto bullet: _allPlayerBullets){
		bullet.setPosition(bullet.getPosition().x - xoff,bullet.getPosition().y - yoff);
		window.draw(bullet);
	}
}

