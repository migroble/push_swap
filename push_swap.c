#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "stack.h"

typedef struct data_s {
  stack_t *a;
  stack_t *b;
} data_t;

void swap_a(data_t *data) {
  stack_swap(data->a, 0, 1);

  write(1, "sa\n", 3);
}

void swap_b(data_t *data) {
  stack_swap(data->b, 0, 1);

  write(1, "sb\n", 3);
}

void swap_ab(data_t *data) {
  stack_swap(data->a, 0, 1);
  stack_swap(data->b, 0, 1);

  write(1, "ss\n", 3);
}

void push_a(data_t *data) {
  int value = stack_pop_first(data->b);
  stack_push_first(data->a, value);

  write(1, "pa\n", 3);
}

void push_b(data_t *data) {
  int value = stack_pop_first(data->a);
  stack_push_first(data->b, value);

  write(1, "pb\n", 3);
}

void rot_a(data_t *data) {
  int value = stack_pop_first(data->a);
  stack_push_last(data->a, value);

  write(1, "ra\n", 3);
}

void rot_b(data_t *data) {
  int value = stack_pop_first(data->b);
  stack_push_last(data->b, value);

  write(1, "rb\n", 3);
}

void rot_ab(data_t *data) {
  int value = stack_pop_first(data->a);
  stack_push_last(data->a, value);

  value = stack_pop_first(data->b);
  stack_push_last(data->b, value);

  write(1, "rr\n", 3);
}

void rev_rot_a(data_t *data) {
  int value = stack_pop_last(data->a);
  stack_push_first(data->a, value);

  write(1, "rra\n", 4);
}

void rev_rot_b(data_t *data) {
  int value = stack_pop_last(data->b);
  stack_push_first(data->b, value);

  write(1, "rrb\n", 4);
}

void rev_rot_ab(data_t *data) {
  int value = stack_pop_last(data->a);
  stack_push_first(data->a, value);

  value = stack_pop_last(data->b);
  stack_push_first(data->b, value);

  write(1, "rrr\n", 4);
}

int main(int argc, char **argv) {
  data_t data = {
      .a = stack_create(),
      .b = stack_create(),
  };

  for (int i = 1; i < argc; ++i) {
    int value = atoi(argv[i]);
    stack_push_last(data.a, value);
  }

  stack_debug_print(data.a);

  // TODO: Sort data.a

  stack_debug_print(data.a);

  stack_destroy(data.a);
  stack_destroy(data.b);

  return 0;
}
