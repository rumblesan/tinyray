CC                = clang
CFLAGS            = -Wall
LDFLAGS           = -c
SDLFLAGS          = `sdl-config --cflags --libs`
VPATH             = src src/core src/tests
LIBS              = 

TEST_CFLAGS       = --coverage $(CFLAGS)
TEST_LIBS         = -lprofile_rt

LCOV_FLAGS        = -c -b ./ -d ./

MAIN_BUILD_DIR    = build/main
TEST_BUILD_DIR    = build/tests
HEADER_DIRS       = include
COVERAGE_DIR      = coverage
COVERAGE_FILE     = $(COVERAGE_DIR)/coverage.info

INCLUDES          = $(addprefix -I, $(HEADER_DIRS))

CORE_SOURCES      = $(notdir $(wildcard src/core/*.c))
TEST_SOURCES      = $(notdir $(wildcard src/tests/*.c)) $(CORE_SOURCES)
MAIN_SOURCES      = main.c $(CORE_SOURCES)

MAIN_OBJECTS      = $(addprefix $(MAIN_BUILD_DIR)/, $(MAIN_SOURCES:.c=.o))
TEST_OBJECTS      = $(addprefix $(TEST_BUILD_DIR)/, $(TEST_SOURCES:.c=.o))

EXECUTABLE        = fray
TEST_EXECUTABLE   = $(addprefix $(TEST_BUILD_DIR)/, test_$(EXECUTABLE))

all: $(EXECUTABLE)

tests: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

coverage: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)
	lcov $(LCOV_FLAGS) -o $(COVERAGE_FILE)
	lcov -r $(COVERAGE_FILE) test\* -o $(COVERAGE_FILE)
	genhtml $(COVERAGE_FILE) -o $(COVERAGE_DIR)

$(MAIN_BUILD_DIR)/%.o: %.c
	$(CC) $(LDFLAGS) $(CFLAGS) $(INCLUDES) $< -o $@

$(TEST_BUILD_DIR)/%.o: %.c
	$(CC) $(LDFLAGS) $(TEST_CFLAGS) $(INCLUDES) $< -o $@

$(EXECUTABLE): $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) $(SDLFLAGS) $(MAIN_OBJECTS) -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(TEST_LIBS) $(TEST_CFLAGS) $(TEST_OBJECTS) -o $@

clean:
	rm -rf $(MAIN_BUILD_DIR)/* $(EXECUTABLE)
	rm -rf $(TEST_BUILD_DIR)/*

