/*!
 \file
 \author Chip
 Проект - Дед Мороз.
 Демонстрация ОО возможностей
 на примере решения конкретной задачи
 */

#include <stdio.h>
#include <arraylist.h>
#include <fruitreader.h>
#include <fruitreaderfile.h>

static void start(fruitreader *fr);

/*!
 Точка входа - запуск программы.
 */
int main(void)
{
  fruitreaderfile *fr = fruitreaderfile_new();
  fruitreaderfile_constructor(fr, "fruits.txt");
  start((fruitreader *) fr);
  fruitreader_destructor((fruitreader *) fr);
  fruitreader_delete((fruitreader *) fr);
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
