# Gyruss — project context

A small Gyruss-style arcade shooter written in C++17 on top of SFML. The player
rides a ring around the centre of the screen and fires inward along its radius;
enemies ride a smaller inner ring and orbit.

This document describes how the code is put together, how to build and run it,
and what is currently known to be broken. It is meant as an entry point for
anyone picking the repository up.

## Build, run, test

Everything goes through the `Makefile` (see `Makefile`):

| Target | Result |
| --- | --- |
| `make` / `make all` | builds game + demo into `Debug/` |
| `make game` | `Debug/Gyruss` (from `main.cpp`) |
| `make demo` | `Debug/GyrussEnemyDemo` (from `mainEnemy.cpp`) |
| `make test` | builds and runs the test suite `Debug/run_tests` |
| `make clean` | removes the build outputs |

Requirements: a C++17 compiler and the SFML graphics/window/system libraries
(`libsfml-dev` on Debian/Ubuntu). The tests create SFML textures, so on a
headless machine the `test` target wraps the binary in `xvfb-run`
(`apt-get install xvfb xauth`).

**Run the game from the directory that contains `textures/`.** The game loads
art via relative paths (`textures/player.png`, …) and only `Debug/textures/`
exists in the checkout, so start it as:

```
cd Debug && ./Gyruss
```

## Layout

| File | Purpose |
| --- | --- |
| `main.cpp` | the real game: splash screen, main loop, enemy wave |
| `mainEnemy.cpp` | minimal demo that only shows enemies orbiting |
| `Collider.*` | axis-aligned `sf::FloatRect` collision with a one-shot latch |
| `Weapon.*` | owns the `Bullet` pool and moves/culls/draws it |
| `Player.*` | player sprite, ring movement, firing, hit detection |
| `GyrussEnemy.*` | enemy sprite, orbit movement, death on player bullet |
| `tests/` | dependency-free test suite (`tests/test_framework.h`) |

## Geometry

The whole game is polar. A body is described by an *angle* (radians) and a
*distance from the centre*; its screen position is

```
pos = centre + radius * (cos(angle), sin(angle))
```

The playfield is 500x500, so the centre is `(250, 250)`.

* The player orbits at radius **200** (`Player::_radius`).
* Enemies orbit at radius **100** (`GyrussEnemy::_radius`).
* A bullet stores its own `radius`/`angle` and is advanced along its spoke by
  `Weapon::updateBullets` (8 px per frame). It is culled once its radius leaves
  `[0, 500]`.
* The player's bullets travel **inward** (`weaponUpdate(..., -1.0f)`), the
  enemies' bullets would travel outward (`+1.0f`).

## Classes

### `Collider`

Wraps an `sf::FloatRect` plus a `_tag` and an `_isCollided` latch.

* `update(bounds)` stores the parent's current bounds.
* `collided(Collider&)` / `collided(vector<Collider>&, int& index)` test
  intersection. Once a collider has hit something it sets its own latch and
  returns `false` on later calls, so a bullet or an enemy collides only once.
  The vector overload also reports the index of the object that was hit.
* `resetCollisionStatus()` clears the latch; the player uses it every frame so
  it can be hit more than once.

### `Bullet` / `Weapon`

`Bullet` is a `sf::Sprite` plus its polar coordinates and its own `Collider`.
`Weapon` owns a `std::deque<Bullet>` and provides:

* `playerShoot(Player&, tag)` / `enemyShoot(GyrussEnemy&, tag)` — spawn a bullet
  at the owner's position/angle.
* `updateBullets(ref, direction)` — advance every bullet, erase those that left
  the field (erase by iterator, never `pop_front`).
* `weaponUpdate(window, ref, direction)` — the above plus drawing.
* `getBulletCollider()` — copies of the bullet colliders, for hit tests.

### `Player`

Placed on the ring by its constructor. `update()` rotates on Left/Right (using
the frame delta from `clockP`) and fires on Space when the caller's `countFrames`
has passed 15. It draws its bullets and itself, and tests its own collider
against the enemy bullets passed in by `main()`.

### `GyrussEnemy`

Two constructors: the default one loads `textures/enemy.png` and orbits
`(250, 250)` at radius 100; the parameterised one takes an orbit centre and an
`EnemyType`. `move()` advances by 0.05 rad and keeps the collider in step with
the sprite. `setOrbit(centre, radius, startAngle)` (re)places the enemy on its
orbit. `updateScreen()` moves, checks the player's bullets, and draws.

## Main loop (`main.cpp`)

1. Show a two-frame splash until Return is pressed.
2. Each frame: collect every enemy's bullets, update the player **once**, then
   update each enemy and erase the dead ones.

## Tests

`make test` builds `tests/*.cpp` together with the game's core sources and runs
them. The framework registers tests at static-init time; `CHECK*`/`REQUIRE*`
macros live in `tests/test_framework.h`. `tests/main.cpp` keeps one texture
alive for the whole run so SFML does not release its GL context between tests.

## Known limitations / open issues

* **Enemies never shoot.** `GyrussEnemy` owns a `_enemyWeapon` and exposes
  `getEnemyBullets()`, and `Weapon::enemyShoot` exists, but nothing ever calls
  it, so `getEnemyBullets()` always returns an empty vector and the player's
  enemy-bullet collision path can never fire. The corresponding lines were
  commented out in the original source.
* **A hit has no consequence.** `Player::update` detects the collision but the
  handler is empty; there is no life/score/game-over state.
* **No win/lose handling.** Killing every enemy leaves an empty `enemies` vector
  and the loop simply keeps running.
* `Collider`/`Weapon` getters return copies, so collision flags written on the
  copies (`getEnemyBullets()`, `getBulletCollider()`) do not propagate back to
  the real bullets.
* `GyrussEnemy` still carries dead members (`_dx`, `_dy`, `_Maxenemy`, the
  file-scope `tempTime`).
* Textures are required at runtime; a failed `loadFromFile` is only reported on
  `std::cout` and the affected sprite is then drawn blank.
