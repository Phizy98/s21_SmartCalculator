#include "stack.h"

stack *create_stack() {
  stack *stack = calloc(1, sizeof(struct myStack));
  if (stack == NULL) return NULL;
  return stack;
}

void clear_stack(stack **top) {
  while (*top != NULL) {
    pop(top);
  }
}

void pop(stack **top) {
  stack *tmp = *top;
  *top = (*top)->next;
  free(tmp);
}

bool push(stack **top, long double value, int priority, type_t type) {
  stack *tmp = calloc(1, sizeof(struct myStack));
  if (tmp == NULL) return false;
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = *top;
  *top = tmp;
  return true;
}

stack *reverse_stack(stack **top) {
  stack *tmp = create_stack();

  if (*top == NULL) return NULL;
  while (*top) {
    push(&tmp, (*top)->value, (*top)->priority, (*top)->type);
    pop(top);
  }
  clear_stack(top);
  return tmp;
}

void print_stack(stack *top) {
  if (top == NULL) {
    printf("Empty stack\n");
  }
  while (top != NULL) {
    printf("value: %Lf, priority: %d, type: %d\n", top->value, top->priority,
           top->type);
    top = top->next;
  }
}

// int main(void) {
//     stack *top = NULL;
//     top = create_stack();
//     push(&top, 12, 0, Num);
//     push(&top, 11, 0, Num);
//     push(&top, 0, 5, Cos);
//     print_stack(top);
//     // while (top->next != NULL)
//     // {
//     //     print_stack(top);
//     //     pop(&top);
//     // }
//     // printf("end\n");
//     // print_stack(top);
//     clear_stack(&top);
//     printf("mmmmmm?\n");
//     //free(top);
//     printf("\n%d\n", top == NULL);
//     print_stack(top);

//     return 0;
// }
