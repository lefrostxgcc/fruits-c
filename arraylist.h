#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <object.h>

typedef struct arraylist_s ArrayList;

ArrayList *arraylist_new(void);
void arraylist_delete(ArrayList *this);
void arraylist_constructor(ArrayList * const this);
void arraylist_destructor(ArrayList * const this);
void arraylist_add(ArrayList * const this, object *element);
int arraylist_size(ArrayList * const this);
object *arraylist_get(ArrayList * const this, int index);
void arraylist_set(ArrayList * const this, object *element, int index);
ArrayList *arraylist_sublist(ArrayList * const this, int start, int end);

#endif
