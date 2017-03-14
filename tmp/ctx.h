#ifndef CO_CTX_H
#define CO_CTX_H

#include <stdlib.h>

struct co_ctx_t;
struct co_frame_t;

typedef struct co_ctx_t {
    struct co_ctx_t *parent_ctx;
    struct co_frame_t *root_frame;
    struct co_frame_t *top_frame;
} co_ctx_t;

#include "value.h"

typedef struct co_frame_t {
    struct co_ctx_t *ctx;
    struct co_frame_t *parent_frame;
    struct co_value_t *function;
    struct co_value_t *args;
    struct co_value_t *upvalues;
} co_frame_t;

co_ctx_t *co_ctx_alloc(co_ctx_t *parent_ctx);
void co_ctx_free(co_ctx_t *ctx);
void co_ctx_exec_path(co_ctx_t *ctx, char *path);
void co_ctx_exec_frame(co_ctx_t *ctx, co_frame_t *frame);

co_frame_t *co_frame_alloc(co_ctx_t *ctx, co_frame_t *parent_frame);
void co_frame_free(co_frame_t *frame);

#endif
