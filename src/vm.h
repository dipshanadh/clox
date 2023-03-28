#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

// maximum no. of values we can store on stack
#define STACK_MAX 256

typedef struct
{
    Chunk *chunk;

    // instruction pointer to keep track where the VM is
    uint8_t *ip;

    Value stack[STACK_MAX];
    Value *stackTop;
} VM;

// vm responds with a value from this enum
typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

// function to initialize the VM
void initVM();

// function to free the VM
void freeVM();

// function to interpret chunk of bytecode
InterpretResult interpret(Chunk *chunk);

// function to push a new value to the stack
void push(Value value);

// function to pop a value off the stack
Value pop();

#endif