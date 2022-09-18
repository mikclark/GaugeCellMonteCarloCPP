COMPILER = g++
FLAGS = -g -O2

COMMON_FILES = state.cpp state.h potential_by_atom_types.cpp potential_by_atom_types.h lj.h
TEST_FILES = test.cpp test/test_state.cpp test/test_state.h test/test_potential.cpp test/test_potential.h $(COMMON_FILES)
MAIN_FILES = main.cpp $(COMMON_FILES)

test.tsk: $(TEST_FILES)
	$(COMPILER) $(FLAGS) -o test.tsk $(TEST_FILES) -I. -Itest

test_speed.tsk: test_speed.cpp $(COMMON_FILES)
	$(COMPILER) $(FLAGS) -o test_speed.tsk test_speed.cpp $(COMMON_FILES)

main.tsk: $(MAIN_FILES)
	$(COMPILER) $(FLAGS) -o main.tsk $(MAIN_FILES)
