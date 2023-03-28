#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char *name) {
    // print a little header
    printf("== %s ==\n", name);

    int offset = 0;

    // diassemble until the offset reach the end of the chunk
    while (offset < chunk->count) {
        offset = disassembleInstruction(chunk, offset);
    }
}

// helper function to disassemble constant instruction
static int constantInstruction(const char *name, Chunk *chunk, int offset) {
    // read the index of constant from the next offset
    uint8_t constant = chunk->code[offset + 1];

    // print out the name of opcode and the index of constant
    printf("%-16s %4d '", name, constant);

    // print the value of the constant by extracting it from the constant list using the index
    printValue(chunk->constants.values[constant]);
    printf("'\n");

    // return the offset to next instruction, not the next byte because it is our index for the constant
    return offset + 2;
}

// helper function to disassemble simple instruction
static int simpleInstruction(const char *name, int offset) {
    // print the name of opcode and return the offset for next byte
    printf("%s\n", name);

    return offset + 1;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    // first print the byte offset
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
        // show a | for any instruction that come from same source line as the preceeding one
        printf("   | ");
    else
        // show the current source line
        printf("%04d ", chunk->lines[offset]);

    // read a byte (opcode) from bytecode at given offset
    uint8_t instruction = chunk->code[offset];

    // switch on that instruction and dispatch to a helper function
    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);

        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);

        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);

        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);

        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);

        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);

        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);

        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}