#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char *argv[])
{
    // create and initialize a chunk
    Chunk chunk;
    initChunk(&chunk);

    // add a constant to the constant list
    int constant = addConstant(&chunk, 1.2);

    // write constant instruction opcode to the chunk followed by the constant index
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    // write return instruction opcode to the chunk
    writeChunk(&chunk, OP_RETURN, 123);

    // pass the chunk to the disassembler
    disassembleChunk(&chunk, "test chunk");

    // free the chunk
    freeChunk(&chunk);

    return 0;
}