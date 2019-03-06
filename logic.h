/**
 * @file
 * Основной модуль по решению всех задач.
 * Каждый метод решает одну задачу.
 * @author Chip
 */

#ifndef LOGIC_H
#define LOGIC_H

#include <chip_string.h>
#include <fruit.h>
#include <arraylist.h>
#include <hashmap.h>

typedef struct Logic_s Logic;

/** Список всех решаемых задач */
typedef enum
  {
   COUNT,
   DIFFCOUNT,
   SETCOUNT,
   FRUITMAX,
   TASKMAX
  } Task;

Logic *logic_new();

/**
 * Инициализация класса с исходными данными
 * @param list 
 */
void logic_constructor(Logic * const this, ArrayList *list);
void logic_destructor(Logic * const this);

String *logic_get_task_raw(Logic * const this);
String *logic_get_task_xml(Logic * const this);
String *logic_get_task_json(Logic * const this);

/**
 * Вычисление всех задач.
 * Ответ формируется в виде словаря.
 * @return Словарь с результатами расчетов: task => answer
 */
HashMap *logic_get_task(Logic * const this);

/**
 * Вычисление указанной задачи.
 * @param task Название задачи
 * @return Ответ в виде строки
 */
String *logic_get_task_task(Logic * const this, Task task);

/**
 * Задача - вычисление количества фруктов.
 * @return Целое число - количество фруктов
 */
int logic_get_count(Logic * const this);

/**
 * Задача - вычисление количества различных фруктов.
 * Сложность алгоритма - O(N * N)
 * @return Целое число - количество разных фруктов
 */
int logic_get_diff_count(Logic * const this);

/**
 * Задача - вычисление количества различных фруктов.
 * Сложность алгоритма - O(N * log N)
 * @return Целое число - количество разных фруктов
 */
int logic_get_set_count(Logic * const this);

/**
 * Задача - какого фрукты было больше всего.
 * @return константа фрукта, которого было больше всего
 */
Fruit logic_get_fruit_max(Logic * const this);

void logic_delete(Logic *this);

#endif
