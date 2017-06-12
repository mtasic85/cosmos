#include "cosmos.h"

//
// common
//
void co_c_error(const char *msg) {
    printf("%s\n", msg);
}

//
// parser
//
struct co_token_t *co_token_new(enum co_symbol_t symbol, const char * str, size_t len, size_t begin, size_t end) {
    struct co_token_t *token = NULL;

    if (!(token = malloc(sizeof(struct co_token_t)))) {
        co_c_error("MemoryError: Could not allocate token.");
        return NULL;
    }

    token->symbol = symbol;
    token->str = str;
    token->len = len;
    token->begin = begin;
    token->end = end;
    return token;
}

bool co_token_free(struct co_token_t *token) {
    if (!token) {
        co_c_error("MemoryError: Token is null.");
        return false;
    }

    free(token);
    return true;
}

struct co_tokenizer_t *co_tokenizer_new(char *path) {
    struct co_tokenizer_t *tokenizer = NULL;

    if (!(tokenizer = malloc(sizeof(struct co_tokenizer_t)))) {
        co_c_error("MemoryError: Could not allocate tokenizer.");
        return NULL;
    }

    FILE *f = fopen(path, "r");

    if (!f) {
        co_c_error("IOError: Could not open file.");
        free(tokenizer);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size_t source_code_len = ftell(f);
    char *source_code = malloc(source_code_len * sizeof(char));
    fseek(f, 0, SEEK_SET);
    size_t read_len = fread(source_code, sizeof(char), source_code_len, f);
    fclose(f);

    // FIXME: compare read_len and source_code_len

    tokenizer->path = path;
    tokenizer->source_code = source_code;
    tokenizer->source_code_len = source_code_len;
    return tokenizer;
}

bool co_tokenizer_free(struct co_tokenizer_t *tokenizer) {
    if (!tokenizer) {
        co_c_error("MemoryError: Tokenizer is null.");
        return false;
    }

    if (!tokenizer->source_code) {
        co_c_error("MemoryError: Tokenizer's source code is null.");
        return false;
    }

    free(tokenizer->source_code);
    free(tokenizer);
    return true;
}

void co_tokenizer_nextsym(struct co_tokenizer_t *tokenizer) {

}

struct co_parser_t *co_parser_new(struct co_tokenizer_t *tokenizer) {
    struct co_parser_t *parser = NULL;

    if (!(parser = malloc(sizeof(struct co_parser_t)))) {
        co_c_error("MemoryError: Could not allocate parser.");
        return NULL;
    }

    parser->tokenizer = tokenizer;
    return parser;
}

bool co_parser_free(struct co_parser_t *parser) {
    if (!parser) {
        co_c_error("MemoryError: Parser is null.");
        return false;
    }

    free(parser);
    return true;
}

bool co_parser_accept(struct co_parser_t *parser, enum co_symbol_t symbol) {
    return false;
}

bool co_parser_expect(struct co_parser_t *parser, enum co_symbol_t symbol) {
    return false;
}

struct co_ast_t *co_parser_parse(struct co_parser_t *parser) {
    return NULL;
}

//
// main
//
int main(int argc, char **argv) {
    struct co_tokenizer_t * tokenizer = co_tokenizer_new("example_hello_world.co");
    struct co_parser_t * parser = co_parser_new(tokenizer);
    struct co_ast_t * ast = co_parser_parse(parser);
    co_parser_free(parser);
    co_tokenizer_free(tokenizer);
    return EXIT_SUCCESS;
}
