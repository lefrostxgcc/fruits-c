#ifndef CONVERTABLE_H
#define CONVERTABLE_H

#include <hashmap.h>

typedef struct convertable_s Convertable;

char *convertable_convert(Convertable * const this, const HashMap *map);
void convertable_destructor(Convertable * const this);
void convertable_delete(Convertable *this);

#endif
