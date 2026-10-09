#include "test_framework.h"
#include "GyrussEnemy.h"

TEST(enemy_default_constructor_initialises_fields) {
	GyrussEnemy e;
	CHECK(!e.isEnemyDead());
	CHECK_NEAR(e.getEnemyRadius(), 100.0f, 0.001f);
	// _dTheta used to be left uninitialised before move() ran
	CHECK_NEAR(e.getEnemyAngle(), 0.0f, 0.001f);
}

TEST(enemy_default_constructor_centres_on_the_screen) {
	GyrussEnemy e;
	CHECK_NEAR(e.getEnemyAngle(), 0.0f, 0.001f);
	e.move();  // angle 0 => ref + (radius, 0), screen centre is (250, 250)
	CHECK_NEAR(e.getEnemyPosition().x, 350.0f, 0.01f);
	CHECK_NEAR(e.getEnemyPosition().y, 250.0f, 0.01f);
}

TEST(enemy_parameterised_constructor_initialises_everything) {
	sf::Vector2f pos(120.f, 340.f);
	GyrussEnemy e(pos, EnemyType::ships);

	CHECK(!e.isEnemyDead());
	CHECK_NEAR(e.getEnemyRadius(), 100.0f, 0.001f);
	CHECK_NEAR(e.getEnemyAngle(), 0.0f, 0.001f);
	CHECK_NEAR(e.getEnemyPosition().x, 120.0f, 0.001f);
	CHECK_NEAR(e.getEnemyPosition().y, 340.0f, 0.001f);
	CHECK_NEAR(e.getX(), 120.0f, 0.001f);
	CHECK_NEAR(e.getY(), 340.0f, 0.001f);
}

TEST(enemy_move_orbits_its_reference_point_and_advances_angle) {
	sf::Vector2f pos(250.f, 250.f);
	GyrussEnemy e(pos, EnemyType::ships);

	e.move();  // starts at angle 0
	CHECK_NEAR(e.getEnemyPosition().x, 350.0f, 0.01f);
	CHECK_NEAR(e.getEnemyPosition().y, 250.0f, 0.01f);
	CHECK(e.getEnemyAngle() > 0.0f);
}

TEST(enemy_getters_report_floating_point_positions) {
	GyrussEnemy e(sf::Vector2f(12.5f, 7.25f), EnemyType::ships);
	CHECK_NEAR(e.getX(), 12.5f, 0.001f);
	CHECK_NEAR(e.getY(), 7.25f, 0.001f);
}

TEST(enemy_set_orbit_configures_its_path) {
	GyrussEnemy e;
	e.setOrbit(sf::Vector2f(100.f, 100.f), 50.f, 0.f);

	CHECK_NEAR(e.getEnemyRadius(), 50.f, 0.001f);
	CHECK_NEAR(e.getEnemyAngle(), 0.f, 0.001f);

	// move() must orbit the configured centre at the configured radius, not a
	// hard-coded one. Angle 0 => centre + (radius, 0).
	e.move();
	CHECK_NEAR(e.getEnemyPosition().x, 150.f, 0.01f);
	CHECK_NEAR(e.getEnemyPosition().y, 100.f, 0.01f);
}

TEST(enemy_set_orbit_places_the_sprite_before_the_first_move) {
	GyrussEnemy e;
	e.setOrbit(sf::Vector2f(250.f, 250.f), 100.f, 1.57079633f);  // pi/2

	CHECK_NEAR(e.getEnemyPosition().x, 250.f, 0.01f);
	CHECK_NEAR(e.getEnemyPosition().y, 350.f, 0.01f);
}

TEST(enemies_with_different_start_angles_do_not_stack) {
	GyrussEnemy a;
	GyrussEnemy b;
	a.setOrbit(sf::Vector2f(250.f, 250.f), 100.f, 0.f);
	b.setOrbit(sf::Vector2f(250.f, 250.f), 100.f, 3.14159265f);

	a.move();
	b.move();

	// Opposite sides of the ring, not the same point.
	CHECK_NEAR(a.getEnemyPosition().x, 350.f, 0.01f);
	CHECK_NEAR(b.getEnemyPosition().x, 150.f, 0.01f);
	CHECK_NEAR(a.getEnemyPosition().y, 250.f, 0.01f);
	CHECK_NEAR(b.getEnemyPosition().y, 250.f, 0.01f);
}

TEST(enemy_collider_tracks_the_sprite_after_moving) {
	GyrussEnemy e;
	e.setOrbit(sf::Vector2f(250.f, 250.f), 100.f, 0.f);
	e.move();

	CHECK_NEAR(e.getEnemyColliderBounds().left, e.getEnemyPosition().x, 0.01f);
	CHECK_NEAR(e.getEnemyColliderBounds().top, e.getEnemyPosition().y, 0.01f);
}
