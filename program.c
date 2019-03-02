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
#include <fruitreader.h>
#include <fruitreaderfile.h>
#include <fruitreaderscan.h>
#include <fruitreaderstringarray.h>

static void start(fruitreader *fr);
static fruitreader *parse_args(int argc, char *argv[]);
static void show_manual(void);
static char *chip_concat(const char *s1, const char *s2);

/*!
  Точка входа - запуск программы.
*/
int main(int argc, char *argv[])
{
  fruitreader *fr = parse_args(argc, argv);
  if (fr == NULL)
    return 1;
  start(fr);
  fruitreader_destructor(fr);
  fruitreader_delete(fr);
}

static fruitreader *parse_args(int argc, char *argv[])
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

static void show_manual(void)
{
  printf("Program: error, no options specified.\n");
  printf("Usage: ./program, [options] [data]\n");
  printf(" -file filename\tLoad Fruits from text file\n");
  printf(" -scan \t\t\tLoad Fruits from Standard input\n");
  printf(" -data FRUIT1\tLoad one fruit\n");
}

/**
   Решение основной задачи
   \param[in] fr - Выбранный класс для считывания начальных данных
*/
static void start(fruitreader *fr)
{
  ArrayList *list = fruitreader_read(fr);
  Logic *logic = logic_new();
  logic_constructor(logic, list);
  HashMap *map = logic_get_task(logic);
  String *answer = logic_convert(logic, map);
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
