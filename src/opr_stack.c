#include "smart_calc.h"

/* стек для операторов */
int push_stack(struct stack **tocken, struct q_points *points) {
  int res = Error;
  struct stack *node = node_stack();
  if (node) {
    res = Ok;
    node->ch = points->head->data[0];
    node->priority = points->head->priority;
    node->type = points->head->type;
    node->next = *tocken;
    *tocken = node;
  }
  return res;
}

struct stack *node_stack() {
  struct stack *A = NULL;
  A = (struct stack *)calloc(sizeof(struct stack), 1);
  return A;
}

void pop_stack(struct stack **tocken) {
  struct stack *tmp = *tocken;
  if (tmp) {
    *tocken = tmp->next;
    free(tmp);
  }
}