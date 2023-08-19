#include "smart_calc.h"

#include <time.h>

int result_calc(char *str, double *num, char x[]) {
  struct q_points points = {0};
  struct q_points_str pointsStr = {0};
  struct stack *brkt = NULL;
  struct stack *tockenOpr = NULL;
  struct stack *stackNum = NULL;
  char arr[256] = {'\0'};
  strcpy(arr, str);
  int res = Error, check = 0;
  res = parcer(&points, arr);
  while (points.head) {
    if (points.head->type == TYPE_X) {
      strcpy(points.head->data, x);
      points.head->type = TYPE_NUM;
    }
    if (points.head->priority >= 0 && points.head->priority <= 2 && !res) {
      check++;
      if (check > 2) res = Incorrect;
    } else
      check = 0;
    if (!res) res = incorrect_data(&points, &pointsStr);
    if (!res) res = processing_tocken(&points, &tockenOpr, &pointsStr, &brkt);
    pop_queue(&points);
  }
  if (brkt) res = Incorrect;
  if (!pointsStr.head && !res) res = Incorrect;
  while (tockenOpr && !res) {
    if (tockenOpr->type == TYPE_BRKT_2)
      res = Incorrect;
    else
      res = push_out_opr(&pointsStr, &tockenOpr);
  }
  if (!res) {
    res = calc_stack_num(&pointsStr, &stackNum);
    *num = stackNum->numD;
    pop_stack(&stackNum);
  }
  if (res) clear(pointsStr, brkt, tockenOpr, stackNum);
  return res;
}
