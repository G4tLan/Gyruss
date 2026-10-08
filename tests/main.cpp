#include <SFML/Graphics.hpp>

#include "test_framework.h"

int main() {
	// SFML releases its OpenGL context once the last resource is destroyed and
	// cannot always recreate it under a headless X server (Xvfb). Holding one
	// texture alive for the whole run keeps the context valid across every test.
	sf::Texture contextGuard;
	contextGuard.create(4, 4);

	return testfw::run();
}
