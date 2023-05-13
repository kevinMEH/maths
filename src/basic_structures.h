#ifndef BASIC_STRUCTURES
#define BASIC_STRUCTURES

typedef union Pair {
    struct { double x; double y; };
    struct { double first; double second; };
} Pair;

typedef Pair Point;

#endif