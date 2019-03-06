/*!
  \file
  \author Chip
  Проект - Дед Мороз.
  Демонстрация ОО возможностей
  на примере решения конкретной задачи
*/

#include <stdio.h>
#include <arraylist.h>
#include <hashmap.h>
#include <logic.h>
#include <convertable.h>
#include <fruitreader.h>
#include <paramfactory.h>

static void start(ParamFactory *pf);
static void show_manual(void);

/*!
  Точка входа - запуск программы.
*/
int main(int argc, char *argv[])
{
  ParamFactory pf;
  paramfactory_constructor(&pf, argc, argv);
  start(&pf);
  paramfactory_destructor(&pf);
}

/**
   Решение основной задачи
   \param[in] fr - Выбранный класс для считывания начальных данных
*/
static void start(ParamFactory *pf)
{
  if (paramfactory_isHelp(pf)
      || paramfactory_fruitReader(pf) == NULL
      || paramfactory_convertable(pf) == NULL)
    {
      show_manual();
      return;
    }
  ArrayList *list = fruitreader_read(paramfactory_fruitReader(pf));
  Logic *logic = logic_new();
  logic_constructor(logic, list);
  HashMap *map = logic_get_task(logic);
  String *answer = convertable_convert(paramfactory_convertable(pf), map);
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
