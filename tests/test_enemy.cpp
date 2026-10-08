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
