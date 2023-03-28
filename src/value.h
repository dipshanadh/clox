#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

// struct to wrap a pointer to an array of values along with its allocated capacity and the no. of elements in use
typedef struct {
    int capacity;
    int count;
    Value *values;
} ValueArray;

// function to initialize / reset a value array
void initValueArray(ValueArray *array);

// function to write a value to the value array
void writeValueArray(ValueArray *array, Value value);

// function to free a value array
void freeValueArray(ValueArray *array);

// functino to print a value
void printValue(Value value);

#endif