#include <convertraw_impl.h>
#include <stdlib.h>
#include <chip_string.h>

static void (*convertraw_void[])() =
  {
   [CONVERTRAW_DESTRUCTOR] = &convertraw_destructor_vf,
  };

static String *(*convertraw_stringp[])() =
  {
   [CONVERTRAW_CONVERT] = &convertraw_convert_vf,
  };

static convertraw_vtbl convertraw_vt =
  {
   .fvoid = convertraw_void,
   .fstringp = convertraw_stringp
  };

ConvertRaw *convertraw_new()
{
  return (ConvertRaw *) malloc(sizeof (ConvertRaw));
}

void convertraw_constructor(ConvertRaw * const this)
{
  this->vptr = &convertraw_vt;
}

void convertraw_destructor(ConvertRaw * const this)
{
}

void convertraw_destructor_vf(Convertable * const this)
{
  convertraw_destructor((ConvertRaw *) this);
}

String *convertraw_convert_vf(Convertable * const this, const HashMap *map)
{
  return convertraw_convert((ConvertRaw *) this, map);
}

String *convertraw_convert(ConvertRaw * const this, const HashMap *map)
{
  String *text = string_new();
  string_constructor(text);
  int map_size = hashmap_get_size(map);
  Entry **entry_set = hashmap_get_entry_set((HashMap *) map);
  for (int i = 0; i < map_size; i++)
    {
      Entry *pair = entry_set[i];
      const char *key = (const char *) object_data(entry_get_key(pair));
      const char *value = (const char *) object_data(entry_get_value(pair));
      string_concat(text, key, "=", value, "\n", NULL);
    }
  return text;
}
