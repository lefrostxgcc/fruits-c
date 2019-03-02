#ifndef CONVERTABLE_IMPL_H
#define CONVERTABLE_IMPL_H

#include <convertable.h>

enum fvoid{ CONVERTABLE_DESTRUCTOR };
enum fstringp{ CONVERTABLE_CONVERT };

typedef struct convertable_vtbl_s
{
  void (**fvoid)();
  String * (**fstringp)();
} convertable_vtbl;

struct convertable_s
{
  convertable_vtbl *vptr;
};

#endif
