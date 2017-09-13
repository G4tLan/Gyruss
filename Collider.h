#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;

class Collider
{
public:
	Collider(){};
	Collider(sf::FloatRect& parentBounds);
	bool collided(vector<Collider> gameObjects, int& index);
	bool collided(sf::FloatRect& gameObject);
	sf::FloatRect getCollider(){return _2Dcollider;}
	string getTag(){return _tag;}
	void setTag(string& name){_tag = name;}
	void update(sf::FloatRect parentBounds);
	~Collider();
private:
	sf::FloatRect _2Dcollider;
	string _tag;
};

#endif // COLLIDER_H
