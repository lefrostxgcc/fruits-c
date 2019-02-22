#include <stdlib.h>
#include <string.h>
#include <fruitreader.h>
#include <fruit.h>

typedef struct fruitreader_s
{
  char dummy;
} fruitreader;

static char *read_line(char *buf, int size, FILE *stream)
{
  if (!fgets(buf, size, stream))
    return NULL;
  char *nl = strchr(buf, '\n');
  if (nl)
    *nl = '\0';
  return buf;
}

fruitreader *fruitreader_new(void)
{
  return (fruitreader *) malloc(sizeof (fruitreader));
}

void fruitreader_delete(fruitreader *this)
{
  free(this);
}

void fruitreader_constructor(fruitreader * const this)
{
  (void) this;
}

arraylist *fruitreader_read(fruitreader * const this)
{
  return fruitreader_reads(this, stdin);
}

arraylist *fruitreader_readf(fruitreader * const this, const char *filename)
{
  FILE *f = fopen(filename, "r");
  if (!f)
    return NULL;
  arraylist *list = fruitreader_reads(this, f);
  fclose(f);
  return list;
}

arraylist *fruitreader_read_from_string(fruitreader * const this,
                                        const char *input)
{
  const char pattern[] = "chipfruitreaderXXXXXX";
  const size_t tmpdir_len = strlen(P_tmpdir);
  const size_t path_len = tmpdir_len + 1 + sizeof pattern;
  char *path = (char *) malloc(path_len);
  memcpy(path, P_tmpdir, tmpdir_len);
  memcpy(path + tmpdir_len, "/", 1);
  memcpy(path + tmpdir_len + 1, pattern, sizeof pattern);
  int fd = mkstemp(path);
  FILE *f = fdopen(fd, "r+");
  fprintf(f, "%s", input);
  rewind(f);
  arraylist *list = fruitreader_reads(this, f);
  fclose(f);
  remove(path);
  free(path);
  return list;
}

arraylist *fruitreader_reads(fruitreader * const this, FILE *stream)
{
  char line[80];
  arraylist *list = arraylist_new();
  arraylist_constructor(list);
  while (strcmp(read_line(line, sizeof line, stream), "") != 0)
    {
      Fruit fruit = fruit_get(line);
      if (fruit == FRUIT_MAX)
        continue;
      object *object_fruit = object_new();
      object_constructor(object_fruit, &fruit, sizeof fruit);
      arraylist_add(list, object_fruit);
      object_destructor(object_fruit);
      object_free(&object_fruit);
    }
  return list;
}

void fruitreader_destructor(fruitreader * const this)
{
  (void) this;
}
