#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

// function to disassemble all of the instructions in the entire chunk
void disassembleChunk(Chunk *chunk, const char *name);

// function to disassemble the instruction at given offset and get the offset for next instruction
int disassembleInstruction(Chunk *chunk, int offset);

#endif