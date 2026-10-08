CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

BIN_DIR  = Debug
CORE_SRC = Collider.cpp Player.cpp Weapon.cpp GyrussEnemy.cpp
GAME_SRC = main.cpp $(CORE_SRC)
DEMO_SRC = mainEnemy.cpp $(CORE_SRC)
TEST_SRC = $(wildcard tests/*.cpp) $(CORE_SRC)

.PHONY: all game demo test clean

all: game demo

game: $(BIN_DIR)/Gyruss
demo: $(BIN_DIR)/GyrussEnemyDemo

$(BIN_DIR)/Gyruss: $(GAME_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(GAME_SRC) -o $@ $(SFML_LIBS)

$(BIN_DIR)/GyrussEnemyDemo: $(DEMO_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(DEMO_SRC) -o $@ $(SFML_LIBS)

# Tests create SFML textures, which need an X display. When headless we start
# one automatically with xvfb-run (install: apt-get install xvfb xauth).
test: $(BIN_DIR)/run_tests
	@if [ -z "$$DISPLAY" ] && command -v xvfb-run >/dev/null 2>&1; then \
		cd $(BIN_DIR) && xvfb-run -a ./run_tests; \
	else \
		cd $(BIN_DIR) && ./run_tests; \
	fi

$(BIN_DIR)/run_tests: $(TEST_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I. -Itests $(TEST_SRC) -o $@ $(SFML_LIBS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/Gyruss $(BIN_DIR)/GyrussEnemyDemo $(BIN_DIR)/run_tests $(BIN_DIR)/*.o
