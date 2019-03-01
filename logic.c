#include <logic.h>
#include <object.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define TASK_STR(TASK) #TASK

static const char *task_str[] =
  {
   TASK_STR(COUNT),
   TASK_STR(DIFFCOUNT),
   TASK_STR(SETCOUNT),
   TASK_STR(FRUITMAX),
   "Not Task"
  };

static const int task_name_lens[] =
  {
   sizeof (TASK_STR(COUNT)) - 1,
   sizeof (TASK_STR(DIFFCOUNT)) - 1,
   sizeof (TASK_STR(SETCOUNT)) - 1,
   sizeof (TASK_STR(FRUITMAX)) - 1,
   sizeof ("Not Task") - 1
  };

const char *task_get_str(Task task)
{
  return task_str[task >= 0 && task < TASKMAX ? task : TASKMAX];
}

struct Logic_s
{
  arraylist *list;
};

struct chip_string
{
  char *s;
  size_t len;
};

static char *chip_concat(char *s, ...)
{
  if (s == NULL)
    return NULL;
  va_list ap;
  char *s_concat = s;
  const char *p = NULL;
  va_start(ap, s);
  while ((p = va_arg(ap, const char *)) != NULL)
    {
      size_t p_len = strlen(p);
      memcpy(s_concat, p, p_len);
      s_concat += p_len;
    }
  *s_concat = '\0';
  va_end(ap);
  return s_concat;
}

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

static struct chip_string *logic_get_task_answers(Logic * const this)
{
  static struct chip_string answers[TASKMAX];
  for (Task task = 0; task < TASKMAX; task++)
    {
      answers[task].s = logic_get_task(this, task);
      if (answers[task].s == NULL)
        {
          for (int i = 0; i < task; i++)
            free(answers[i].s);
          return NULL;
        }
      answers[task].len = strlen(answers[task].s);
    }
  return answers;
}

char *logic_get_task_raw(Logic * const this)
{
  struct chip_string *task_answers = logic_get_task_answers(this);
  if (task_answers == NULL)
    return NULL;
  size_t answer_len = 0;
  for (Task task = 0; task < TASKMAX; task++)
    answer_len += task_name_lens[task] + 1 + task_answers[task].len + 1;
  char *answer = (char *) malloc(answer_len + 1);
  if (answer == NULL)
    return NULL;
  char *p = answer;
  *p = '\0';
  for (Task task = 0; task < TASKMAX; task++)
    {
      memcpy(p, task_get_str(task), task_name_lens[task]);
      p += task_name_lens[task];
      *p++ = '=';
      memcpy(p, task_answers[task].s, task_answers[task].len);
      p += task_answers[task].len;
      *p++ = '\n';
    }
  *p = '\0';
  for (Task task = 0; task < TASKMAX; task++)
    free(task_answers[task].s);
  return answer;
}

char *logic_get_task_xml(Logic * const this)
{
  struct chip_string *task_answers = logic_get_task_answers(this);
  if (task_answers == NULL)
    return NULL;
#define XML_HEADER "<?xml version=\"1.0\">\n"
#define XML_ROOT_NAME "TASKS"
  size_t answer_len = sizeof (XML_HEADER) + 2 * sizeof(XML_ROOT_NAME) + 6;
  for (Task task = 0; task < TASKMAX; task++)
    answer_len += task_name_lens[task] * 2 + task_answers[task].len + 10;
  char *answer = (char *) malloc(answer_len + 1);
  if (answer == NULL)
    return NULL;
  char *p = answer;
  *p = '\0';
  p = chip_concat(p, XML_HEADER, "<", XML_ROOT_NAME, ">\n", NULL);
  for (Task task = 0; task < TASKMAX; task++)
    {
      p = chip_concat(p, "    <", task_get_str(task), ">",
                      task_answers[task].s,
                      "</", task_get_str(task), ">\n", NULL
                      );
    }
  p = chip_concat(p, "</", XML_ROOT_NAME, ">", NULL);
  *p = '\0';
  for (Task task = 0; task < TASKMAX; task++)
    free(task_answers[task].s);
  return answer;
}

char *logic_get_task_json(Logic * const this)
{
  struct chip_string *task_answers = logic_get_task_answers(this);
  if (task_answers == NULL)
    return NULL;
  size_t answer_len = 3;
  for (Task task = 0; task < TASKMAX; task++)
    answer_len += task_name_lens[task] + task_answers[task].len + 12;
  char *answer = (char *) malloc(answer_len + 1);
  if (answer == NULL)
    return NULL;
  char *p = answer;
  *p = '\0';
  p = chip_concat(p, "{\n", NULL);
  for (Task task = 0; task < TASKMAX; task++)
    {
      p = chip_concat(p,
                      "    \"", task_get_str(task), "\": \"",
                      task_answers[task].s,
                      "\",\n", NULL
                      );
    }
  p -= 2;
  p = chip_concat(p, "\n}", NULL);
  *p = '\0';
  for (Task task = 0; task < TASKMAX; task++)
    free(task_answers[task].s);
  return answer;
}

char *logic_get_task(Logic * const this, Task task)
{
  char buf[32];
  const char *p = buf;
  switch (task)
    {
    case COUNT: snprintf(buf, sizeof buf, "%d", logic_get_count(this)); break;
    case DIFFCOUNT: snprintf(buf, sizeof buf, "%d", logic_get_diff_count(this)); break;
    case SETCOUNT: snprintf(buf, sizeof buf, "%d", logic_get_set_count(this)); break;
    case FRUITMAX: p = fruit_get_str(logic_get_fruit_max(this)); break;
    default: snprintf(buf, sizeof buf, "%s", "unknown"); break;
    }
  return strdup(p);
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
