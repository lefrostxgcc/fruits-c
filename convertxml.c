#include <convertxml_impl.h>
#include <stdlib.h>
#include <chip_string.h>

static void (*convertxml_void[])() =
  {
   [CONVERTXML_DESTRUCTOR] = &convertxml_destructor_vf,
  };

static String *(*convertxml_stringp[])() =
  {
   [CONVERTXML_CONVERT] = &convertxml_convert_vf,
  };

static convertxml_vtbl convertxml_vt =
  {
   .fvoid = convertxml_void,
   .fstringp = convertxml_stringp
  };

ConvertXML *convertxml_new()
{
  return (ConvertXML *) malloc(sizeof (ConvertXML));
}

void convertxml_constructor(ConvertXML * const this)
{
  this->vptr = &convertxml_vt;
}

void convertxml_destructor(ConvertXML * const this)
{
}

void convertxml_destructor_vf(Convertable * const this)
{
  convertxml_destructor((ConvertXML *) this);
}

String *convertxml_convert_vf(Convertable * const this, const HashMap *map)
{
  return convertxml_convert((ConvertXML *) this, map);
}

String *convertxml_convert(ConvertXML * const this, const HashMap *map)
{
  String *text = string_new_concat("<?xml version=\"1.0\">\n<XML>\n", NULL);
  int map_size = hashmap_get_size(map);
  Entry **entry_set = hashmap_get_entry_set((HashMap *) map);
  for (int i = 0; i < map_size; i++)
    {
      Entry *pair = entry_set[i];
      const char *key = (const char *) object_data(entry_get_key(pair));
      const char *value = (const char *) object_data(entry_get_value(pair));
      string_concat(text, "    <", key, ">", value, "</", key, ">\n", NULL);
    }
  string_concat(text, "</XML>", NULL);
  return text;
}
