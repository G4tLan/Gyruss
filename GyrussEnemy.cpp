#include "GyrussEnemy.h"

GyrussEnemy::GyrussEnemy() 
{
		_isDead = false;
		_radius = 0.1f;
		if(EnemyTexture.loadFromFile("textures/enemy.png") ){
			cout << "enemy sprite loaded" << endl;
		}
		length = 500; 
		width = 500; 
		EnemySprite.setTexture(EnemyTexture) ; 
		int ts = 1 ;
		_x = 0; 
		_y=  0;
		
		_xRefPoint = ((width-1)/2)*ts;
		_yRefPoint = ((length -1)/2)*ts; 
		_dx = 4 - rand()%8 ; 
		_dy = 4 - rand()%8 ; 
		
		_enemyCollider.update(EnemySprite.getGlobalBounds());
		_enemyCollider.setTag("enemyCollider");
	
}

void GyrussEnemy::move()
{
	_radius = 100;
	//srand(time(0)) ; 
	//_dx =+ ((2 - rand()%2) +  _dx) ; 
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	//_dy =+ ((2 - rand()%2)+ _dy ) ;
	_y =  _radius*sin(_dTheta) +  _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
	// int changeinX = (_xRefPoint - _x)  ,changeinY = (_yRefPoint -  _y) ;
		EnemySprite.rotate(200) ;
		_dTheta += 0.05f;
}


float tempTime = 0;
void GyrussEnemy::updateScreen( sf::RenderWindow &window, vector<Collider> playerBullets)
{	
	float timeE = clockE.getElapsedTime().asSeconds ();
	///this is were the enemy chooses the move
	move() ; 
	////////////////////
	float xDiff = _x - _xRefPoint;
	float yDiff = _yRefPoint - _y;
	//_radius = sqrt(xDiff*xDiff + yDiff*yDiff);
	//_dTheta = atan(yDiff/(xDiff + 0.001f));
	/*
	if(yDiff >= 0 && xDiff >= 0){ //first quadrant
		_dTheta -= 4*atan(1)/2;
	} else if (yDiff >= 0 && xDiff < 0){ //second quadrant
		_dTheta -= 4*atan(1)/2;
	} else if (yDiff < 0 && xDiff < 0){ //third quadrant
		_dTheta += 4*atan(1)/2;
	}else if (yDiff < 0 && xDiff >= 0){ //fourth quadrant
		_dTheta += 4*atan(1)/2;
	}
	*/
	tempTime += timeE;
	if(tempTime > 0.1){
		//cout << " enemy shooting" << endl;
		//_enemyWeapon.enemyShoot(*this, "enemyBullet");
		tempTime = 0;
	}
	timeE = clockE.restart().asSeconds();
	//_enemyWeapon.weaponUpdate(window,sf::Vector2<float> (250,250), 1.0f);
	_enemyCollider.update(EnemySprite.getGlobalBounds());
	int i = 0;
	if(_enemyCollider.collided(playerBullets,i) && !playerBullets.empty()){
		if(playerBullets.at(i - 1).getTag() == "playerBullet"){
			_isDead = true;
			
		}
	}
	//std::cout <<"x: " << _x << "y: " << _y << std::endl ; ,
	window.draw(EnemySprite) ;
}


void GyrussEnemy::enemySetup(sf::Texture texture,sf::Vector2f initialPosition, sf::Vector2f scale){
	EnemyTexture = texture;
	EnemySprite.setPosition(initialPosition);
	EnemySprite.setScale(scale);
}

GyrussEnemy::GyrussEnemy( sf::Vector2f initPos, EnemyType enemyType = EnemyType::ships){
	sf::Texture temp ;
	switch(enemyType){
		case EnemyType::ships:
			temp.loadFromFile("textures/enemy.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::satellites:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::laser:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::generator:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::asteroids:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		default:
			break;
	} 
}
