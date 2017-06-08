#include "cosmos.h"

//
// common
//
void co_c_error(const char *msg);

void co_c_error(const char *msg) {
    printf("%s\n", msg);
}

//
// parser
//
struct co_token_t *co_token_new(enum co_symbol_t symbol, const char * str, size_t len, size_t begin, size_t end);
bool co_token_free(struct co_token_t *token);

struct co_tokenizer_t *co_tokenizer_new(char *path);
bool co_tokenizer_free(struct co_tokenizer_t *tokenizer);
void co_tokenizer_nextsym(struct co_tokenizer_t *tokenizer);

struct co_parser_t *co_parser_new(struct co_tokenizer_t *tokenizer);
bool co_parser_free(struct co_parser_t *parser);
bool co_parser_accept(struct co_parser_t *parser, enum co_symbol_t symbol);
bool co_parser_expect(struct co_parser_t *parser, enum co_symbol_t symbol);
struct co_ast_t *co_parser_parse(struct co_parser_t *parser);

typedef enum co_symbol_t {
    CO_SYMBOL_ERRORTOKEN,
    CO_SYMBOL_BEGINMARKER,
    CO_SYMBOL_ENDMARKER,
    CO_SYMBOL_NEWLINE,
    CO_SYMBOL_NAME,
    CO_SYMBOL_NUMBER,
    CO_SYMBOL_STRING,
    CO_SYMBOL_LPAR,
    CO_SYMBOL_RPAR,
    CO_SYMBOL_LSQB,
    CO_SYMBOL_RSQB,
    CO_SYMBOL_LBRACE,
    CO_SYMBOL_RBRACE,
    CO_SYMBOL_COLON,
    CO_SYMBOL_COMMA,
    CO_SYMBOL_SEMI,
    CO_SYMBOL_AT,
    CO_SYMBOL_PLUS,
    CO_SYMBOL_MINUS,
    CO_SYMBOL_STAR,
    CO_SYMBOL_SLASH,
    CO_SYMBOL_DOUBLESLASH,
    CO_SYMBOL_VBAR,
    CO_SYMBOL_AMPER,
    CO_SYMBOL_LESS,
    CO_SYMBOL_GREATER,
    CO_SYMBOL_EQUAL,
    CO_SYMBOL_DOT,
    CO_SYMBOL_PERCENT,
    CO_SYMBOL_EQEQUAL,
    CO_SYMBOL_NOTEQUAL,
    CO_SYMBOL_LESSEQUAL,
    CO_SYMBOL_GREATEREQUAL,
    CO_SYMBOL_TILDE,
    CO_SYMBOL_CIRCUMFLEX,
    CO_SYMBOL_LEFTSHIFT,
    CO_SYMBOL_RIGHTSHIFT,
    CO_SYMBOL_DOUBLESTAR,
    CO_SYMBOL_PLUSEQUAL,
    CO_SYMBOL_MINEQUAL,
    CO_SYMBOL_STAREQUAL,
    CO_SYMBOL_SLASHEQUAL,
    CO_SYMBOL_PERCENTEQUAL,
    CO_SYMBOL_AMPEREQUAL,
    CO_SYMBOL_VBAREQUAL,
    CO_SYMBOL_CIRCUMFLEXEQUAL,
    CO_SYMBOL_LEFTSHIFTEQUAL,
    CO_SYMBOL_RIGHTSHIFTEQUAL,
    CO_SYMBOL_DOUBLESTAREQUAL,
    CO_SYMBOL_DOUBLESLASHEQUAL
} co_symbol_t;

typedef struct co_token_t {
    enum co_symbol_t symbol;
    const char * str;
    size_t len;
    size_t begin;
    size_t end;
} co_token_t;

typedef struct co_tokenizer_t {
    char *path;
    char *source_code;
    size_t source_code_len;
    struct co_token_t *token;
} co_tokenizer_t;

typedef struct co_ast_t {
    void * dummy;
} co_ast_t;

typedef struct co_parser_t {
    struct co_tokenizer_t *tokenizer;
} co_parser_t;

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
    struct co_tokenizer_t *tokenizer = co_tokenizer_new("example_fp_0.co");
    struct co_parser_t *parser = co_parser_new(tokenizer);
    struct co_ast_t *ast = co_parser_parse(parser);
    co_parser_free(parser);
    co_tokenizer_free(tokenizer);
    return EXIT_SUCCESS;
}
