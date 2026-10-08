#include "GyrussEnemy.h"

GyrussEnemy::GyrussEnemy() 
{
		_isDead = false;
		_radius = 100.0f;
		_dTheta = 0.0f;
		_enemyType = EnemyType::ships;
		if(EnemyTexture.loadFromFile("textures/enemy.png") ){
			cout << "enemy sprite loaded" << endl;
		}
		length = 500; 
		width = 500; 
		EnemySprite.setTexture(EnemyTexture) ; 
		_x = 0; 
		_y=  0;
		
		_xRefPoint = width/2;
		_yRefPoint = length/2; 
		_dx = 4 - rand()%8 ; 
		_dy = 4 - rand()%8 ; 
		
		_enemyCollider.update(EnemySprite.getGlobalBounds());
		_enemyCollider.setTag("enemyCollider");
	
}

void GyrussEnemy::move()
{
	_radius = 100;
	_x =  _radius*cos(_dTheta) + _xRefPoint;
	_y =  _radius*sin(_dTheta) +  _yRefPoint;
	EnemySprite.setPosition(_x, _y ) ;
	_dTheta += 0.05f;
}


float tempTime = 0;
void GyrussEnemy::updateScreen( sf::RenderWindow &window, vector<Collider> playerBullets)
{	
	float timeE = clockE.getElapsedTime().asSeconds ();
	///this is were the enemy chooses the move
	move() ; 
	////////////////////
	tempTime += timeE;
	if(tempTime > 0.1){
		tempTime = 0;
	}
	timeE = clockE.restart().asSeconds();
	_enemyCollider.update(EnemySprite.getGlobalBounds());
	int i = 0;
	if(_enemyCollider.collided(playerBullets,i) && !playerBullets.empty()){
		if(playerBullets.at(i).getTag() == "playerBullet"){
			_isDead = true;
		}
	}
	window.draw(EnemySprite) ;
}


void GyrussEnemy::updateScreen( sf::RenderWindow &window, deque<Bullet>& playerBullets){
	_enemyCollider.update(EnemySprite.getGlobalBounds());
	
	move() ; 

	for(auto& bullet:playerBullets){
		if(_enemyCollider.collided(bullet.bulletCollider)){
			if(bullet.bulletCollider.isCollided()){
				continue;
			}
			bullet.bulletCollider.setCollisionStatus(true);
			if(bullet.bulletCollider.getTag() == "playerBullet"){
				_isDead = true;
			}
		}
	}
	window.draw(EnemySprite);
}



void GyrussEnemy::enemySetup(sf::Texture texture,sf::Vector2f initialPosition, sf::Vector2f scale){
	EnemyTexture = texture;
	EnemySprite.setTexture(EnemyTexture);
	EnemySprite.setPosition(initialPosition);
	EnemySprite.setScale(scale);
	_x = initialPosition.x;
	_y = initialPosition.y;
	_xRefPoint = initialPosition.x;
	_yRefPoint = initialPosition.y;
}

GyrussEnemy::GyrussEnemy( sf::Vector2f initPos, EnemyType enemyType){
	_isDead = false;
	_radius = 100.0f;
	_dTheta = 0.0f;
	_enemyType = enemyType;
	length = 500;
	width = 500;
	_x = initPos.x;
	_y = initPos.y;
	_dx = 4 - rand()%8 ;
	_dy = 4 - rand()%8 ;
	_xRefPoint = initPos.x;
	_yRefPoint = initPos.y;

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
