typedef struct stack_s stack_t;

stack_t *stack_create();
void stack_destroy(stack_t *s);

const int *stack_data(const stack_t *s);
int stack_len(const stack_t *s);

int stack_get(const stack_t *s, int idx);
int stack_is_decreasing(const stack_t *s);
int stack_is_increasing(const stack_t *s);

void stack_push_first(stack_t *s, int value);
void stack_push_last(stack_t *s, int value);
int stack_pop_first(stack_t *s);
int stack_pop_last(stack_t *s);
void stack_swap(stack_t *s, int idx_a, int idx_b);

void stack_debug_print(const stack_t *s);
