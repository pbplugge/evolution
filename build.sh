# create so.

g++ -shared -o _evolution.so -fPIC \
    src/experiments/adding_two_numbers.cpp \
    src/experiments/test_mutations.cpp \
    src/experiments/complex_formula.cpp \
    src/evolution/component.cpp \
    src/evolution/component_inputnode.cpp \
    src/evolution/component_library.cpp \
    src/evolution/component_manager.cpp \
    src/evolution/component_outputnode.cpp \
    src/evolution/config.cpp \
    src/evolution/evolutionary_program.cpp \
    src/evolution/fitness.cpp \
    src/evolution/hall_of_fame.cpp \
    src/evolution/individual.cpp \
    src/evolution/population.cpp \
    src/evolution/shared_library.cpp \
    src/evolution/statistics.cpp \
    src/evolution/thread.cpp \
    src/evolution/thread_manager.cpp
