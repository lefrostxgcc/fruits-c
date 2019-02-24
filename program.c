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
#include <fruitreader.h>
#include <fruitreaderfile.h>
#include <fruitreaderscan.h>
#include <fruitreaderstring.h>

static void start(fruitreader *fr);
static void show_manual(void);
static char *chip_concat(const char *s1, const char *s2);

/*!
  Точка входа - запуск программы.
*/
int main(int argc, char *argv[])
{
  if (argc <= 1)
    {
      show_manual();
      return 0;
    }
  fruitreader *fr;
  if (strcmp(argv[1], "-file") == 0)
    {
      fruitreaderfile *frfile = fruitreaderfile_new();
      fruitreaderfile_constructor(frfile, argv[2]);
      fr = (fruitreader *) frfile;
    }
  else if (strcmp(argv[1], "-scan") == 0)
    {
      fruitreaderscan *frscan = fruitreaderscan_new();
      fruitreaderscan_constructor(frscan);
      fr = (fruitreader *) frscan;
    }
  else if (strcmp(argv[1], "-data") == 0)
    {
      fruitreaderstring *frstring = fruitreaderstring_new();
      char *s = chip_concat(argv[2], "\n\n");
      fruitreaderstring_constructor(frstring, s);
      free(s);
      fr = (fruitreader *) frstring;
    }
  if (fr == NULL)
    {
      show_manual();
      return 0;
    }
  start(fr);
  fruitreader_destructor(fr);
  fruitreader_delete(fr);
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
  arraylist *list = fruitreader_read(fr);
  int count = arraylist_size(list);
  printf("%d\n", count);
  arraylist_destructor(list);
  arraylist_delete(list);
}

static char *chip_concat(const char *s1, const char *s2)
{
  if (!s1 && !s2)
    return NULL;
  size_t s1_len = s1 ? strlen(s1) : 0;
  size_t s2_len = s2 ? strlen(s2) : 0;
  size_t s_len = s1_len + s2_len;
  char *s = (char *) malloc(s_len + 1);
  if (!s)
    return NULL;
  if (s1)
    memcpy(s, s1, s1_len);
  if (s2)
    memcpy(s + s1_len, s2, s2_len);
  s[s_len] = '\0';
  return s;
}
