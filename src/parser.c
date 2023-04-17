#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "parser.h"
#include "lexer.h"

typedef struct {
    Token current;
    Token previous;

    bool hadError;
    bool panicMode;
} Parser;

Parser parser;
Chunk *parsingChunk;

static Chunk *currentChunk() {
    return parsingChunk;
}

static void errorAt(Token *token, const char *message) {
    if(parser.panicMode) return;

    parser.panicMode = true;

    fprintf(stderr, "[line %d] Error", token->line);

    if(token->type != TOKEN_ERROR) {
        if(token->type == TOKEN_EOF)
            fprintf(stderr, " at end");
        else 
            fprintf(stderr, " at '%.*s'", token->length, token->start);
    }

    fprintf(stderr, ": %s\n", message);

    parser.hadError = true;
}

static void error(const char *message) {
    errorAt(&parser.previous, message);
}

static void errorAtCurrent(const char *message) {
    errorAt(&parser.current, message);
}

static void advance() {
    parser.previous = parser.current;

    while(true) {
        parser.current = scanToken();
        if(parser.current.type != TOKEN_ERROR) break;

        errorAtCurrent(parser.current.start);
    }
}

static void consume(TokenType type, const char *message) {
    if(parser.current.type == type) {
        advance();
        return;
    }

    errorAtCurrent(message);
}

static void emitByte(uint8_t byte) {
    writeChunk(currentChunk(), byte, parser.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

static void emitReturn() {
    emitByte(OP_RETURN);
}

static void endParser() {
    emitReturn();
}

static void expression() {
    // to be continued...
}

bool parse(const char *source, Chunk *chunk) {
    initLexer(source);

    parsingChunk = chunk;

    parser.hadError     = false;
    parser.panicMode    = false;

    advance();
    
    expression();

    consume(TOKEN_EOF, "Expect end of expression");

    endParser();

    return !parser.hadError;
}