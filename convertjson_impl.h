#ifndef CONVERTJSON_IMPL_H
#define CONVERTJSON_IMPL_H

#include <convertjson.h>
#include <convertable_impl.h>
#include <chip_string.h>
#include <hashmap.h>

enum { CONVERTJSON_DESTRUCTOR };
enum { CONVERTJSON_CONVERT };

typedef struct convertjson_vtbl_s
{
  void (**fvoid)();
  String * (**fstringp)();
} convertjson_vtbl;

struct ConvertJSON_s
{
  convertjson_vtbl *vptr;
};

String *convertjson_convert_vf(Convertable * const this, const HashMap *map);
void convertjson_destructor_vf(Convertable * const this);

#endif
