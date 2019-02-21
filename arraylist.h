#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <object.h>

typedef struct arraylist_s arraylist;

arraylist *arraylist_new(void);
void arraylist_free(arraylist **this);
void arraylist_constructor(arraylist * const this);
void arraylist_destructor(arraylist * const this);
void arraylist_add(arraylist * const this, object *element);
int arraylist_size(arraylist * const this);
object *arraylist_get(arraylist * const this, int index);
void arraylist_set(arraylist * const this, object *element, int index);

#endif
