#ifndef CONVERTABLE_IMPL_H
#define CONVERTABLE_IMPL_H

#include <convertable.h>

enum fvoid{ CONVERTABLE_DESTRUCTOR };
enum fcharp{ CONVERTABLE_CONVERT };

typedef struct convertable_vtbl_s
{
  void (**fvoid)();
  char* (**fcharp)();
} convertable_vtbl;

struct convertable_s
{
  convertable_vtbl *vptr;
};

#endif
