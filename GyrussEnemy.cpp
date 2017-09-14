#include "GyrussEnemy.h"

GyrussEnemy::GyrussEnemy() 
{
		EnemyTexture.loadFromFile("images/enemy.png") ;
		sEnemy.setTexture(EnemyTexture) ; 
		int ts = 1 ;
		_x= ((width-1)/2)*ts; 
		_y= ((length -1)/2)*ts ;
		
		_xRefPoint = _x ;
		_yRefPoint = _y ; 
		_dx = 4 - rand()%8 ; 
		_dy = 4 - rand()%8 ; 
	
	
	
}

void GyrussEnemy::move()
{
	srand(time(0)) ; 
	_dx =+ ((2 - rand()%2) +  _dx) ; _x +=  _dx ;
	_dy =+ ((2 - rand()%2)+ _dy ) ; _y +=      _dy ;
	 int changeinX = (_xRefPoint - _x)  ,changeinY = (_yRefPoint -  _y) ;
	
		
	 float r =  sqrt( pow(changeinX , 2)  + pow(changeinY , 2)   )   ; 
		
		if((  r >= 100)) { _dx =- _dx ; _x +=  _dx  ; } ;
	
		if((  r >= 100)) { _dy =- _dy ; _y += _dy  ; } ;
		sEnemy.rotate(10) ;
}



GyrussEnemy::updateScreen( sf::RenderWindow &window)
{
	move() ; 
	sEnemy.setPosition(_x, _y ) ;
	std::cout <<"x: " << _x << "y: " << _y << std::endl ; 
	window.draw(sEnemy) ;
}

GyrussEnemy::~GyrussEnemy()
{
}

