#include "smart_calc.h"

/* удаляет след элемент если он больше по приоритету и не трогает скобки*/
void get_next_opr(struct stack **tockenOpr, struct q_points_str *pointsStr) {
  struct stack *tmpOpr = *tockenOpr;
  int flag = 0;
  while (tmpOpr && tmpOpr->next && tmpOpr->priority <= tmpOpr->next->priority &&
         tmpOpr->next->type != TYPE_BRKT_1 &&
         tmpOpr->next->type != TYPE_BRKT_2 && tmpOpr->type != TYPE_BRKT_1 &&
         tmpOpr->type != TYPE_BRKT_2 && !flag) {
    if (tmpOpr->type == TYPE_DEG && tmpOpr->next->type == TYPE_DEG) {
      flag = 1;
    } else
      push_out_opr(pointsStr, &tmpOpr->next);
  }
  *tockenOpr = tmpOpr;
}

/* пушим данные в выходную строку */
int push_out_num(struct q_points_str *pointsStr, struct q_points *points) {
  int res = Error;
  struct out_str *node = node_out_str();
  if (node && !pointsStr->head && points->head->type == TYPE_NUM) {
    res = Ok;
    pointsStr->head = node;
    pointsStr->head->data[0] = points->head->data[0];
    pointsStr->head->numD = atof(points->head->data);
    pointsStr->head->priority = points->head->priority;
    pointsStr->head->type = points->head->type;
    pointsStr->head->next = NULL;
    pointsStr->end = pointsStr->head;
  } else if (node && points->head && points->head->type == TYPE_NUM) {
    res = Ok;
    pointsStr->end->next = node;
    pointsStr->end = pointsStr->end->next;
    *pointsStr->end->data = *points->head->data;
    pointsStr->end->priority = points->head->priority;
    pointsStr->end->type = points->head->type;
    pointsStr->end->numD = atof(points->head->data);
  }
  return res;
}

/* пушим операторы в выходную строку*/
int push_out_opr(struct q_points_str *pointsStr, struct stack **tockenOpr) {
  struct out_str *node = node_out_str();
  struct stack *tmpOpr = *tockenOpr;
  int res = Error;
  if (node && tockenOpr) {
    res = Ok;
    *node->data = tmpOpr->ch;
    node->priority = tmpOpr->priority;
    node->type = tmpOpr->type;
    pointsStr->end->next = node;
    pointsStr->end = pointsStr->end->next;
    pop_stack(&tmpOpr);
  }
  *tockenOpr = tmpOpr;
  return res;
}

struct out_str *node_out_str() {
  struct out_str *A = NULL;
  A = (struct out_str *)calloc(sizeof(struct out_str), 1);
  return A;
}

void pop_out_str(struct q_points_str *pointsStr) {
  struct out_str *tmp = pointsStr->head;
  if (tmp) {
    pointsStr->head = tmp->next;
    free(tmp);
  }
}

/* вычисление */
int calc_stack_num(struct q_points_str *pointsStr, struct stack **stackNum) {
  struct stack *tmpNum = *stackNum;
  int res = Ok;
  while (pointsStr->head) {
    if (pointsStr->head->type == TYPE_NUM) {
      push_stack_num(&tmpNum, pointsStr);
    } else if (pointsStr->head->type <= 6) {
      if (pointsStr->head->type == TYPE_SUM)
        tmpNum->next->numD += tmpNum->numD;
      else if (pointsStr->head->type == TYPE_SUB)
        tmpNum->next->numD -= tmpNum->numD;
      else if (pointsStr->head->type == TYPE_MUL)
        tmpNum->next->numD *= tmpNum->numD;
      else if (pointsStr->head->type == TYPE_DEL)
        tmpNum->next->numD /= tmpNum->numD;
      else if (pointsStr->head->type == TYPE_MOD)
        tmpNum->next->numD = fmod(tmpNum->next->numD, tmpNum->numD);
      else if (pointsStr->head->type == TYPE_DEG)
        tmpNum->next->numD = pow(tmpNum->next->numD, tmpNum->numD);
      else if (pointsStr->head->type == TYPE_UNSUB)
        tmpNum->numD = -1 * tmpNum->numD;
      else if (pointsStr->head->type == TYPE_UNSUM)
        tmpNum->numD = 1 * tmpNum->numD;
      if (pointsStr->head->type != TYPE_UNSUB &&
          pointsStr->head->type != TYPE_UNSUM)
        pop_stack(&tmpNum);
    } else if (pointsStr->head->type >= 7) {
      if (pointsStr->head->type == TYPE_COS)
        tmpNum->numD = cos(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_SIN)
        tmpNum->numD = sin(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_TAN)
        tmpNum->numD = tan(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_ACOS)
        tmpNum->numD = acos(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_ASIN)
        tmpNum->numD = asin(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_ATAN)
        tmpNum->numD = atan(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_SQRT)
        tmpNum->numD = sqrt(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_LN)
        tmpNum->numD = log(tmpNum->numD);
      else if (pointsStr->head->type == TYPE_LOG)
        tmpNum->numD = log10(tmpNum->numD);
    }
    pop_out_str(pointsStr);
  }
  *stackNum = tmpNum;
  return res;
}