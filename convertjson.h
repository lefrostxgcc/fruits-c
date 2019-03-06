#ifndef CONVERTJSON_H
#define CONVERTJSON_H

#include <convertable.h>
#include <chip_string.h>
#include <hashmap.h>

typedef struct ConvertJson_s ConvertJson;

ConvertJson *convertjson_new();
void convertjson_constructor(ConvertJson * const this);
void convertjson_destructor(ConvertJson * const this);
String *convertjson_convert(ConvertJson * const this, const HashMap *map);

#endif
