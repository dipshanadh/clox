#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
    // initialize the VM
    initVM();

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

    // command the vm to interpret the chunk of bytecode
    interpret(&chunk);

    // pass the chunk to the disassembler for some debugging
    disassembleChunk(&chunk, "test chunk");

    // free the VM
    freeVM();

    // free the chunk
    freeChunk(&chunk);

    return 0;
}