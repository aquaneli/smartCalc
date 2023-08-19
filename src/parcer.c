#include "smart_calc.h"
/* 0 - Ок */
/* 1 - Incorrect - Неправильные данные */
/* 2 - Error - Ошибка в системе */

/* получаем все лексемы в очереди */
int parcer(struct q_points *points, char *str) {
  int res = Error;
  char *buff1 = "+-*/^()mx";
  char *p = token_func(str, buff1);
  points->head = node_queue(p);
  if (points->head) {
    res = Ok;
    init_data(points->head);
    points->end = points->head;
    points->end->next = NULL;
    while (p && !res) {
      p = token_func(NULL, buff1);
      res = push_queue(points, p);
    }
  }
  return res;
}

/* положить структуру в конец очереди */
int push_queue(struct q_points *points, char *arr) {
  int res = Error;
  struct parcer *node = node_queue(arr);
  if (node) {
    res = Ok;
    init_data(node);
    points->end->next = node;
    points->end = points->end->next;
  } else if (!arr)
    res = Ok;
  return res;
}

/* создание новой заполненной структуры */
struct parcer *node_queue(char *arr) {
  struct parcer *A = NULL;
  if (arr) A = (struct parcer *)calloc(sizeof(struct parcer), 1);
  if (A)
    for (int i = 0; arr[i] != '\0'; i++) A->data[i] = arr[i];
  return A;
}

/* вытащить первую структуру из очереди и очистить */
int pop_queue(struct q_points *points) {
  int res = Error;
  struct parcer *tmp = NULL;
  if (points->head) {
    res = Ok;
    tmp = points->head;
    points->head = points->head->next;
    free(tmp);
  }
  return res;
}

/* получает каждый токен из строки */
char *token_func(char *str, const char *delim) {
  static char *arr = NULL;
  static char *p = NULL;
  static char buff[256] = {'\0'};
  int ch = 0;
  int i = 0;

  if (str != NULL) {
    arr = str;
    ch = *str;
  } else {
    memset(buff, '\0', 256);
    str = arr;
    ch = *str;
  }

  /* указатель на символ */
  while (strchr(delim, ch) == NULL && *str != '\0') {
    buff[i] = ch;
    p = buff;
    i++;
    ch = *++str;
  }

  /* указатель на оператор */
  arr = str + strcspn(str, delim);
  if (i == 0) {
    buff[i] = *str;
    p = buff;
    if (buff[i] == 'm') {
      for (i = 1; i < 3; i++) buff[i] = *++arr;
    }
    if (*arr != '\0') {
      *arr = '\0';
      ++arr;
    } else
      p = NULL;
  }
  return p;
}

/* приоритет и тип */
void init_data(struct parcer *node) {
  if (*node->data == '+') {
    node->priority = 0;
    node->type = TYPE_SUM;
  } else if (*node->data == '-') {
    node->priority = 0;
    node->type = TYPE_SUB;
  } else if (*node->data == '*') {
    node->priority = 1;
    node->type = TYPE_MUL;
  } else if (*node->data == '/') {
    node->priority = 1;
    node->type = TYPE_DEL;
  } else if (!strcmp(node->data, "mod")) {
    node->priority = 1;
    node->type = TYPE_MOD;
  } else if (*node->data == '^') {
    node->priority = 2;
    node->type = TYPE_DEG;
  } else if (*node->data == '(') {
    node->priority = -1;
    node->type = TYPE_BRKT_1;
  } else if (*node->data == ')') {
    node->priority = -1;
    node->type = TYPE_BRKT_2;
  } else
    init_num_func(node);
}

void init_num_func(struct parcer *node) {
  if (!strcmp(node->data, "cos")) {
    node->priority = 3;
    node->type = TYPE_COS;
  } else if (!strcmp(node->data, "sin")) {
    node->priority = 3;
    node->type = TYPE_SIN;
  } else if (!strcmp(node->data, "tan")) {
    node->priority = 3;
    node->type = TYPE_TAN;
  } else if (!strcmp(node->data, "acos")) {
    node->priority = 3;
    node->type = TYPE_ACOS;
  } else if (!strcmp(node->data, "asin")) {
    node->priority = 3;
    node->type = TYPE_ASIN;
  } else if (!strcmp(node->data, "atan")) {
    node->priority = 3;
    node->type = TYPE_ATAN;
  } else if (!strcmp(node->data, "sqrt")) {
    node->priority = 3;
    node->type = TYPE_SQRT;
  } else if (!strcmp(node->data, "ln")) {
    node->priority = 3;
    node->type = TYPE_LN;
  } else if (!strcmp(node->data, "log")) {
    node->priority = 3;
    node->type = TYPE_LOG;
  } else if (*node->data == 'x') {
    node->priority = 3;
    node->type = TYPE_X;
  } else {
    node->priority = 3;
    node->type = TYPE_NUM;
  }
}