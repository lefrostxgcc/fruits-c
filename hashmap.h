#ifndef HASHMAP_H
#define HASHMAP_H

#include <object.h>

typedef struct hashmap_s HashMap;

typedef struct
{
  object *key;
  object *value;
} Entry;

object *entry_get_key(Entry *entry);
object *entry_get_value(Entry *entry);

HashMap *hashmap_new(void);
void hashmap_delete(HashMap *this);
void hashmap_constructor(HashMap * const this);
void hashmap_destructor(HashMap * const this);
Entry **hashmap_get_entry_set(HashMap * this);
void hashmap_add(HashMap * const this, object *key, object *element);
int hashmap_get_size(const HashMap * const this);
object *hashmap_get(const HashMap * const this, object *key);
void hashmap_put(HashMap * const this, object *key, object * element);

#endif
