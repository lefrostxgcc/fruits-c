#ifndef LOGIC_H
#define LOGIC_H

#include <chip_string.h>
#include <fruit.h>
#include <arraylist.h>
#include <hashmap.h>

typedef struct Logic_s Logic;

typedef enum
  {
   COUNT,
   DIFFCOUNT,
   SETCOUNT,
   FRUITMAX,
   TASKMAX
  } Task;

Logic *logic_new();
void logic_constructor(Logic * const this, ArrayList *list);
void logic_destructor(Logic * const this);
String *logic_get_task_raw(Logic * const this);
String *logic_get_task_xml(Logic * const this);
String *logic_get_task_json(Logic * const this);
HashMap *logic_get_task(Logic * const this);
String *logic_get_task_task(Logic * const this, Task task);
int logic_get_count(Logic * const this);
int logic_get_diff_count(Logic * const this);
int logic_get_set_count(Logic * const this);
Fruit logic_get_fruit_max(Logic * const this);
void logic_delete(Logic *this);

#endif
