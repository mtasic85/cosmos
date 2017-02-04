#ifndef CO_VALUE_H
#define CO_VALUE_H

#include <stdbool.h>
#include <stdint.h>

#define CO_FUNC_ARGS co_ctx_t *ctx, co_list_t *args, co_dict_t *kwargs

enum co_type_t;
union _co_value_t;
struct co_value_t;
struct co_error_t;
typedef _Bool _co_c_bool;
typedef int64_t _co_c_int;
typedef double _co_c_float;
struct co_str_t;
struct co_list_t;
struct _co_set_entry_t;
struct co_set_t;
struct _co_dict_entry_t;
struct co_dict_t;
struct co_object_t;
struct co_code_t;
struct co_function_t;
struct co_module_t;

#include "ctx.h"

typedef enum co_type_t {
    CO_TYPE_ERROR,
    CO_TYPE_NIL,
    CO_TYPE_BOOL,
    CO_TYPE_INT,
    CO_TYPE_FLOAT,
    CO_TYPE_STR,
    CO_TYPE_LIST,
    CO_TYPE_SET,
    CO_TYPE_DICT,
    CO_TYPE_OBJECT,
    CO_TYPE_CODE,
    CO_TYPE_FUNCTION,
    CO_TYPE_MODULE
} co_type_t;



typedef union _co_value_t {
    struct co_error_t *error;
    _co_c_bool bool_;
    _co_c_int int_;
    _co_c_float float_;
    struct co_str_t *str;
    struct co_list_t *list;
    struct co_set_t *set;
    struct co_dict_t *dict;
    struct co_object_t *object;
    struct co_code_t *code;
    struct co_function_t *function;
    struct co_module_t *module;
} _co_value_t;


typedef struct co_value_t {
    uint32_t rc;
    enum co_type_t type;
    union _co_value_t value;
} co_value_t;

typedef struct co_error_t {
    co_value_t *error_type;         // string
    co_value_t *error_message;      // string
    uint64_t line;                  // |
    uint64_t column;                // | used only for unhandled errors
    co_value_t *filename;           // |
} co_error_t;

typedef struct co_str_t {
    uint64_t cap;
    uint64_t len;
    char *str;
} co_str_t;

typedef struct co_list_t {
    uint64_t cap;
    uint64_t len;
    co_value_t **items;
} co_list_t;

typedef struct _co_set_entry_t {
    uint64_t hash;
    co_value_t *key;
} _co_set_entry_t;

typedef struct co_set_t {
    uint64_t fill;
    uint64_t used;
    uint64_t mask;
    struct _co_set_entry_t **entries;
} co_set_t;

typedef struct _co_dict_entry_t {
    uint64_t hash;
    co_value_t *key;
    co_value_t *value;
} _co_dict_entry_t;

typedef struct co_dict_t {
    uint64_t fill;
    uint64_t used;
    uint64_t mask;
    struct _co_dict_entry_t **entries;
} co_dict_t;

typedef struct co_code_t {
    uint64_t len;
    char *bytecode;
} co_code_t;

typedef struct co_function_t {
    co_value_t *params; // parameters names (strings)
    co_value_t *code;   // function code
} co_function_t;

typedef struct co_module_t {
    co_value_t *name;   // name of module (string) - filename without extension
    co_value_t *path;   // path of module (string)
    co_value_t *code;   // module code - module initialization code
    co_value_t *items;  // module members (dict)
} co_module_t;

co_value_t * co_error_new(CO_FUNC_ARGS);
co_value_t * co_error_del(CO_FUNC_ARGS);

#endif
