#include <paramfactory.h>
#include <object_cstr.h>
#include <fruitreaderscan.h>
#include <fruitreaderfile.h>
#include <fruitreaderstringarray.h>
#include <convertraw.h>
#include <convertxml.h>
#include <convertjson.h>
#include <string.h>

static void create(ParamFactory * const this, ArrayList *params);
static Convertable *create_convertable(const char *format);

void paramfactory_constructor(ParamFactory * const this, int argc, char *argv[])
{
  this->fruitReader = NULL;
  this->convertable = NULL;
  this->isHelp = false;
  if (argc <= 1)
    {
      this->isHelp = true;
      return;
    }
  ArrayList *params = arraylist_new();
  arraylist_constructor(params);
  for (int i = 1; i < argc; i++)
    {
      if (argv[i][0] == '-')
        {
          create(this, params);
          arraylist_destructor(params);
          arraylist_delete(params);
          params = arraylist_new();
          arraylist_constructor(params);
        }
      object_cstr *object_arg = object_cstr_new();
      object_cstr_constructor(object_arg, argv[i]);
      arraylist_add(params, (object *) object_arg);
      object_destructor((object *) object_arg);
      object_delete((object *) object_arg);
    }
  create(this, params);
  arraylist_destructor(params);
  arraylist_delete(params);
}

void paramfactory_destructor(ParamFactory * const this)
{
  fruitreader_destructor(this->fruitReader);
  fruitreader_delete(this->fruitReader);
  this->fruitReader = NULL;
  convertable_destructor(this->convertable);
  convertable_delete(this->convertable);
  this->convertable = NULL;
  this->isHelp = false;
}

static void create(ParamFactory * const this, ArrayList *params)
{
  int params_size = arraylist_size(params);
  if (params_size == 0)
    return;
  if (params_size == 2 && strcmp(object_data(arraylist_get(params, 0)), "-file") == 0)
    {
      fruitreader_destructor(this->fruitReader);
      fruitreader_delete(this->fruitReader);
      FruitReaderFile *frfile = fruitreaderfile_new();
      const char *filename = object_data(arraylist_get(params, 1));
      fruitreaderfile_constructor(frfile, filename);
      this->fruitReader = (FruitReader *) frfile;
      return;
    }
  if (params_size == 1 && strcmp(object_data(arraylist_get(params, 0)), "-scan") == 0)
    {
      fruitreader_destructor(this->fruitReader);
      fruitreader_delete(this->fruitReader);
      FruitReaderScan *frscan = fruitreaderscan_new();
      fruitreaderscan_constructor(frscan);
      this->fruitReader = (FruitReader *) frscan;
      return;
    }
  if (params_size >= 1 && strcmp(object_data(arraylist_get(params, 0)), "-data") == 0)
    {
      fruitreader_destructor(this->fruitReader);
      fruitreader_delete(this->fruitReader);
      FruitReaderStringArray *frarray = fruitreaderstringarray_new();
      ArrayList *sub = arraylist_sublist(params, 1, arraylist_size(params));
      fruitreaderstringarray_constructor_list(frarray, sub);
      arraylist_destructor(sub);
      arraylist_delete(sub);
      this->fruitReader = (FruitReader *) frarray;
      return;
    }
  if (params_size == 1 && strcmp(object_data(arraylist_get(params, 0)), "-help") == 0)
    {
      this->isHelp = true;
      return;
    }
  if (params_size == 2 && strcmp(object_data(arraylist_get(params, 0)), "-format") == 0)
    {
      convertable_destructor(this->convertable);
      convertable_delete(this->convertable);
      this->convertable = create_convertable(object_data(arraylist_get(params, 1)));
      return;
    }
}

FruitReader *paramfactory_fruitReader(ParamFactory * const this)
{
  if (this)
    return this->fruitReader;
  return NULL;
}

Convertable *paramfactory_convertable(ParamFactory * const this)
{
  if (this)
    return this->convertable;
  return NULL;
}

bool paramfactory_isHelp(ParamFactory * const this)
{
  if (this)
    return this->isHelp;
  return false;
}

static Convertable *create_convertable(const char *format)
{
  if (strcmp(format, "raw") == 0)
    {
      ConvertRaw *convertRaw = convertraw_new();
      convertraw_constructor(convertRaw);
      return (Convertable *) convertRaw;
    }
  else if (strcmp(format, "xml") == 0)
    {
      ConvertXml *convertXml = convertxml_new();
      convertxml_constructor(convertXml);
      return (Convertable *) convertXml;
    }
  else if (strcmp(format, "json") == 0)
    {
      ConvertJson *convertJson = convertjson_new();
      convertjson_constructor(convertJson);
      return (Convertable *) convertJson;
    }
  ConvertJson *convertJson = convertjson_new();
  convertjson_constructor(convertJson);
  return (Convertable *) convertJson;
}
