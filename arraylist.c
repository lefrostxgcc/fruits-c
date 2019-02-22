#include <stdlib.h>
#include <string.h>
#include <arraylist.h>
#include <object.h>

enum { CAPACITY_MIN = 8, CAPACITY_COEFF = 2 };

typedef struct arraylist_s
{
  object **data;
  int size;
  int capacity;
} arraylist;

arraylist *arraylist_new(void)
{
  return (arraylist *) malloc(sizeof(arraylist));
}

void arraylist_delete(arraylist *this)
{
  free(this);
}

static void arraylist_reallocate(arraylist * const this)
{
  int new_capacity = this->capacity != 0 ?
    this->capacity * CAPACITY_COEFF : CAPACITY_MIN;
  this->data = realloc(this->data, new_capacity * sizeof (object *));
  this->capacity = new_capacity;
}

void arraylist_constructor(arraylist * const this)
{
  this->data = NULL;
  this->size = this->capacity = 0;
}

void arraylist_destructor(arraylist * const this)
{
  for (int i = 0; i < this->size; i++)
      if (this->data[i])
        {
          object_destructor(this->data[i]);
          free(this->data[i]);
          this->data[i] = NULL;
        }
  free(this->data);
  this->data = NULL;
  this->size = this->capacity = 0;
}

void arraylist_add(arraylist * const this, object *element)
{
  if (this->size >= this->capacity)
    arraylist_reallocate(this);
  this->data[this->size] = object_copy_constructor(element);
  this->size++;
}

int arraylist_size(arraylist * const this)
{
  return this->size;
}

int arraylist_capacity(arraylist * const this)
{
  return this->capacity;
}

object *arraylist_get(arraylist * const this, int index)
{
  if (index < 0 || index >= this->size)
    return NULL;
  return this->data[index];
}

void arraylist_set(arraylist * const this, object *element, int index)
{
  if (index < 0 || index >= this->size)
    return;
  object_destructor(this->data[index]);
  free(this->data[index]);
  object_copy(this->data[index], element);
}
