#ifndef CO_COSMOS_H
#define CO_COSMOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//
// common
//
void co_c_error(const char *msg);

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


//
// vm
//
#define CO_OBJ struct co_object_t *

#define CO_CAK \
    struct co_ctx_t *ctx, struct co_object_t *args, struct co_object_t *kwargs

enum co_symbol_t;
struct co_token_t;
struct co_tokenizer_t;
struct co_ast_t;
struct co_parser_t;
struct co_ctx_t;
struct co_vm_t;

enum co_type_t;
union co_value_t;
typedef _Bool co_bool_t;
typedef int64_t co_int_t;
typedef double co_float_t;
struct co_bytes_t;
struct co_str_t;
struct co_list_t;
struct co_set_t;
struct co_dict_t;
struct co_code_t;
struct co_function_t;
struct co_object_t;

typedef struct co_vm_t {
    // current working direcotry, initial file, etc
    void * dummy;
} co_vm_t;

typedef struct co_ctx_t {
    struct co_vm_t * vm;
    struct co_object_t * globals;
    struct co_object_t * locals;
} co_ctx_t;

typedef enum co_type_t {
    CO_TYPE_NULL,
    CO_TYPE_BOOL,
    CO_TYPE_INT,
    CO_TYPE_FLOAT,
    CO_TYPE_BYTES,
    CO_TYPE_STR,
    CO_TYPE_LIST,
    CO_TYPE_SET,
    CO_TYPE_DICT,
    CO_TYPE_CODE,
    CO_TYPE_FUNCTION,
    CO_TYPE_C_DATA
} co_type_t;

typedef union co_value_t {
    co_bool_t * bool_;
    co_int_t * int_;
    co_float_t * float_;
    struct co_bytes_t * bytes;
    struct co_str_t * str;
    struct co_list_t * list;
    struct co_set_t * set;
    struct co_dict_t * dict;
    struct co_code_t * code;
    struct co_function_t * function;
    void * c_data;
} co_value_t;

typedef struct co_object_t {
    size_t rc;  // reference count
    enum co_type_t type;
    union co_value_t value;
} co_object_t;

typedef struct co_bytes_t {
    size_t len;
    char * items;
} co_bytes_t;

typedef struct co_str_t {
    size_t len;
    char * items;
} co_str_t;

typedef struct co_list_t {
    size_t len;
    size_t cap;
    struct co_object_t ** items;
} co_list_t;

typedef struct co_set_t {
    size_t fill;
    size_t used;
    size_t mask;
    struct co_object_t ** items;
} co_set_t;

typedef struct co_dict_item_t {
    struct co_object_t * key;
    struct co_object_t * value;
} co_dict_item_t;

typedef struct co_dict_t {
    size_t fill;
    size_t used;
    size_t mask;
    struct co_dict_item_t ** items;
} co_dict_t;

typedef struct co_code_t {
    char * file_path;
    size_t len_bytecode;
    char * bytecode;
    size_t len_line_numbers;
    int * line_numbers;
} co_code_t;

typedef struct co_function_t {
    struct co_object_t * name;
    struct co_object_t * params;
    struct co_object_t * kwparams;
    struct co_object_t * code;
} co_function_t;

CO_OBJ co_null_init(CO_CAK);
CO_OBJ co_null_del(CO_CAK);
CO_OBJ co_null_repr(CO_CAK);
CO_OBJ co_null_not(CO_CAK);
CO_OBJ co_null_truth(CO_CAK);
CO_OBJ co_null_hash(CO_CAK);

CO_OBJ co_bool_init(CO_CAK);
CO_OBJ co_bool_del(CO_CAK);
CO_OBJ co_bool_repr(CO_CAK);
CO_OBJ co_bool_not(CO_CAK);
CO_OBJ co_bool_truth(CO_CAK);
CO_OBJ co_bool_hash(CO_CAK);
CO_OBJ co_bool_and(CO_CAK);
CO_OBJ co_bool_or(CO_CAK);
CO_OBJ co_bool_xor(CO_CAK);

CO_OBJ co_int_init(CO_CAK);
CO_OBJ co_int_del(CO_CAK);
CO_OBJ co_int_repr(CO_CAK);
CO_OBJ co_int_not(CO_CAK);
CO_OBJ co_int_truth(CO_CAK);
CO_OBJ co_int_hash(CO_CAK);
CO_OBJ co_int_neg(CO_CAK);
CO_OBJ co_int_pos(CO_CAK);
CO_OBJ co_int_add(CO_CAK);
CO_OBJ co_int_sub(CO_CAK);
CO_OBJ co_int_mul(CO_CAK);
CO_OBJ co_int_div(CO_CAK);
CO_OBJ co_int_ddiv(CO_CAK);
CO_OBJ co_int_mod(CO_CAK);
CO_OBJ co_int_pow(CO_CAK);
CO_OBJ co_int_inv(CO_CAK);
CO_OBJ co_int_and(CO_CAK);
CO_OBJ co_int_or(CO_CAK);
CO_OBJ co_int_xor(CO_CAK);
CO_OBJ co_int_lshift(CO_CAK);
CO_OBJ co_int_rshift(CO_CAK);
CO_OBJ co_int_eq(CO_CAK);
CO_OBJ co_int_ne(CO_CAK);
CO_OBJ co_int_lt(CO_CAK);
CO_OBJ co_int_le(CO_CAK);
CO_OBJ co_int_gt(CO_CAK);
CO_OBJ co_int_ge(CO_CAK);

CO_OBJ co_float_init(CO_CAK);
CO_OBJ co_float_del(CO_CAK);
CO_OBJ co_float_repr(CO_CAK);
CO_OBJ co_float_not(CO_CAK);
CO_OBJ co_float_truth(CO_CAK);
CO_OBJ co_float_hash(CO_CAK);
CO_OBJ co_float_neg(CO_CAK);
CO_OBJ co_float_pos(CO_CAK);
CO_OBJ co_float_add(CO_CAK);
CO_OBJ co_float_sub(CO_CAK);
CO_OBJ co_float_mul(CO_CAK);
CO_OBJ co_float_div(CO_CAK);
CO_OBJ co_float_ddiv(CO_CAK);
CO_OBJ co_float_mod(CO_CAK);
CO_OBJ co_float_pow(CO_CAK);
CO_OBJ co_float_eq(CO_CAK);
CO_OBJ co_float_ne(CO_CAK);
CO_OBJ co_float_lt(CO_CAK);
CO_OBJ co_float_le(CO_CAK);
CO_OBJ co_float_gt(CO_CAK);
CO_OBJ co_float_ge(CO_CAK);

CO_OBJ co_bytes_init(CO_CAK);
CO_OBJ co_bytes_del(CO_CAK);
CO_OBJ co_bytes_repr(CO_CAK);
CO_OBJ co_bytes_not(CO_CAK);
CO_OBJ co_bytes_truth(CO_CAK);
CO_OBJ co_bytes_hash(CO_CAK);
CO_OBJ co_bytes_add(CO_CAK);
CO_OBJ co_bytes_split(CO_CAK);
CO_OBJ co_bytes_join(CO_CAK);
CO_OBJ co_bytes_index(CO_CAK);
CO_OBJ co_bytes_getitem(CO_CAK);
CO_OBJ co_bytes_setitem(CO_CAK);
CO_OBJ co_bytes_delitem(CO_CAK);
CO_OBJ co_bytes_iter(CO_CAK);
CO_OBJ co_bytes_eq(CO_CAK);
CO_OBJ co_bytes_ne(CO_CAK);
CO_OBJ co_bytes_lt(CO_CAK);
CO_OBJ co_bytes_le(CO_CAK);
CO_OBJ co_bytes_gt(CO_CAK);
CO_OBJ co_bytes_ge(CO_CAK);
CO_OBJ co_bytes_encode(CO_CAK);
CO_OBJ co_bytes_pack(CO_CAK);
CO_OBJ co_bytes_unpack(CO_CAK);

CO_OBJ co_str_init(CO_CAK);
CO_OBJ co_str_del(CO_CAK);
CO_OBJ co_str_repr(CO_CAK);
CO_OBJ co_str_not(CO_CAK);
CO_OBJ co_str_truth(CO_CAK);
CO_OBJ co_str_hash(CO_CAK);
CO_OBJ co_str_add(CO_CAK);
CO_OBJ co_str_split(CO_CAK);
CO_OBJ co_str_join(CO_CAK);
CO_OBJ co_str_index(CO_CAK);
CO_OBJ co_str_getitem(CO_CAK);
CO_OBJ co_str_setitem(CO_CAK);
CO_OBJ co_str_delitem(CO_CAK);
CO_OBJ co_str_iter(CO_CAK);
CO_OBJ co_str_eq(CO_CAK);
CO_OBJ co_str_ne(CO_CAK);
CO_OBJ co_str_lt(CO_CAK);
CO_OBJ co_str_le(CO_CAK);
CO_OBJ co_str_gt(CO_CAK);
CO_OBJ co_str_ge(CO_CAK);
CO_OBJ co_str_decode(CO_CAK);

CO_OBJ co_list_init(CO_CAK);
CO_OBJ co_list_del(CO_CAK);
CO_OBJ co_list_repr(CO_CAK);
CO_OBJ co_list_not(CO_CAK);
CO_OBJ co_list_truth(CO_CAK);
CO_OBJ co_list_hash(CO_CAK);
CO_OBJ co_list_add(CO_CAK);
CO_OBJ co_list_getitem(CO_CAK);
CO_OBJ co_list_setitem(CO_CAK);
CO_OBJ co_list_delitem(CO_CAK);
CO_OBJ co_list_hasitem(CO_CAK);
CO_OBJ co_list_iter(CO_CAK);
CO_OBJ co_list_eq(CO_CAK);
CO_OBJ co_list_ne(CO_CAK);
CO_OBJ co_list_lt(CO_CAK);
CO_OBJ co_list_le(CO_CAK);
CO_OBJ co_list_gt(CO_CAK);
CO_OBJ co_list_ge(CO_CAK);

CO_OBJ co_set_init(CO_CAK);
CO_OBJ co_set_del(CO_CAK);
CO_OBJ co_set_repr(CO_CAK);
CO_OBJ co_set_not(CO_CAK);
CO_OBJ co_set_truth(CO_CAK);
CO_OBJ co_set_hash(CO_CAK);
CO_OBJ co_set_add(CO_CAK);
CO_OBJ co_set_getitem(CO_CAK);
CO_OBJ co_set_setitem(CO_CAK);
CO_OBJ co_set_delitem(CO_CAK);
CO_OBJ co_set_hasitem(CO_CAK);
CO_OBJ co_set_iter(CO_CAK);
CO_OBJ co_set_eq(CO_CAK);
CO_OBJ co_set_ne(CO_CAK);
CO_OBJ co_set_lt(CO_CAK);
CO_OBJ co_set_le(CO_CAK);
CO_OBJ co_set_gt(CO_CAK);
CO_OBJ co_set_ge(CO_CAK);

CO_OBJ co_dict_init(CO_CAK);
CO_OBJ co_dict_del(CO_CAK);
CO_OBJ co_dict_repr(CO_CAK);
CO_OBJ co_dict_not(CO_CAK);
CO_OBJ co_dict_truth(CO_CAK);
CO_OBJ co_dict_hash(CO_CAK);
CO_OBJ co_dict_add(CO_CAK);
CO_OBJ co_dict_getitem(CO_CAK);
CO_OBJ co_dict_setitem(CO_CAK);
CO_OBJ co_dict_delitem(CO_CAK);
CO_OBJ co_dict_hasitem(CO_CAK);
CO_OBJ co_dict_iter(CO_CAK);
CO_OBJ co_dict_eq(CO_CAK);
CO_OBJ co_dict_ne(CO_CAK);
CO_OBJ co_dict_lt(CO_CAK);
CO_OBJ co_dict_le(CO_CAK);
CO_OBJ co_dict_gt(CO_CAK);
CO_OBJ co_dict_ge(CO_CAK);

CO_OBJ co_code_init(CO_CAK);
CO_OBJ co_code_del(CO_CAK);
CO_OBJ co_code_repr(CO_CAK);
CO_OBJ co_code_not(CO_CAK);
CO_OBJ co_code_truth(CO_CAK);
CO_OBJ co_code_hash(CO_CAK);
CO_OBJ co_code_eval(CO_CAK);

CO_OBJ co_function_init(CO_CAK);
CO_OBJ co_function_del(CO_CAK);
CO_OBJ co_function_repr(CO_CAK);
CO_OBJ co_function_not(CO_CAK);
CO_OBJ co_function_truth(CO_CAK);
CO_OBJ co_function_hash(CO_CAK);
CO_OBJ co_function_call(CO_CAK);

#endif
