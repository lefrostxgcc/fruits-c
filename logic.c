#include <logic.h>
#include <object.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TASK_STR(TASK) #TASK

static const char *task_str[] =
  {
   TASK_STR(COUNT),
   TASK_STR(DIFFCOUNT),
   TASK_STR(SETCOUNT),
   TASK_STR(FRUITMAX),
   "Not Task"
  };

const char *task_get_str(Task task)
{
  return task_str[task >= 0 && task < TASKMAX ? task : TASKMAX];
}

struct Logic_s
{
  arraylist *list;
};

static int logic_get_fruit_count(Logic *const this, Fruit find);

Logic *logic_new()
{
  return (Logic *) malloc(sizeof (Logic));
}

void logic_delete(Logic *this)
{
  free(this);
}

void logic_constructor(Logic * const this, arraylist *list)
{
  if (!this)
    return;
  this->list = list;
}

void logic_destructor(Logic * const this)
{
  if (!this)
    return;
  this->list = NULL;
}

char *logic_get_task(Logic * const this)
{
  struct
  {
    char *s;
    size_t len;
  } task_answers[TASKMAX];
  size_t answer_len = 0;
  for (Task task = 0; task < TASKMAX; task++)
    {
      task_answers[task].s = logic_get_task_id(this, task);
      if (task_answers[task].s == NULL)
        {
          for (int i = 0; i < task; i++)
            free(task_answers[i].s);
          return NULL;
        }
      task_answers[task].len = strlen(task_answers[task].s);
      answer_len += task_answers[task].len + 1;
    }
  char *answer = (char *) malloc(answer_len + 1);
  if (answer == NULL)
    return NULL;
  char *p = answer;
  *p = '\0';
  for (Task task = 0; task < TASKMAX; task++)
    {
      memcpy(p, task_answers[task].s, task_answers[task].len);
      p += task_answers[task].len;
      *p++ = '\n';
    }
  *p = '\0';
  for (Task task = 0; task < TASKMAX; task++)
    free(task_answers[task].s);
  return answer;
}

char *logic_get_task_id(Logic * const this, Task task)
{
  char buf[32];
  const char *p1 = task_get_str(task);
  const char *p2 = buf;
  size_t t1 = strlen(p1);
  size_t t2 = 0;
  switch (task)
    {
    case COUNT: t2 = snprintf(buf, sizeof buf, "%d", logic_get_count(this)); break;
    case DIFFCOUNT: t2 = snprintf(buf, sizeof buf, "%d", logic_get_diff_count(this)); break;
    case SETCOUNT: t2 = snprintf(buf, sizeof buf, "%d", logic_get_set_count(this)); break;
    case FRUITMAX: p2 = fruit_get_str(logic_get_fruit_max(this)); t2 = strlen(p2);  break;
    default: t2 = snprintf(buf, sizeof buf, "%s", "unknown"); break;
    }
  size_t t = t1 + 1 + t2 + 1;
  char *answer = (char *) malloc(t);
  if (answer == NULL)
    return NULL;
  snprintf(answer, t, "%s=%s", p1, p2);
  return answer;
}

int logic_get_count(Logic * const this)
{
  if (!this)
    return 0;
  return arraylist_size(this->list);
}

int logic_get_diff_count(Logic * const this)
{
  int count = 0;
  for (Fruit fruit = 0; fruit < FRUIT_MAX; fruit++)
    if (logic_get_fruit_count(this, fruit) > 0)
      count++;
  return count;
}

int logic_get_set_count(Logic * const this)
{
  return logic_get_diff_count(this);
}

Fruit logic_get_fruit_max(Logic * const this)
{
  if (!this)
    return FRUIT_MAX;
  int max = 0;
  Fruit fruitMax = FRUIT_MAX;
  for (Fruit fruit = 0; fruit < FRUIT_MAX; fruit++)
    {
      int count = logic_get_fruit_count(this, fruit);
      if (count > max)
        {
          max = count;
          fruitMax = fruit;
        }
    }
  return fruitMax;
}

static int logic_get_fruit_count(Logic * const this, Fruit find)
{
  int count = 0;
  int list_size = arraylist_size(this->list);
  for (int i = 0; i < list_size; i++)
    {
      Fruit fruit = *(Fruit *)object_data(arraylist_get(this->list, i));
      if (fruit == find)
        count++;
    }
  return count;
}
