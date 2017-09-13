#include "Collider.h"

Collider::Collider(sf::Vector2f& parentPosition, sf::Vector2f& parentBounds):
_2Dcollider{parentPosition,parentBounds}
{
	
}

Collider::~Collider()
{
}


void Collider::update(sf::Vector2f& parentPosition, sf::Vector2f& parentBounds){
	sf::FloatRect tempRect{parentPosition,parentBounds};
	_2Dcollider = tempRect;
}


bool  Collider::collided(vector<sf::FloatRect>& gameObjects){
	for(auto bounds : gameObjects){
		if(_2Dcollider.intersects(bounds))
			return true;
	}
	return false;
}