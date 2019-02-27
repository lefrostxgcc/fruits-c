#include <logic.h>
#include <object.h>
#include <stdlib.h>

struct Logic_s
{
  arraylist *list;
};

static int logic_get_fruit_count(Logic *const this, Fruit find);

Logic *logic_new()
{
  return (Logic *) malloc(sizeof (Logic));
}

void logic_delete(Logic *this)
{
  free(this);
}

void logic_constructor(Logic * const this, arraylist *list)
{
  if (!this)
    return;
  this->list = list;
}

void logic_destructor(Logic * const this)
{
  if (!this)
    return;
  this->list = NULL;
}

int logic_get_count(Logic * const this)
{
  if (!this)
    return 0;
  return arraylist_size(this->list);
}

Fruit logic_get_fruit_max(Logic * const this)
{
  if (!this)
    return FRUIT_MAX;
  int max = 0;
  Fruit fruitMax = FRUIT_MAX;
  for (Fruit fruit = 0; fruit < FRUIT_MAX; fruit++)
    {
      int count = logic_get_fruit_count(this, fruit);
      if (count > max)
        {
          max = count;
          fruitMax = fruit;
        }
    }
  return fruitMax;
}

static int logic_get_fruit_count(Logic * const this, Fruit find)
{
  int count = 0;
  int list_size = arraylist_size(this->list);
  for (int i = 0; i < list_size; i++)
    {
      Fruit fruit = *(Fruit *)object_data(arraylist_get(this->list, i));
      if (fruit == find)
        count++;
    }
  return count;
}
