/*!
  \file
  \author Chip
  Проект - Дед Мороз.
  Демонстрация ОО возможностей
  на примере решения конкретной задачи
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arraylist.h>
#include <fruit.h>
#include <logic.h>
#include <object_cstr.h>
#include <convertable.h>
#include <convertraw.h>
#include <convertxml.h>
#include <convertjson.h>
#include <fruitreader.h>
#include <fruitreaderfile.h>
#include <fruitreaderscan.h>
#include <fruitreaderstringarray.h>

static void start(fruitreader *fr, Convertable *co);
static void show_manual(void);
static void parse_args(int argc, char *argv[]);
static void create(ArrayList *params);

static void start_code(void);
static void exit_code(void);

static fruitreader *fr;
static Convertable *co;

/*!
  Точка входа - запуск программы.
*/
int main(int argc, char *argv[])
{
  start_code();
  parse_args(argc, argv);
  if (fr == NULL)
    return 0;
  start(fr, co);
  exit_code();
}

static void start_code(void)
{
  ConvertRAW *convertRAW = convertraw_new();
  convertraw_constructor(convertRAW);
  co = (Convertable *) convertRAW;
}

static void exit_code(void)
{
  fruitreader_destructor(fr);
  fruitreader_delete(fr);
  convertable_destructor(co);
  convertable_delete(co);
}

static void parse_args(int argc, char *argv[])
{
  if (argc <= 1)
    {
      show_manual();
      return;
    }
  ArrayList *params = arraylist_new();
  arraylist_constructor(params);
  for (int i = 1; i < argc; i++)
    {
      if (argv[i][0] == '-')
        {
          create(params);
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
  create(params);
  arraylist_destructor(params);
  arraylist_delete(params);
}

static void create(ArrayList *params)
{
  int params_size = arraylist_size(params);
  if (params_size == 0)
    return;
  if (params_size == 2 && strcmp(object_data(arraylist_get(params, 0)), "-file") == 0)
    {
      fruitreader_destructor(fr);
      fruitreader_delete(fr);
      fruitreaderfile *frfile = fruitreaderfile_new();
      const char *filename = object_data(arraylist_get(params, 1));
      fruitreaderfile_constructor(frfile, filename);
      fr = (fruitreader *) frfile;
      return;
    }
  if (params_size == 1 && strcmp(object_data(arraylist_get(params, 0)), "-scan") == 0)
    {
      fruitreader_destructor(fr);
      fruitreader_delete(fr);
      fruitreaderscan *frscan = fruitreaderscan_new();
      fruitreaderscan_constructor(frscan);
      fr = (fruitreader *) frscan;
      return;
    }
  if (params_size >= 1 && strcmp(object_data(arraylist_get(params, 0)), "-data") == 0)
    {
      fruitreader_destructor(fr);
      fruitreader_delete(fr);
      fruitreaderstringarray *frarray = fruitreaderstringarray_new();
      ArrayList *sub = arraylist_sublist(params, 1, arraylist_size(params));
      fruitreaderstringarray_constructor_list(frarray, sub);
      arraylist_destructor(sub);
      arraylist_delete(sub);
      fr = (fruitreader *) frarray;
      return;
    }
  if (params_size == 1 && strcmp(object_data(arraylist_get(params, 0)), "-help") == 0)
    {
      show_manual();
      return;
    }
  if (params_size == 2 && strcmp(object_data(arraylist_get(params, 0)), "-format") == 0)
    {
      if (strcmp(object_data(arraylist_get(params, 1)), "raw") == 0)
        {
          ConvertRAW *convertRAW = convertraw_new();
          convertraw_constructor(convertRAW);
          convertable_destructor(co);
          convertable_delete(co);
          co = (Convertable *) convertRAW;
        }
      else if (strcmp(object_data(arraylist_get(params, 1)), "xml") == 0)
        {
          ConvertXML *convertXML = convertxml_new();
          convertxml_constructor(convertXML);
          convertable_destructor(co);
          convertable_delete(co);
          co = (Convertable *) convertXML;
        }
      else if (strcmp(object_data(arraylist_get(params, 1)), "json") == 0)
        {
          ConvertJSON *convertJSON = convertjson_new();
          convertjson_constructor(convertJSON);
          convertable_destructor(co);
          convertable_delete(co);
          co = (Convertable *) convertJSON;
        }
      return;
    }
}

/**
   Решение основной задачи
   \param[in] fr - Выбранный класс для считывания начальных данных
*/
static void start(fruitreader *fr, Convertable *co)
{
  ArrayList *list = fruitreader_read(fr);
  Logic *logic = logic_new();
  logic_constructor(logic, list);
  HashMap *map = logic_get_task(logic);
  String *answer = convertable_convert(co, map);
  printf("%s\n", answer ? string_data(answer) : "task error");
  string_destructor(answer);
  string_delete(answer);
  hashmap_destructor(map);
  hashmap_delete(map);
  logic_destructor(logic);
  logic_delete(logic);
  arraylist_destructor(list);
  arraylist_delete(list);
}

static void show_manual(void)
{
  printf("Program: error, no options specified.\n");
  printf("Usage: ./program [-help] [-format json|xml|raw] "
         "[-file filename]|[-scan]|[-data data]\n");
  printf(" -format\t\tUse specified format, default raw\n");
  printf(" -file filename\tLoad Fruits from text file\n");
  printf(" -scan \t\t\tLoad Fruits from Standard input\n");
  printf(" -data FRUIT1..\tLoad list of fruits\n");
}
