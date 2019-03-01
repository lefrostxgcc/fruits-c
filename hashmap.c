#include <stdlib.h>
#include <string.h>
#include <hashmap.h>
#include <object.h>

enum { CAPACITY_MIN = 8, CAPACITY_COEFF = 2 };

struct hashmap_s
{
  object **key;
  object **data;
  int size;
  int capacity;
};

static int hashmap_find_index(HashMap * const this, object *key);

HashMap *hashmap_new(void)
{
  return (HashMap *) malloc(sizeof(HashMap));
}

void hashmap_delete(HashMap *this)
{
  free(this);
}

static void hashmap_reallocate(HashMap * const this)
{
  int new_capacity = this->capacity != 0 ?
    this->capacity * CAPACITY_COEFF : CAPACITY_MIN;
  this->key = realloc(this->key, new_capacity * sizeof (object *));
  this->data = realloc(this->data, new_capacity * sizeof (object *));
  this->capacity = new_capacity;
}

void hashmap_constructor(HashMap * const this)
{
  this->key = NULL;
  this->data = NULL;
  this->size = this->capacity = 0;
}

void hashmap_destructor(HashMap * const this)
{
  if (!this)
    return;
  for (int i = 0; i < this->size; i++)
    {
      if (this->key[i])
        {
          object_destructor(this->key[i]);
          free(this->key[i]);
          this->key[i] = NULL;
        }
      if (this->data[i])
        {
          object_destructor(this->data[i]);
          free(this->data[i]);
          this->data[i] = NULL;
        }
    }
  free(this->key);
  free(this->data);
  this->key = NULL;
  this->data = NULL;
  this->size = this->capacity = 0;
}

void hashmap_add(HashMap * const this, object *key, object *element)
{
  if (!this || !key || !element)
    return;
  int index = hashmap_find_index(this, key);
  if (index < 0)
    {
      if (this->size >= this->capacity)
        hashmap_reallocate(this);
      this->key[this->size] = object_copy_constructor(key);
      this->data[this->size] = object_copy_constructor(element);
      this->size++;
    }
  else
    {
      object_destructor(this->data[index]);
      free(this->data[index]);
      this->data[index] = object_copy_constructor(element);
    }
}

int hashmap_size(HashMap * const this)
{
  return this ? this->size : 0;
}

int hashmap_capacity(HashMap * const this)
{
  return this ? this->capacity : 0;
}

static int hashmap_find_index(HashMap * const this, object *key)
{
  if (!this || !key)
    return -1;
  for (int i = 0; i < this->size; i++)
    if(object_equal(this->key[i], key) == 0)
      return i;
  return -1;
}

object *hashmap_get(HashMap * const this, object *key)
{
  int index = hashmap_find_index(this, key);
  if (index < 0)
    return NULL;
  return this->data[index];
}

void hashmap_set(HashMap * const this, object *key, object *element)
{
  hashmap_add(this, key, element);
}
