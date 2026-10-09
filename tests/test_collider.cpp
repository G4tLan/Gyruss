#include "test_framework.h"
#include "Collider.h"

TEST(collider_default_is_not_collided) {
	Collider c;
	CHECK(!c.isCollided());
	CHECK_EQ(c.getTag(), std::string("noNAme"));
}

TEST(collider_tag_round_trip) {
	Collider c;
	c.setTag("playerBullet");
	CHECK_EQ(c.getTag(), std::string("playerBullet"));
}

TEST(collider_update_stores_bounds) {
	Collider c;
	c.update(sf::FloatRect(10.f, 20.f, 30.f, 40.f));
	sf::FloatRect bounds = c.getCollider();
	CHECK_EQ(bounds.left, 10.f);
	CHECK_EQ(bounds.top, 20.f);
	CHECK_EQ(bounds.width, 30.f);
	CHECK_EQ(bounds.height, 40.f);
}

TEST(collider_floatrect_constructor_stores_bounds) {
	sf::FloatRect bounds(1.f, 2.f, 3.f, 4.f);
	Collider c(bounds);
	CHECK_EQ(c.getCollider().left, 1.f);
	CHECK_EQ(c.getCollider().width, 3.f);
}

TEST(single_collider_detects_intersection) {
	Collider a;
	Collider b;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));
	b.update(sf::FloatRect(5.f, 5.f, 10.f, 10.f));
	CHECK(a.collided(b));
}

TEST(single_collider_detects_no_intersection) {
	Collider a;
	Collider b;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));
	b.update(sf::FloatRect(50.f, 50.f, 10.f, 10.f));
	CHECK(!a.collided(b));
}

TEST(single_collider_does_not_repeat_after_being_flagged) {
	Collider a;
	Collider b;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));
	b.update(sf::FloatRect(5.f, 5.f, 10.f, 10.f));
	CHECK(a.collided(b));
	a.setCollisionStatus(true);
	CHECK(!a.collided(b));
}

TEST(vector_collision_reports_index_of_hit_and_flags_both) {
	Collider a;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));

	std::vector<Collider> objects(3);
	objects.at(0).update(sf::FloatRect(100.f, 100.f, 10.f, 10.f));
	objects.at(1).update(sf::FloatRect(5.f, 5.f, 10.f, 10.f));
	objects.at(2).update(sf::FloatRect(200.f, 200.f, 10.f, 10.f));

	int index = -1;
	bool hit = a.collided(objects, index);

	CHECK(hit);
	CHECK_EQ(index, 1);  // index of the colliding object, not a running count
	CHECK(a.isCollided());
	CHECK(objects.at(1).isCollided());
	CHECK(!objects.at(0).isCollided());
	CHECK(!objects.at(2).isCollided());
}

TEST(vector_collision_without_hit_leaves_index_untouched) {
	Collider a;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));

	std::vector<Collider> objects(2);
	objects.at(0).update(sf::FloatRect(100.f, 100.f, 10.f, 10.f));
	objects.at(1).update(sf::FloatRect(200.f, 200.f, 10.f, 10.f));

	int index = -1;
	CHECK(!a.collided(objects, index));
	CHECK_EQ(index, -1);
}

TEST(vector_collision_skipped_when_already_collided) {
	Collider a;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));
	a.setCollisionStatus(true);

	std::vector<Collider> objects(1);
	objects.at(0).update(sf::FloatRect(5.f, 5.f, 10.f, 10.f));

	int index = -1;
	CHECK(!a.collided(objects, index));
}

TEST(reset_collision_status_rearms_the_collider) {
	Collider a;
	Collider b;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));
	b.update(sf::FloatRect(5.f, 5.f, 10.f, 10.f));

	CHECK(a.collided(b));
	a.setCollisionStatus(true);
	CHECK(a.isCollided());
	CHECK(!a.collided(b));  // still latched

	a.resetCollisionStatus();
	CHECK(!a.isCollided());
	CHECK(a.collided(b));  // can collide again after the reset
}

TEST(reset_collision_status_rearms_vector_collisions) {
	Collider a;
	a.update(sf::FloatRect(0.f, 0.f, 10.f, 10.f));

	std::vector<Collider> objects(1);
	objects.at(0).update(sf::FloatRect(5.f, 5.f, 10.f, 10.f));

	int index = -1;
	CHECK(a.collided(objects, index));
	CHECK_EQ(index, 0);
	CHECK(!a.collided(objects, index));  // latched after the first hit

	a.resetCollisionStatus();
	index = -1;
	CHECK(a.collided(objects, index));
	CHECK_EQ(index, 0);
}
