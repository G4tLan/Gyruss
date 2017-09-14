#ifndef GYRUSSENEMY_H
#define GYRUSSENEMY_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


class GyrussEnemy
{
public:
    
	GyrussEnemy();
	void move() ; 
	updateScreen( sf::RenderWindow &window);
	int getX() {return _x ; }  
	int getY()   {return _y ; }   
	
	
	~GyrussEnemy();
	
private:
		sf::Texture EnemyTexture ; 		
		sf::Sprite sEnemy ; 
		const int length =500 ; 
		const int width = 500 ; 
		int _Maxenemy  ; 
		int _x, _y,  _dx , _dy , _xRefPoint, _yRefPoint;   
		


};

#endif // GYRUSSENEMY_H
