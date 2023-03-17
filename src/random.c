#include "random.h"

static XorshiftState state;

void setXorshiftState(uint64_t first, uint64_t second) {
    state.x[0] = first;
    state.x[1] = second;
}

uint64_t xorshift() {
    uint64_t t = state.x[0];
    uint64_t s = state.x[1];
    state.x[0] = s;
    t ^= t << 23;
    t ^= t >> 18;
    t ^= s ^ (s >> 5);
    state.x[1] = t;
    return t + s;
}

double xorshiftDouble() {
    return (double) xorshift() / (0x8000000000000000u * 2.0);
}