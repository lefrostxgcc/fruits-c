#ifndef LOGIC_IMPL_H
#define LOGIC_IMPL_H

#include <logic.h>
#include <chip_string.h>
#include <hashmap.h>

enum { LOGIC_DESTRUCTOR };
enum { LOGIC_CONVERT };

typedef struct logic_vtbl_s
{
  void (**fvoid)();
  String * (**fstringp)();
} logic_vtbl;

struct Logic_s
{
  logic_vtbl *vptr;
  ArrayList *list;
};

String *logic_convert_vf(Convertable * const this, const HashMap *map);
void logic_destructor_vf(Convertable * const this);

#endif
