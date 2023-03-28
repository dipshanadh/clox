#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

// helper function to reset stack (set stackTop to beginning of stack array)
static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

static InterpretResult run() {
    // a macro to read currently pointed byte and and then increment the ip
    #define READ_BYTE() (*vm.ip++)

    // a macro to read the index from bytecode and look up for corresponding value in constant table
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    while (true)
    {
        // if DEBUG_TRACE_EXECUTION flag is defined, enable logging
        #ifdef DEBUG_TRACE_EXECUTION
        // stack tracing
        for (Value *slot = vm.stack; slot < vm.stackTop; slot++)
        {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }

        // subtract adress of code from ip to get the relative offset from beginning of bytecode
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif

        // read the current byte
        uint8_t instruction = READ_BYTE();

        switch (instruction)
        {
            case OP_CONSTANT:
                // read the constant the push to the stack
                Value constant = READ_CONSTANT();
                push(constant);

                break;

            case OP_RETURN:
                printValue(pop());
                printf("\n");

                return INTERPRET_OK;
        }
    }

    // to make the scoping more explicit, undefine these macros
    #undef READ_BYTE
    #undef READ_CONSTANT
}

void freeVM() { }

void push(Value value) {
    // store the value at the top of the stack
    *vm.stackTop = value;

    // then increment the pointer to the next unused slot
    vm.stackTop++;
}

Value pop() {
    // decrement the pointer back to the most recent used slot
    vm.stackTop--;

    // also return the value at that index
    return *vm.stackTop;
}

InterpretResult interpret(Chunk *chunk) {
    // store the chunk being executed in the vm and call run()
    vm.chunk = chunk;

    // put the instruction pointer to the beginning of the bytecode
    vm.ip = vm.chunk->code;

    return run();
}