#ifndef clox_parser_h
#define clox_parser_h

#include "vm.h"

bool parse(const char *source, Chunk *chunk);

#endif