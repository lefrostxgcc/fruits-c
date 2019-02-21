#include <stdlib.h>
#include <string.h>
#include <object_cstr_impl.h>

object_cstr *object_cstr_new(void)
{
  return (object_cstr *) malloc(sizeof (object_cstr));
}

void object_cstr_constructor(object_cstr * const this, const char *str)
{
  object_constructor((object * const) this, (void*) str, strlen(str) + 1);
}
