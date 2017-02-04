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
    uint64_t line;                  // `
    uint64_t column;                // | used only for unhandled errors
    co_value_t *filename;           // /
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
    co_value_t *path;   // path of module (string)
    co_value_t *name;   // name of module (string) - filename without extension
    co_value_t *code;   // module code - module initialization code
    co_value_t *items;  // module members (dict)
} co_module_t;

co_value_t *co_error_new(CO_FUNC_ARGS);
co_value_t *co_error_delete(CO_FUNC_ARGS);

co_value_t *co_nil_new(CO_FUNC_ARGS);
co_value_t *co_nil_delete(CO_FUNC_ARGS);
co_value_t *co_nil_not(CO_FUNC_ARGS);

co_value_t *co_bool_new(CO_FUNC_ARGS);
co_value_t *co_bool_delete(CO_FUNC_ARGS);
co_value_t *co_bool_not(CO_FUNC_ARGS);
co_value_t *co_bool_and(CO_FUNC_ARGS);
co_value_t *co_bool_or(CO_FUNC_ARGS);
co_value_t *co_bool_xor(CO_FUNC_ARGS);

co_value_t *co_int_new(CO_FUNC_ARGS);
co_value_t *co_int_delete(CO_FUNC_ARGS);
co_value_t *co_int_not(CO_FUNC_ARGS);
co_value_t *co_int_neg(CO_FUNC_ARGS);
co_value_t *co_int_pos(CO_FUNC_ARGS);
co_value_t *co_int_inv(CO_FUNC_ARGS);
co_value_t *co_int_add(CO_FUNC_ARGS);
co_value_t *co_int_sub(CO_FUNC_ARGS);
co_value_t *co_int_mul(CO_FUNC_ARGS);
co_value_t *co_int_div(CO_FUNC_ARGS);
co_value_t *co_int_mod(CO_FUNC_ARGS);
co_value_t *co_int_pow(CO_FUNC_ARGS);
co_value_t *co_int_lshift(CO_FUNC_ARGS);
co_value_t *co_int_rshift(CO_FUNC_ARGS);
co_value_t *co_int_and(CO_FUNC_ARGS);
co_value_t *co_int_or(CO_FUNC_ARGS);
co_value_t *co_int_xor(CO_FUNC_ARGS);

co_value_t *co_float_new(CO_FUNC_ARGS);
co_value_t *co_float_delete(CO_FUNC_ARGS);
co_value_t *co_float_not(CO_FUNC_ARGS);
co_value_t *co_float_neg(CO_FUNC_ARGS);
co_value_t *co_float_pos(CO_FUNC_ARGS);
co_value_t *co_float_add(CO_FUNC_ARGS);
co_value_t *co_float_sub(CO_FUNC_ARGS);
co_value_t *co_float_mul(CO_FUNC_ARGS);
co_value_t *co_float_div(CO_FUNC_ARGS);
co_value_t *co_float_mod(CO_FUNC_ARGS);
co_value_t *co_float_pow(CO_FUNC_ARGS);

co_value_t *co_str_new(CO_FUNC_ARGS);
co_value_t *co_str_delete(CO_FUNC_ARGS);
co_value_t *co_str_not(CO_FUNC_ARGS);
co_value_t *co_str_encode(CO_FUNC_ARGS);
co_value_t *co_str_decode(CO_FUNC_ARGS);
co_value_t *co_str_add(CO_FUNC_ARGS);
co_value_t *co_str_format(CO_FUNC_ARGS);
co_value_t *co_str_index(CO_FUNC_ARGS);
co_value_t *co_str_replace(CO_FUNC_ARGS);
co_value_t *co_str_get(CO_FUNC_ARGS);
co_value_t *co_str_set(CO_FUNC_ARGS);
co_value_t *co_str_del(CO_FUNC_ARGS);
co_value_t *co_str_getslice(CO_FUNC_ARGS);
co_value_t *co_str_setslice(CO_FUNC_ARGS);
co_value_t *co_str_delslice(CO_FUNC_ARGS);
co_value_t *co_str_iter(CO_FUNC_ARGS);
co_value_t *co_str_join(CO_FUNC_ARGS);
co_value_t *co_str_split(CO_FUNC_ARGS);

co_value_t *co_list_new(CO_FUNC_ARGS);
co_value_t *co_list_delete(CO_FUNC_ARGS);
co_value_t *co_list_not(CO_FUNC_ARGS);
co_value_t *co_list_add(CO_FUNC_ARGS);
co_value_t *co_list_append(CO_FUNC_ARGS);
co_value_t *co_list_prepend(CO_FUNC_ARGS);
co_value_t *co_list_insert(CO_FUNC_ARGS);
co_value_t *co_list_remove(CO_FUNC_ARGS);
co_value_t *co_list_pop(CO_FUNC_ARGS);
co_value_t *co_list_leftpop(CO_FUNC_ARGS);
co_value_t *co_list_index(CO_FUNC_ARGS);
co_value_t *co_list_get(CO_FUNC_ARGS);
co_value_t *co_list_set(CO_FUNC_ARGS);
co_value_t *co_list_del(CO_FUNC_ARGS);
co_value_t *co_list_getslice(CO_FUNC_ARGS);
co_value_t *co_list_setslice(CO_FUNC_ARGS);
co_value_t *co_list_delslice(CO_FUNC_ARGS);
co_value_t *co_list_iter(CO_FUNC_ARGS);

co_value_t *co_set_new(CO_FUNC_ARGS);
co_value_t *co_set_delete(CO_FUNC_ARGS);
co_value_t *co_set_not(CO_FUNC_ARGS);
co_value_t *co_set_add(CO_FUNC_ARGS);
co_value_t *co_set_sub(CO_FUNC_ARGS);
co_value_t *co_set_div(CO_FUNC_ARGS);
co_value_t *co_set_and(CO_FUNC_ARGS);
co_value_t *co_set_or(CO_FUNC_ARGS);
co_value_t *co_set_xor(CO_FUNC_ARGS);
co_value_t *co_set_add(CO_FUNC_ARGS);
co_value_t *co_set_remove(CO_FUNC_ARGS);
co_value_t *co_set_iter(CO_FUNC_ARGS);

co_value_t *co_dict_new(CO_FUNC_ARGS);
co_value_t *co_dict_delete(CO_FUNC_ARGS);
co_value_t *co_dict_not(CO_FUNC_ARGS);
co_value_t *co_dict_add(CO_FUNC_ARGS);
co_value_t *co_dict_get(CO_FUNC_ARGS);
co_value_t *co_dict_set(CO_FUNC_ARGS);
co_value_t *co_dict_del(CO_FUNC_ARGS);
co_value_t *co_dict_iter(CO_FUNC_ARGS);

co_value_t *co_object_new(CO_FUNC_ARGS);
co_value_t *co_object_delete(CO_FUNC_ARGS);
co_value_t *co_object_add(CO_FUNC_ARGS);
co_value_t *co_object_get(CO_FUNC_ARGS);       // `
co_value_t *co_object_set(CO_FUNC_ARGS);       // | low-level access to attrs
co_value_t *co_object_del(CO_FUNC_ARGS);       // /
co_value_t *co_object_getattr(CO_FUNC_ARGS);   // `
co_value_t *co_object_setattr(CO_FUNC_ARGS);   // | high-level access to attrs
co_value_t *co_object_delattr(CO_FUNC_ARGS);   // /

co_value_t *co_code_new(CO_FUNC_ARGS);
co_value_t *co_code_delete(CO_FUNC_ARGS);

co_value_t *co_function_new(CO_FUNC_ARGS);
co_value_t *co_function_delete(CO_FUNC_ARGS);
co_value_t *co_function_call(CO_FUNC_ARGS);

co_value_t *co_module_new(CO_FUNC_ARGS);
co_value_t *co_module_delete(CO_FUNC_ARGS);
co_value_t *co_module_get(CO_FUNC_ARGS);
co_value_t *co_module_set(CO_FUNC_ARGS);
co_value_t *co_module_del(CO_FUNC_ARGS);
co_value_t *co_module_getattr(CO_FUNC_ARGS);
co_value_t *co_module_setattr(CO_FUNC_ARGS);
co_value_t *co_module_delattr(CO_FUNC_ARGS);

#endif
