# Project Context

## What this is

A small **Gyruss**-style arcade game written in **C++17** using **SFML 2** (graphics + window +
system). The player rides a circular orbit around the screen centre, rotates left/right around it,
and fires bullets radially outward. Enemies orbit their own reference point and die when struck by
a player bullet. The project also carries a headless unit-test suite for the core logic.

## Layout

| Path | Purpose |
| --- | --- |
| `Collider.{h,cpp}` | Axis-aligned `sf::FloatRect` intersection helper (tag + one-shot collision flag). |
| `Player.{h,cpp}` | Orbiting player sprite, input handling, shooting, collider. |
| `Weapon.{h,cpp}` | `Bullet` struct + the weapon that spawns/updates/culls bullets. |
| `GyrussEnemy.{h,cpp}` | Orbiting enemy, `EnemyType` enum, death-on-hit logic. |
| `main.cpp` | The real game: splash screen, game loop, enemy management. |
| `mainEnemy.cpp` | A minimal demo binary that just draws a field of enemies. |
| `tests/` | Dependency-free unit tests (`test_framework.h` + `tests/main.cpp` runner). |
| `Debug/textures/` | All image assets, **tracked in git** (backgrounds, `player.png`, `enemy.png`, `bullet.png`, splash art). |
| `Gyruss2.txt` | Stray object-file list; not used by the build. |

The `Makefile` is the single build entry point. Sources are compiled directly (no object-file
rules): the root `.cpp` files and `tests/*.cpp` are each linked into their own binary.

## Build & test

Requires an SFML development install (`libsfml-dev` on Debian/Ubuntu) and a working compiler.

```sh
make            # builds Debug/Gyruss and Debug/GyrussEnemyDemo
make game       # the game only
make demo       # the demo only
make test       # builds + runs Debug/run_tests
make clean
```

Flags: `-std=c++17 -Wall -Wextra -Wpedantic -O2`; SFML linked via
`-lsfml-graphics -lsfml-window -lsfml-system`.

The tests create SFML textures, which need an X display. `make test` auto-detects a headless
environment (`$DISPLAY` unset) and wraps the run in `xvfb-run -a` when available; otherwise run it
from a real display. `tests/main.cpp` additionally holds one `sf::Texture` alive for the whole run,
because SFML cannot reliably recreate an OpenGL context under Xvfb.

Current state: **21 tests, 0 failed, 58 checks** (`make test`).

## Architecture / data flow

- **`Collider`** wraps an `sf::FloatRect` and a string `tag`, plus an `_isCollided` latch.
  `collided(vector<Collider>&, int& index)` returns `true` on the first intersection, reports the
  hit index and flags both colliders so a bullet is only consumed once. A default-constructed
  collider uses the off-screen rect `(600, 600, 2, 3)` and tag `"noNAme"`.
- **`Bullet`** is polar: it stores an `angle` and increasing/decreasing `radius` around a reference
  point, and `updatePosition(ref)` recomputes `xPos/yPos` and the collider. `Weapon::updateBullets`
  steps radius by `8 * bulletDir` and culls anything outside `[0, 500]`. Bullets are tagged
  (`"playerBullet"`, etc.) and the tag decides what they can kill.
- **`Player`** holds an angle on a circle of radius `200` centred at `(refX, refY)` (the 250/250
  window centre). Left/Right change the angle by `PI * elapsedMs / 600`; Space fires if
  `countFrames > 15`. Its own bullets advance with `bulletDir = -1` (outward).
- **`GyrussEnemy`** orbits its `(_xRefPoint, _yRefPoint)` at `radius 100`, advancing `_dTheta` by
  `0.05` per `move()`. It has two `updateScreen` overloads (vector-of-`Collider` vs
  `deque<Bullet>`); colliding with a `"playerBullet"` sets `_isDead`. The `EnemyType` enum
  (`ships, satellites, asteroids, laser, generator`) selects a texture in the parameterised
  constructor (most currently reuse `game_sprite.png`).
- **`main.cpp` game loop**: shows an animated splash until Enter sets `playGame`; then, per frame,
  it concatenates every enemy's bullets into one vector, updates the player **once** with all of
  them, then updates each enemy with the player's bullets and erases dead ones. (`fitSpriteTo`
  guards against empty textures before scaling.)

## Conventions & gotchas

- **Tab indentation**, tabs inside methods; `using namespace std;` is present in headers.
  Classic `#ifndef`/`#define` header guards.
- **Textures are resolved relative to the process working directory** (`textures/...`), and the
  assets live in `Debug/textures/`. Run the game/demo/tests **from `Debug/`**, which is exactly
  what `make test` does (`cd Debug && ./run_tests`). Running a binary from elsewhere silently fails
  to load sprites.
- `GyrussEnemy::updateScreen` uses a **file-scope `tempTime`** shared by all enemies; it is
  effectively global state and will misbehave with many enemies.
- Collider bounds come from `sprite.getGlobalBounds()`, so they track scale/rotation only after the
  sprite has a texture; empty textures leave stale bounds.
- Keep changes warning-clean: the project builds with `-Wall -Wextra -Wpedantic`.
