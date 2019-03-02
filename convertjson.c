#include <convertjson_impl.h>
#include <stdlib.h>
#include <chip_string.h>

static void (*convertjson_void[])() =
  {
   [CONVERTJSON_DESTRUCTOR] = &convertjson_destructor_vf,
  };

static String *(*convertjson_stringp[])() =
  {
   [CONVERTJSON_CONVERT] = &convertjson_convert_vf,
  };

static convertjson_vtbl convertjson_vt =
  {
   .fvoid = convertjson_void,
   .fstringp = convertjson_stringp
  };

ConvertJSON *convertjson_new()
{
  return (ConvertJSON *) malloc(sizeof (ConvertJSON));
}

void convertjson_constructor(ConvertJSON * const this)
{
  this->vptr = &convertjson_vt;
}

void convertjson_destructor(ConvertJSON * const this)
{
}

void convertjson_destructor_vf(Convertable * const this)
{
  convertjson_destructor((ConvertJSON *) this);
}

String *convertjson_convert_vf(Convertable * const this, const HashMap *map)
{
  return convertjson_convert((ConvertJSON *) this, map);
}

String *convertjson_convert(ConvertJSON * const this, const HashMap *map)
{
  if (hashmap_get_size(map) == 0)
    return string_new_concat("{}", NULL);
  String *text = string_new_concat("{\n", NULL);
  int map_size = hashmap_get_size(map);
  Entry **entry_set = hashmap_get_entry_set((HashMap *) map);
  for (int i = 0; i < map_size; i++)
    {
      Entry *pair = entry_set[i];
      const char *key = (const char *) object_data(entry_get_key(pair));
      const char *value = (const char *) object_data(entry_get_value(pair));
      string_concat(text, "    \"", key, "\": ", value, "\",\n", NULL);
    }
  string_set(text, string_size(text) - 2, '\n');
  string_set(text, string_size(text) - 1, '}');
  return text;
}
