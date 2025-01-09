#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16

struct stack_s {
  int *data;
  int cap;
  int len;
};

stack_t *stack_create() {
  stack_t *s = calloc(1, sizeof(stack_t));

  s->cap = INITIAL_CAPACITY;
  s->len = 0;
  s->data = calloc(s->cap, sizeof(int));

  return s;
}

void stack_destroy(stack_t *s) {
  free(s->data);
  free(s);
}

const int *stack_data(const stack_t *s) { return s->data; }

int stack_len(const stack_t *s) { return s->len; }

int stack_get(const stack_t *s, int idx) {
  assert(idx < s->len);

  return s->data[idx];
}

int stack_is_decreasing(const stack_t *s) {
  for (int i = 1; i < s->len; ++i) {
    if (s->data[i] > s->data[i - 1]) {
      return 0;
    }
  }

  return 1;
}

int stack_is_increasing(const stack_t *s) {
  for (int i = 1; i < s->len; ++i) {
    if (s->data[i] < s->data[i - 1]) {
      return 0;
    }
  }

  return 1;
}

static void stack_maybe_grow(stack_t *s) {
  if (s->cap > s->len) {
    return;
  }

  s->cap *= 2;

  int *tmp = s->data;
  s->data = calloc(s->cap, sizeof(int));

  for (int i = 0; i < s->len; ++i) {
    s->data[i] = tmp[i];
  }

  free(tmp);
}

void stack_push_first(stack_t *s, int value) {
  stack_maybe_grow(s);

  for (int i = s->len; i >= 1; --i) {
    s->data[i] = s->data[i - 1];
  }
  s->len += 1;

  s->data[0] = value;
}

void stack_push_last(stack_t *s, int value) {
  stack_maybe_grow(s);

  s->data[s->len] = value;
  s->len += 1;
}

int stack_pop_first(stack_t *s) {
  assert(s->len > 0);

  int tmp = s->data[0];

  for (int i = 1; i < s->len; ++i) {
    s->data[i - 1] = s->data[i];
  }
  s->len -= 1;

  return tmp;
}

int stack_pop_last(stack_t *s) {
  assert(s->len > 0);

  int tmp = s->data[s->len - 1];
  s->len -= 1;

  return tmp;
}

void stack_swap(stack_t *s, int idx_a, int idx_b) {
  if (idx_a >= s->len || idx_b >= s->len) {
    return;
  }

  int tmp = s->data[idx_a];
  s->data[idx_a] = s->data[idx_b];
  s->data[idx_b] = tmp;
}

void stack_debug_print(const stack_t *s) {
  fprintf(stderr, "{\n  len = %d\n  cap = %d\n  data = [\n", s->len, s->cap);

  for (int i = 0; i < s->len; ++i) {
    fprintf(stderr, "    %d\n", s->data[i]);
  }

  fprintf(stderr, "  ]\n}\n");
}
