#ifndef CONVERTRAW_IMPL_H
#define CONVERTRAW_IMPL_H

#include <convertraw.h>
#include <convertable_impl.h>
#include <chip_string.h>
#include <hashmap.h>

enum { CONVERTRAW_DESTRUCTOR };
enum { CONVERTRAW_CONVERT };

typedef struct convertraw_vtbl_s
{
  void (**fvoid)();
  String * (**fstringp)();
} convertraw_vtbl;

struct ConvertRaw_s
{
  convertraw_vtbl *vptr;
};

String *convertraw_convert_vf(Convertable * const this, const HashMap *map);
void convertraw_destructor_vf(Convertable * const this);

#endif
