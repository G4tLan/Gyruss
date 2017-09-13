#include "Collider.h"

Collider::Collider(sf::FloatRect& parentBounds):
_2Dcollider{parentBounds}, _tag{"noNAme"}
{
	
}

Collider::~Collider()
{
}


void Collider::update(sf::FloatRect parentBounds){
	_2Dcollider = parentBounds;
}


bool  Collider::collided(vector<Collider> gameObjects, int& index){
	for(auto bounds : gameObjects){
		if(_2Dcollider.intersects(bounds.getCollider())){
			index++;
			return true;
		}
	}
	return false;
}

bool  Collider::collided(sf::FloatRect& gameObject){
	return _2Dcollider.intersects(gameObject);
}