#include "test_framework.h"
#include "Weapon.h"

#include <cmath>

TEST(bullet_constructor_stores_fields) {
	sf::Sprite sprite;
	Bullet b(sprite, sf::Vector2f(1.f, 2.f), 45.f, 200.f, "playerBullet");
	CHECK_EQ(b.angle, 45.f);
	CHECK_EQ(b.radius, 200.f);
	CHECK_EQ(b.bulletCollider.getTag(), std::string("playerBullet"));
	CHECK_EQ(b.bullet.getPosition().x, 1.f);
	CHECK_EQ(b.bullet.getPosition().y, 2.f);
}

TEST(bullet_update_position_uses_polar_coordinates) {
	sf::Sprite sprite;
	Bullet b(sprite, sf::Vector2f(0.f, 0.f), 0.f, 0.f);
	b.angle = 0.f;
	b.radius = 50.f;
	b.updatePosition(sf::Vector2f(10.f, 20.f));

	CHECK_NEAR(b.xPos, 60.f, 0.001f);  // ref.x + radius * cos(angle)
	CHECK_NEAR(b.yPos, 20.f, 0.001f);  // ref.y + radius * sin(angle)
	CHECK_NEAR(b.bullet.getPosition().x, 60.f, 0.001f);
	CHECK_NEAR(b.bullet.getPosition().y, 20.f, 0.001f);
}

TEST(weapon_starts_empty) {
	Weapon w;
	CHECK_EQ(static_cast<int>(w.getBullets().size()), 0);
}

TEST(weapon_update_moves_every_bullet_in_range) {
	Weapon w;
	std::deque<Bullet>& bullets = w.getBullets();
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 100.f));
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 200.f));

	w.updateBullets(sf::Vector2f(0.f, 0.f), 1.0f);  // radius += 8

	REQUIRE_EQ(static_cast<int>(bullets.size()), 2);
	CHECK_NEAR(bullets.at(0).radius, 108.f, 0.001f);
	CHECK_NEAR(bullets.at(1).radius, 208.f, 0.001f);
}

TEST(weapon_update_culls_out_of_range_bullets_without_skipping) {
	Weapon w;
	std::deque<Bullet>& bullets = w.getBullets();
	// radii after a +8 step: 108 (kept), 58 (kept), 507 (culled), 502 (culled)
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 100.f));
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 50.f));
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 499.f));
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 494.f));

	w.updateBullets(sf::Vector2f(0.f, 0.f), 1.0f);

	// Only the two in-range bullets survive, and both were advanced.
	REQUIRE_EQ(static_cast<int>(bullets.size()), 2);
	CHECK_NEAR(bullets.at(0).radius, 108.f, 0.001f);
	CHECK_NEAR(bullets.at(1).radius, 58.f, 0.001f);
}

TEST(weapon_update_culls_bullets_that_leave_the_inner_boundary) {
	Weapon w;
	std::deque<Bullet>& bullets = w.getBullets();
	// bulletDir = -1 => radius -= 8; a bullet at radius 5 goes to -3 (culled)
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 5.f));
	bullets.push_back(Bullet(sf::Sprite(), sf::Vector2f(0.f, 0.f), 0.f, 100.f));

	w.updateBullets(sf::Vector2f(0.f, 0.f), -1.0f);

	REQUIRE_EQ(static_cast<int>(bullets.size()), 1);
	CHECK_NEAR(bullets.at(0).radius, 92.f, 0.001f);
}
