#ifndef FRUIT_H
#define FRUIT_H

/*!
  Список всех допустимых наименований
  фруктов в мешке Деда Мороза.
  \file
  \author Chip
*/
typedef enum
  {
   LEMON,
   ORANGE,
   MANDARIN,
   FERRARI,
   TESLA,
   RENAULT,
   MERCEDES,
   BMW,
   FRUIT_MAX
  } Fruit;

/*!
  Получить экземпляр фрукта по заданной строке
  \param[in] line Полученная на вход строка
  \return Если получилось распознать фрукт - экземпляр Fruit.
  Иначе - значение null.
*/
Fruit fruit_get(const char *line);

#endif
