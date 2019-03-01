#ifndef HASHMAP_H
#define HASHMAP_H

#include <object.h>

typedef struct hashmap_s HashMap;

HashMap *hashmap_new(void);
void hashmap_delete(HashMap *this);
void hashmap_constructor(HashMap * const this);
void hashmap_destructor(HashMap * const this);
void hashmap_add(HashMap * const this, object *key, object *element);
int hashmap_size(HashMap * const this);
object *hashmap_get(HashMap * const this, object *key);
void hashmap_set(HashMap * const this, object *key, object * element);

#endif
