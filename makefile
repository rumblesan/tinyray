CC                = clang
CFLAGS            = -Wall
LDFLAGS           = -c
VPATH             = src src/core src/tests
LIBS              = 

TEST_CFLAGS       = $(CFLAGS) -fprofile-instr-generate -fcoverage-mapping
TEST_LIBS         =

LCOV_FLAGS        = -c -b ./ -d ./

MAIN_BUILD_DIR    = build/main
TEST_BUILD_DIR    = build/tests
HEADER_DIRS       = include
CORE_SRC_DIRS     = $(shell find src/core -type d)
TEST_SRC_DIRS     = $(shell find src/tests -type d)
LIB_SRC_DIRS      = $(shell find src/libs -type d)

COVERAGE_DIR      = coverage
COVERAGE_FILE     = default.profraw

INCLUDES          = $(addprefix -I, $(HEADER_DIRS))

CORE_SOURCES      = $(foreach dir,$(CORE_SRC_DIRS),$(wildcard $(dir)/*.c))
TEST_SOURCES      = $(foreach dir,$(TEST_SRC_DIRS),$(wildcard $(dir)/*.c)) $(CORE_SOURCES)
LIB_SOURCES       = $(foreach dir,$(LIB_SRC_DIRS),$(wildcard $(dir)/*.c))
MAIN_SOURCES      = main.c $(CORE_SOURCES) $(LIB_SOURCES)

MAIN_OBJECTS      = $(addprefix $(MAIN_BUILD_DIR)/, $(MAIN_SOURCES:.c=.o))
TEST_OBJECTS      = $(addprefix $(TEST_BUILD_DIR)/, $(TEST_SOURCES:.c=.o))

EXECUTABLE        = fray
TEST_EXECUTABLE   = $(addprefix $(TEST_BUILD_DIR)/, test_$(EXECUTABLE))

.PHONY: clean echo

all: $(EXECUTABLE)

tests: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

coverage: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)
	xcrun llvm-profdata merge -o $(COVERAGE_DIR)/test_fray.profdata $(COVERAGE_FILE)
	xcrun llvm-cov show $(TEST_EXECUTABLE) -instr-profile=$(COVERAGE_DIR)/test_fray.profdata

$(MAIN_BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) $(CFLAGS) $(INCLUDES) $< -o $@

$(TEST_BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_CFLAGS) $(INCLUDES) $< -o $@

$(EXECUTABLE): $(MAIN_OBJECTS)
	@$(CC) $(CFLAGS) $(MAIN_OBJECTS) -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	@$(CC) $(TEST_LIBS) $(TEST_CFLAGS) $(TEST_OBJECTS) -o $@

clean:
	rm -rf $(MAIN_BUILD_DIR)/* $(EXECUTABLE)
	rm -rf $(TEST_BUILD_DIR)/*

