#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class Collider
{
public:
	Collider(sf::Vector2f& parentPosition, sf::Vector2f& parentBounds);
	bool collided(vector<sf::FloatRect>& gameObjects);
	void update(sf::Vector2f& parentPosition, sf::Vector2f& parentBounds);
	~Collider();
private:
	sf::FloatRect _2Dcollider;
};

#endif // COLLIDER_H
