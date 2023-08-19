#include "smart_calc.h"

/* обрабатываем элемент и закидываем в выходную строку или в стек */
int processing_tocken(struct q_points *points, struct stack **tockenOpr,
                      struct q_points_str *pointsStr, struct stack **brkt) {
  int res = Error;
  struct stack *tmpOpr = *tockenOpr;
  struct stack *tmpBrkt = *brkt;

  if (points->head->type == TYPE_NUM) {
    res = push_out_num(pointsStr, points);
    if (tmpBrkt && tmpBrkt->ch == '~' && pointsStr->head)
      res = push_out_opr(pointsStr, &tmpBrkt);
    else if (tmpBrkt && tmpBrkt->ch == '#' && pointsStr->head)
      res = push_out_opr(pointsStr, &tmpBrkt);
    else if (tmpOpr && tmpOpr->ch == '~' && pointsStr->head && !tmpBrkt)
      res = push_out_opr(pointsStr, &tmpOpr);
    else if (tmpOpr && tmpOpr->ch == '#' && pointsStr->head && !tmpBrkt)
      res = push_out_opr(pointsStr, &tmpOpr);
  } else {
    if (points->head->type == TYPE_BRKT_1 || tmpBrkt) {
      res = push_stack(&tmpBrkt, points);
      unary_opr(points, &tmpBrkt, pointsStr);
      if (pointsStr->head && tmpBrkt->type != TYPE_BRKT_2 &&
          (tmpBrkt->type != TYPE_UNSUB && tmpBrkt->type != TYPE_UNSUM))
        get_next_opr(&tmpBrkt, pointsStr);
    }
    if (tmpBrkt && tmpBrkt->type == TYPE_BRKT_2 && pointsStr->head) {
      if (tmpBrkt->type == TYPE_BRKT_2) pop_stack(&tmpBrkt);
      while (tmpBrkt && tmpBrkt->type != TYPE_BRKT_1)
        res = push_out_opr(pointsStr, &tmpBrkt);
      if (tmpBrkt->type == TYPE_BRKT_1) pop_stack(&tmpBrkt);
    } else if (!tmpBrkt) {
      res = push_stack(&tmpOpr, points);
      unary_opr(points, &tmpOpr, pointsStr);
      if (pointsStr->head && tmpOpr &&
          (tmpOpr->type != TYPE_UNSUB && tmpOpr->type != TYPE_UNSUM))
        get_next_opr(&tmpOpr, pointsStr);
    }
  }
  *brkt = tmpBrkt;
  *tockenOpr = tmpOpr;
  return res;
}

/* нахождение унарного минуса или плюса */
void unary_opr(struct q_points *points, struct stack **tockenOpr,
               struct q_points_str *pointsStr) {
  struct stack *tmpOpr = *tockenOpr;
  if (!pointsStr->head && tmpOpr && tmpOpr->type == TYPE_SUB) {
    tmpOpr->ch = '~';
    tmpOpr->priority = 0;
    tmpOpr->type = TYPE_UNSUB;
  } else if (points->head->next && points->head->next->type == TYPE_SUB &&
             ((points->head->type <= 7 && points->head->type >= 0) ||
              points->head->type == TYPE_BRKT_1)) {
    points->head->next->data[0] = '~';
    points->head->next->priority = 0;
    points->head->next->type = TYPE_UNSUB;
  } else if (!pointsStr->head && tmpOpr && tmpOpr->type == TYPE_SUM) {
    tmpOpr->ch = '#';
    tmpOpr->priority = 0;
    tmpOpr->type = TYPE_UNSUM;
  } else if (points->head->next && points->head->next->type == TYPE_SUM &&
             ((points->head->type <= 7 && points->head->type >= 0) ||
              points->head->type == TYPE_BRKT_1)) {
    points->head->next->data[0] = '#';
    points->head->next->priority = 0;
    points->head->next->type = TYPE_UNSUM;
  }
  *tockenOpr = tmpOpr;
}

/* пушим сюда числа */
void push_stack_num(struct stack **tocken, struct q_points_str *pointsStr) {
  struct stack *node = node_stack();
  if (node) {
    node->numD = pointsStr->head->numD;
    node->priority = pointsStr->head->priority;
    node->type = pointsStr->head->type;
    node->next = *tocken;
    *tocken = node;
  }
}

int incorrect_data(struct q_points *points, struct q_points_str *pointsStr) {
  int res = Ok;
  /* проверяем корректность ввода самого числа */
  res = incorrect_num(points, pointsStr);
  if (points->head->next && !res) {
    /* проверяем корректность ввода cо скобками */
    res = incorrect_brkt(points);
    /* проверяем если второй знак по приоритету стоит выше */
    if ((points->head->priority == 0 || points->head->priority == 1) &&
        (points->head->next->priority == 1 ||
         points->head->next->priority == 2))
      res = Incorrect;
    /* проверяем сколько поставили операторов в начале строки */
    else if (!pointsStr->head &&
             (points->head->type == TYPE_SUM ||
              points->head->type == TYPE_SUB) &&
             (points->head->next->type == TYPE_SUM ||
              points->head->next->type == TYPE_SUB))
      res = Incorrect;
    else if (points->head->type == TYPE_NUM &&
             points->head->next->type == TYPE_X)
      res = Incorrect;
  }

  return res;
}

int incorrect_brkt(struct q_points *points) {
  int res = Ok;
  /* проверяем стоит ли сразу за числом символ X или открывающая скобка */
  if (points->head->type == TYPE_NUM &&
      (points->head->next->type == TYPE_NUM ||
       points->head->next->type == TYPE_BRKT_1))
    res = Incorrect;
  /* проверяем есть ли в скобках число */
  else if (((points->head->type >= 1 && points->head->type < 7) ||
            points->head->type == TYPE_UNSUB ||
            points->head->type == TYPE_UNSUM) &&
           points->head->next->type == TYPE_BRKT_2)
    res = Incorrect;
  /* проверяем все что стоит после открывающей скобки */
  else if (points->head->type == TYPE_BRKT_1 &&
           points->head->next->type == TYPE_SUB && points->head->next->next &&
           (points->head->next->next->type != TYPE_NUM &&
            points->head->next->next->type != TYPE_BRKT_1))
    res = Incorrect;
  else if (points->head->type == TYPE_BRKT_1 &&
           points->head->next->type == TYPE_SUM && points->head->next->next &&
           (points->head->next->next->type != TYPE_NUM &&
            points->head->next->next->type != TYPE_BRKT_1))
    res = Incorrect;
  /* проверяем стоит ли после закрывающей скобки оператор или число(функция) */
  else if (points->head->type == TYPE_BRKT_2 &&
           (points->head->next->type == TYPE_BRKT_1 ||
            points->head->next->priority == 3))
    res = Incorrect;
  /* проверяем стоил ли сразу после функции скобка */
  else if (points->head->priority == 3 && points->head->type != TYPE_NUM &&
           points->head->next->type != TYPE_BRKT_1)
    res = Incorrect;
  /* проверяем если скобки пустые */
  else if (points->head->type == TYPE_BRKT_1 &&
           points->head->next->type == TYPE_BRKT_2)
    res = Incorrect;
  return res;
}

int incorrect_num(struct q_points *points, struct q_points_str *pointsStr) {
  int res = Ok;
  /* проверяем что стоит в самом начале строки если нет числа */
  if (!pointsStr->head &&
      (points->head->priority == 1 || points->head->priority == 2))
    res = Incorrect;
  /* проверяем ввели ли мы несколько точек */
  if (points->head->type == TYPE_NUM) {
    int ch = points->head->data[0], i = 0, count = 0;
    char *num = "1234567890.-+";
    char *ptr = NULL;
    while ((ptr = strchr(num, ch)) != NULL && points->head->data[i] != '\0') {
      ch = points->head->data[i];
      if (ch == '.') count++;
      if ((i > 0 && (ch == '-' || ch == '+'))) res = Incorrect;
      i++;
    }
    if (!ptr || count > 1) res = Incorrect;
  }
  /* проверяем какой последнйи символ в строке */
  if (!points->head->next && points->head->type != TYPE_NUM &&
      points->head->type != TYPE_BRKT_2)
    res = Incorrect;
  if (points->head->data[0] == '.' && points->head->data[1] == '\0')
    res = Incorrect;
  return res;
}

void clear(struct q_points_str pointsStr, struct stack *brkt,
           struct stack *tockenOpr, struct stack *stackNum) {
  while ((pointsStr.head || brkt || tockenOpr || stackNum)) {
    if (pointsStr.head) pop_out_str(&pointsStr);
    if (brkt) pop_stack(&brkt);
    if (tockenOpr) pop_stack(&tockenOpr);
    if (stackNum) pop_stack(&stackNum);
  }
}
