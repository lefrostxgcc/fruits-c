#include <stdlib.h>
#include <string.h>
#include <arraylist.h>
#include <object.h>

enum { CAPACITY_MIN = 8, CAPACITY_COEFF = 2 };

struct arraylist_s
{
  object **data;
  int size;
  int capacity;
};

ArrayList *arraylist_new(void)
{
  return (ArrayList *) malloc(sizeof(ArrayList));
}

void arraylist_delete(ArrayList *this)
{
  free(this);
}

static void arraylist_reallocate(ArrayList * const this)
{
  int new_capacity = this->capacity != 0 ?
    this->capacity * CAPACITY_COEFF : CAPACITY_MIN;
  this->data = realloc(this->data, new_capacity * sizeof (object *));
  this->capacity = new_capacity;
}

void arraylist_constructor(ArrayList * const this)
{
  this->data = NULL;
  this->size = this->capacity = 0;
}

void arraylist_destructor(ArrayList * const this)
{
  if (!this)
    return;
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

void arraylist_add(ArrayList * const this, object *element)
{
  if (!this || !element)
    return;
  if (this->size >= this->capacity)
    arraylist_reallocate(this);
  this->data[this->size] = object_copy_constructor(element);
  this->size++;
}

int arraylist_size(ArrayList * const this)
{
  return this ? this->size : 0;
}

int arraylist_capacity(ArrayList * const this)
{
  return this ? this->capacity : 0;
}

object *arraylist_get(ArrayList * const this, int index)
{
  if (!this || index < 0 || index >= this->size)
    return NULL;
  return this->data[index];
}

void arraylist_set(ArrayList * const this, object *element, int index)
{
  if (!this || !element || index < 0 || index >= this->size)
    return;
  object_destructor(this->data[index]);
  free(this->data[index]);
  object_copy(this->data[index], element);
}
