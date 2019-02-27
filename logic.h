#ifndef LOGIC_H
#define LOGIC_H

#include <fruit.h>
#include <arraylist.h>

typedef struct Logic_s Logic;

Logic *logic_new();
void logic_constructor(Logic * const this, arraylist *list);
void logic_destructor(Logic * const this);
int logic_get_count(Logic * const this);
Fruit logic_get_fruit_max(Logic * const this);
void logic_delete(Logic *this);

#endif
