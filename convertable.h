#ifndef CONVERTABLE_H
#define CONVERTABLE_H

#include <chip_string.h>
#include <hashmap.h>

typedef struct convertable_s Convertable;

String *convertable_convert(Convertable * const this, const HashMap *map);
void convertable_destructor(Convertable * const this);
void convertable_delete(Convertable *this);

#endif
