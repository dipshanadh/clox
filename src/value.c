#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray *array)
{
    // zero out all the fields of the struct
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void freeValueArray(ValueArray *array)
{
    // first deallocate all the memory
    FREE_ARRAY(Value, array->values, array->count);

    // then reset the field of the ValueArray struct
    initValueArray(array);
}

void writeValueArray(ValueArray *array, Value value)
{
    // grow the array if its doesn't have capacity for the new value
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;

        // set the new capacity
        array->capacity = GROW_CAPACITY(oldCapacity);

        // and grow the array of values
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }

    // store the new value to the array
    array->values[array->count] = value;

    // then increase its count
    array->count++;
}

void printValue(Value value)
{
    printf("%g", value);
}