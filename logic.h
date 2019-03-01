#ifndef LOGIC_H
#define LOGIC_H

#include <convertable.h>
#include <fruit.h>
#include <arraylist.h>

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
char *logic_get_task_raw(Logic * const this);
char *logic_get_task_xml(Logic * const this);
char *logic_get_task_json(Logic * const this);
char *logic_get_task(Logic * const this, Task task);
int logic_get_count(Logic * const this);
int logic_get_diff_count(Logic * const this);
int logic_get_set_count(Logic * const this);
Fruit logic_get_fruit_max(Logic * const this);
char *logic_convert(Logic * const this, const HashMap *map);
void logic_delete(Logic *this);

#endif
