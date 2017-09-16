#include "Collider.h"

Collider::Collider():
_2Dcollider{sf::Rect<float> (600,600,2,3)},_tag{"noNAme"}, _isCollided{false}
{
	
}

Collider::Collider(sf::FloatRect& parentBounds):
_2Dcollider{parentBounds}, _tag{"noNAme"}, _isCollided{false}
{
	
}

Collider::~Collider()
{		
		//if(_tag == "playerBullet" && !_isCollided){
			//cout<< _tag << " Collider destroyed here" << endl;
		//	_isCollided  = true;
		//}
}


void Collider::update(sf::FloatRect parentBounds){
	_2Dcollider = parentBounds;
	if(_tag == "playerBullet")
	cout << " bounds " <<	parentBounds.left << " " << parentBounds.top << endl;
}


bool  Collider::collided(vector<Collider>& gameObjects, int& index){
	
	if(_isCollided){
		return false;
	} else{
		for(auto i = 0; i < gameObjects.size(); i++){
			if(_2Dcollider.intersects(gameObjects.at(i).getCollider())){
				index++;
				cout << _tag << " collided with " << gameObjects.at(i).getTag() << endl;
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