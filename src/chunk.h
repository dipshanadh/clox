#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// one-byte operation code that each instruction have
typedef enum
{
    OP_RETURN,
    OP_CONSTANT,
} OpCode;

// struct to wrap a pointer to an array of bytecode along with its allocated capacity and the no. of elements in use
typedef struct
{
    // no. of allocated entries in use
    int count;

    // no. of elements in the array we have allocated
    int capacity;

    // array of instructions / bytecode
    uint8_t *code;

    // array to track the current source line
    int *lines;

    // array of constants
    ValueArray constants;
} Chunk;

// function to initialize / reset a chunk
void initChunk(Chunk *chunk);

// function to write a bytecode to a chunk
void writeChunk(Chunk *chunk, uint8_t byte, int line);

// function to add a value to the constant list
int addConstant(Chunk *chunk, Value value);

// function to free a chunk
void freeChunk(Chunk *chunk);

#endif