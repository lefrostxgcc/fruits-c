#ifndef CONVERTJSON_H
#define CONVERTJSON_H

#include <convertable.h>
#include <chip_string.h>
#include <hashmap.h>

typedef struct ConvertJSON_s ConvertJSON;

ConvertJSON *convertjson_new();
void convertjson_constructor(ConvertJSON * const this);
void convertjson_destructor(ConvertJSON * const this);
String *convertjson_convert(ConvertJSON * const this, const HashMap *map);

#endif
