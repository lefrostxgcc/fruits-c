#include <logic_impl.h>
#include <object.h>
#include <object_cstr.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <chip_string.h>

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

static void (*logic_void[])() =
  {
   [LOGIC_DESTRUCTOR] = &logic_destructor_vf,
  };

static String *(*logic_stringp[])() =
  {
   [LOGIC_CONVERT] = &logic_convert_vf,
  };

static logic_vtbl logic_vt =
  {
   .fvoid = logic_void,
   .fstringp = logic_stringp
  };

const char *task_get_str(Task task)
{
  return task_str[task >= 0 && task < TASKMAX ? task : TASKMAX];
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

void logic_constructor(Logic * const this, ArrayList *list)
{
  if (!this)
    return;
  this->vptr = &logic_vt;
  this->list = list;
}

String *logic_convert_vf(Convertable * const this, const HashMap *map)
{
  return logic_convert((Logic *) this, map);
}

String *logic_convert(Logic * const this, const HashMap *map)
{
  String *text = string_new();
  string_constructor(text);
  int map_size = hashmap_get_size(map);
  Entry **entry_set = hashmap_get_entry_set((HashMap *) map);
  for (int i = 0; i < map_size; i++)
    {
      Entry *pair = entry_set[i];
      const char *key = (const char *) object_data(entry_get_key(pair));
      const char *value = (const char *) object_data(entry_get_value(pair));
      string_concat(text, key, "=", value, "\n", NULL);
    }
  return text;
}

HashMap *logic_get_task(Logic * const this)
{
  HashMap *map = hashmap_new();
  hashmap_constructor(map);
  for (Task task = 0; task < TASKMAX; task++)
    {
      object_cstr *key = object_cstr_new();
      object_cstr *value = object_cstr_new();
      String *s = logic_get_task_task(this, task);
      object_cstr_constructor(key, task_get_str(task));
      object_cstr_constructor(value, string_data(s));
      hashmap_put(map, (object *) key, (object *) value);
      string_destructor(s);
      object_destructor((object *) key);
      object_destructor((object *) value);
      string_delete(s);
      object_delete((object *) key);
      object_delete((object *) value);
    }
  return map;
}

void logic_destructor_vf(Convertable * const this)
{
  logic_destructor((Logic *) this);
}

void logic_destructor(Logic * const this)
{
  if (!this)
    return;
  this->list = NULL;
}

static String **logic_get_task_answers(Logic * const this)
{
  String **answers = (String **) malloc(sizeof (String *) * TASKMAX);
  for (Task task = 0; task < TASKMAX; task++)
      answers[task] = logic_get_task_task(this, task);
  return answers;
}

String *logic_get_task_raw(Logic * const this)
{
  String **task_answers = logic_get_task_answers(this);
  if (task_answers == NULL)
    return NULL;
  String *answer = string_new();
  if (answer == NULL)
    return NULL;
  string_constructor(answer);
  for (Task task = 0; task < TASKMAX; task++)
    {
      string_concat(answer,
                    task_get_str(task),
                    "=",
                    string_data(task_answers[task]),
                    "\n",
                    NULL);
    }
  for (Task task = 0; task < TASKMAX; task++)
    {
      string_destructor(task_answers[task]);
      string_delete(task_answers[task]);
    }
  free(task_answers);
  return answer;
}

String *logic_get_task_xml(Logic * const this)
{
  String **task_answers = logic_get_task_answers(this);
  if (task_answers == NULL)
    return NULL;
  String *answer = string_new();
  if (answer == NULL)
    return NULL;
  string_constructor(answer);
  string_concat(answer, "<?xml version=\"1.0\">\n<TASKS>\n", NULL);
  for (Task task = 0; task < TASKMAX; task++)
    {
      string_concat(answer,
                    "    <", task_get_str(task), ">",
                    string_data(task_answers[task]),
                    "</", task_get_str(task), ">\n",
                    NULL);
    }
  string_concat(answer, "</TASKS>", NULL);
  for (Task task = 0; task < TASKMAX; task++)
    {
      string_destructor(task_answers[task]);
      string_delete(task_answers[task]);
    }
  free(task_answers);
  return answer;
}

String *logic_get_task_json(Logic * const this)
{
  String **task_answers = logic_get_task_answers(this);
  if (task_answers == NULL)
    return NULL;
  String *answer = string_new();
  if (answer == NULL)
    return NULL;
  string_constructor(answer);
  string_concat(answer, "{\n", NULL);
  for (Task task = 0; task < TASKMAX; task++)
    {
       string_concat(answer,
                    "    \"", task_get_str(task), "\": \"",
                    string_data(task_answers[task]),
                    "\",\n",
                    NULL);
    }
  string_set(answer, string_size(answer) - 2, '\n');
  string_set(answer, string_size(answer) - 1, '}');
  for (Task task = 0; task < TASKMAX; task++)
    {
      string_destructor(task_answers[task]);
      string_delete(task_answers[task]);
    }
  free(task_answers);
  return answer;
}

String *logic_get_task_task(Logic * const this, Task task)
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
  return string_new_concat(p, NULL);
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
