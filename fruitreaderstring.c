#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fruitreaderstring_impl.h>

static void (*fruitreaderstring_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

static ArrayList *(*fruitreaderstring_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

static fruitreaderstring_vtable fruitreaderstring_vt =
  {
   .fvoid = fruitreaderstring_void,
   .farraylist = fruitreaderstring_arraylist
  };

FruitReaderString *fruitreaderstring_new(void)
{
  return (FruitReaderString *) malloc(sizeof(FruitReaderString));
}

void fruitreaderstring_constructor(FruitReaderString * const this,
                                   const char *input)
{
  fruitreader_constructor((FruitReader *) this);

  const char pattern[] = "chipfruitreaderXXXXXX";
  const size_t tmpdir_len = strlen(P_tmpdir);
  const size_t path_len = tmpdir_len + 1 + sizeof pattern;
  char *path = (char *) malloc(path_len);
  memcpy(path, P_tmpdir, tmpdir_len);
  path[tmpdir_len] = '/';
  memcpy(path + tmpdir_len + 1, pattern, sizeof pattern);
  FILE *f = fdopen(mkstemp(path), "r+");
  fprintf(f, "%s", input);
  rewind(f);
  free(path);
  this->vt = &fruitreaderstring_vt;
  this->br = f; 
}
