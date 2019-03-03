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
#include <convertable.h>
#include <convertraw.h>
#include <convertxml.h>
#include <convertjson.h>
#include <fruitreader.h>
#include <fruitreaderfile.h>
#include <fruitreaderscan.h>
#include <fruitreaderstringarray.h>

static void start(fruitreader *fr, Convertable *co);
static Convertable *parse_args_convert(int argc, char *argv[]);
static fruitreader *parse_args_freader(int argc, char *argv[]);
static void show_manual(void);

/*!
  Точка входа - запуск программы.
*/
int main(int argc, char *argv[])
{
  Convertable *co = parse_args_convert(argc, argv);
  fruitreader *fr = parse_args_freader(argc, argv);
  if (fr == NULL)
    return 1;
  start(fr, co);
  fruitreader_destructor(fr);
  fruitreader_delete(fr);
  convertable_destructor(co);
  convertable_delete(co);
}

static Convertable *parse_args_convert(int argc, char *argv[])
{
  ConvertRAW *convertRAW = convertraw_new();
  convertraw_constructor(convertRAW);
  return (Convertable *) convertRAW;
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
  printf("Usage: ./program [-format json|xml|raw] "
         "[-file filename]|[-scan]|[-data data]\n");
  printf(" -format\t\tUse specified format, default raw\n");
  printf(" -file filename\tLoad Fruits from text file\n");
  printf(" -scan \t\t\tLoad Fruits from Standard input\n");
  printf(" -data FRUIT1..\tLoad list of fruits\n");
}

static fruitreader *parse_args_freader(int argc, char *argv[])
{
  fruitreader *fr = NULL;
  if (argc == 3 && strcmp(argv[1], "-file") == 0)
    {
      fruitreaderfile *frfile = fruitreaderfile_new();
      fruitreaderfile_constructor(frfile, argv[2]);
      fr = (fruitreader *) frfile;
    }
  else if (argc == 2 && strcmp(argv[1], "-scan") == 0)
    {
      fruitreaderscan *frscan = fruitreaderscan_new();
      fruitreaderscan_constructor(frscan);
      fr = (fruitreader *) frscan;
    }
  else if (argc >= 3 && strcmp(argv[1], "-data") == 0)
    {
      fruitreaderstringarray *frarray = fruitreaderstringarray_new();
      fruitreaderstringarray_constructor(frarray, argv + 2, argc - 2);
      fr = (fruitreader *) frarray;
    }
  else
    show_manual();
  return fr;
}
