# create so.

g++ -shared -o _evolution.so -fPIC \
    src/experiments/*.cpp \
    src/evolution/*.cpp \
    src/evolution/component_types/*.cpp
