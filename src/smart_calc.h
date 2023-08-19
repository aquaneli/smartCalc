#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Ok 0        /* 0 - Ок */
#define Incorrect 1 /* 1 - Incorrect - Неправильные данные */
#define Error 2     /* 2 - Error - Ошибка в системе */

enum lexeme {
  TYPE_SUM = 1,
  TYPE_SUB,
  TYPE_MUL,
  TYPE_DEL,
  TYPE_MOD,
  TYPE_DEG,
  TYPE_COS,
  TYPE_SIN,
  TYPE_TAN,
  TYPE_ACOS,
  TYPE_ASIN,
  TYPE_ATAN,
  TYPE_SQRT,
  TYPE_LN,
  TYPE_LOG,
  TYPE_NUM,
  TYPE_X,
  TYPE_BRKT_1 = -1,
  TYPE_BRKT_2 = -2,
  TYPE_UNSUB = -3,
  TYPE_UNSUM = -4
};

// #define calloc(X, Y) NULL

/* очередь для лексем */
struct parcer {
  char data[256];
  int priority;
  int type;
  struct parcer *next;
};

struct q_points {
  struct parcer *head, *end;
};

/* стек */
struct stack {
  char ch;
  int type;
  double numD;
  int priority;
  struct stack *next;
};

/* очередь для выходной строки */
struct out_str {
  char data[4];
  double numD;
  int type;
  int priority;
  struct out_str *next;
};

struct q_points_str {
  struct out_str *head, *end;
};

int result_calc(char *str, double *num, char *x);

/* parcer */
int parcer(struct q_points *points, char *str);
int push_queue(struct q_points *points, char *arr);
struct parcer *node_queue(char *arr);
int pop_queue(struct q_points *points);
char *token_func(char *str, const char *delim);
void init_data(struct parcer *node);
void init_num_func(struct parcer *node);
void clear(struct q_points_str pointsStr, struct stack *brkt,
           struct stack *tockenOpr, struct stack *stackNum);

/* out_str */
void get_next_opr(struct stack **tockenOpr, struct q_points_str *pointsStr);
int push_out_num(struct q_points_str *pointsStr, struct q_points *points);
int push_out_opr(struct q_points_str *pointsStr, struct stack **tockenOpr);
struct out_str *node_out_str();
void pop_out_str(struct q_points_str *pointsStr);
int calc_stack_num(struct q_points_str *pointsStr, struct stack **stackNum);

/* rev_notation */
int processing_tocken(struct q_points *points, struct stack **tockenOpr,
                      struct q_points_str *pointsStr, struct stack **brkt);
void push_stack_num(struct stack **tocken, struct q_points_str *pointsStr);
void unary_opr(struct q_points *points, struct stack **tockenOpr,
               struct q_points_str *pointsStr);
int incorrect_data(struct q_points *points, struct q_points_str *pointsStr);
int incorrect_num(struct q_points *points, struct q_points_str *pointsStr);
int incorrect_brkt(struct q_points *points);

/* opr_stack */
int push_stack(struct stack **tocken, struct q_points *points);
struct stack *node_stack();
void pop_stack(struct stack **tocken);
#endif  // SMART_CALC.H
