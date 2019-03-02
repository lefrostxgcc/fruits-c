#include <stdlib.h>
#include <string.h>
#include <hashmap.h>
#include <object.h>

enum { CAPACITY_MIN = 8, CAPACITY_COEFF = 2 };

struct hashmap_s
{
  Entry **data;
  int size;
  int capacity;
};

object *entry_get_key(Entry *entry)
{
  return entry ? entry->key : NULL;
}

object *entry_get_value(Entry *entry)
{
  return entry ? entry->value : NULL;
}

static int hashmap_find_index(const HashMap * const this, object *key);

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
  this->data = realloc(this->data, new_capacity * sizeof (Entry *));
  this->capacity = new_capacity;
}

void hashmap_constructor(HashMap * const this)
{
  this->data = NULL;
  this->size = this->capacity = 0;
}

void hashmap_destructor(HashMap * const this)
{
  if (!this)
    return;
  for (int i = 0; i < this->size; i++)
    {
      if (this->data[i])
        {
          object_destructor(this->data[i]->key);
          free(this->data[i]->key);
          this->data[i]->key = NULL;
          object_destructor(this->data[i]->value);
          free(this->data[i]->value);
          this->data[i]->value = NULL;
        }
      free(this->data[i]);
    }
  free(this->data);
  this->data = NULL;
  this->size = this->capacity = 0;
}

void hashmap_add(HashMap * const this, object *key, object *value)
{
  if (!this || !key || !value)
    return;
  int index = hashmap_find_index(this, key);
  if (index < 0)
    {
      if (this->size >= this->capacity)
        hashmap_reallocate(this);
      Entry *pair = (Entry *) malloc(sizeof (Entry));
      pair->key = object_copy_constructor(key);
      pair->value = object_copy_constructor(value);
      this->data[this->size] = pair;
      this->size++;
    }
  else
    {
      object_destructor(this->data[index]->value);
      this->data[index]->value = object_copy_constructor(value);
    }
}

int hashmap_get_size(const HashMap * const this)
{
  return this ? this->size : 0;
}

int hashmap_capacity(const HashMap * const this)
{
  return this ? this->capacity : 0;
}

Entry **hashmap_get_entry_set(HashMap * this)
{
  return this->data;
}

static int hashmap_find_index(const HashMap * const this, object *key)
{
  if (!this || !key)
    return -1;
  for (int i = 0; i < this->size; i++)
    if(object_equal(this->data[i]->key, key))
      return i;
  return -1;
}

object *hashmap_get(const HashMap * const this, object *key)
{
  int index = hashmap_find_index(this, key);
  if (index < 0)
    return NULL;
  return this->data[index]->value;
}

void hashmap_put(HashMap * const this, object *key, object *value)
{
  hashmap_add(this, key, value);
}
