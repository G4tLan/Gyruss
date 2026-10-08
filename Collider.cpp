#include "Collider.h"

Collider::Collider():
_2Dcollider{sf::Rect<float> (600,600,2,3)},_tag{"noNAme"}, _isCollided{false}
{

}

Collider::Collider(const sf::FloatRect& parentBounds):
_2Dcollider{parentBounds}, _tag{"noNAme"}, _isCollided{false}
{

}

Collider::~Collider()
{
}


void Collider::update(sf::FloatRect parentBounds){
	_2Dcollider = parentBounds;
}


bool  Collider::collided(vector<Collider>& gameObjects, int& index){
	if(_isCollided){
		return false;
	} else{
		for(size_t i = 0; i < gameObjects.size(); i++){
			if(_2Dcollider.intersects(gameObjects.at(i).getCollider())){
				index = static_cast<int>(i);
				_isCollided = true;
				gameObjects.at(i).setCollisionStatus(true);
				return true;
			}
		}
	}

	return false;
}

bool  Collider::collided(Collider& gameObject){
	if(_isCollided){
		return false;
	}
	return _2Dcollider.intersects(gameObject.getCollider());
}
