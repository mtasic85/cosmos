#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//
// c_storage
//
struct c_storage_t;

typedef struct c_storage_t {
    size_t cap;
    unsigned char *data;
} c_storage_t;

struct c_storage_t *co_c_storage_new(size_t cap);
bool co_c_storage_free(struct c_storage_t *storage);


//
// c_array
//
struct co_c_array_t;

typedef struct co_c_array_t {
    size_t rc;
    size_t len;
    unsigned char *data;
    struct c_storage_t *storage;
} co_c_array_t;

struct co_c_array_t *co_c_array_new(size_t item_size, size_t cap);
bool co_c_array_free(struct co_c_array_t *array);
void c_c_array_ref(struct co_c_array_t *array);
void c_c_array_unref(struct co_c_array_t *array);
int co_c_array_cmp(struct co_c_array_t *array, struct co_c_array_t *other);
int co_c_array_cmp_with_cstr(struct co_c_array_t *array, size_t len, char *items);
int co_c_array_cmp_with_char(struct co_c_array_t *array, char *items);
struct co_c_array_t *co_c_array_append(struct co_c_array_t *array, void *value);
bool co_c_array_mut_append(struct co_c_array_t *array, void *value);
struct co_c_array_t *co_c_array_remove(struct co_c_array_t *array, void *value);
bool co_c_array_mut_remove(struct co_c_array_t *array, void *value);
int co_c_array_index(struct co_c_array_t *array, void *value);
void *co_c_array_get(struct co_c_array_t *array, size_t index);
struct co_c_array_t *co_c_array_set(struct co_c_array_t *array, size_t index, void *value);
bool co_c_array_mut_set(struct co_c_array_t *array, size_t index, void *value);
struct co_c_array_t *co_c_array_del(struct co_c_array_t *array, size_t index);
bool co_c_array_mul_del(struct co_c_array_t *array, size_t index);
struct co_c_array_t *co_c_array_clear(struct co_c_array_t *array);
bool co_c_array_mul_clear(struct co_c_array_t *array);

//
// c_map
//
typedef struct co_c_map_t {
    size_t rc;
    size_t len;
    unsigned char *data;
    struct c_storage_t *storage;
} co_c_map_t;

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
enum co_symbol_t;
struct co_token_t;
struct co_tokenizer_t;
struct co_ast_t;
struct co_parser_t;

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
    CO_ERRORTOKEN,
    CO_BEGINMARKER,
    CO_ENDMARKER,
    CO_NEWLINE,
    CO_NAME,
    CO_NUMBER,
    CO_STRING,
    CO_LPAR,
    CO_RPAR,
    CO_LSQB,
    CO_RSQB,
    CO_LBRACE,
    CO_RBRACE,
    CO_COLON,
    CO_COMMA,
    CO_SEMI,
    CO_AT,
    CO_PLUS,
    CO_MINUS,
    CO_STAR,
    CO_SLASH,
    CO_DOUBLESLASH,
    CO_VBAR,
    CO_AMPER,
    CO_LESS,
    CO_GREATER,
    CO_EQUAL,
    CO_DOT,
    CO_PERCENT,
    CO_EQEQUAL,
    CO_NOTEQUAL,
    CO_LESSEQUAL,
    CO_GREATEREQUAL,
    CO_TILDE,
    CO_CIRCUMFLEX,
    CO_LEFTSHIFT,
    CO_RIGHTSHIFT,
    CO_DOUBLESTAR,
    CO_PLUSEQUAL,
    CO_MINEQUAL,
    CO_STAREQUAL,
    CO_SLASHEQUAL,
    CO_PERCENTEQUAL,
    CO_AMPEREQUAL,
    CO_VBAREQUAL,
    CO_CIRCUMFLEXEQUAL,
    CO_LEFTSHIFTEQUAL,
    CO_RIGHTSHIFTEQUAL,
    CO_DOUBLESTAREQUAL,
    CO_DOUBLESLASHEQUAL
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
