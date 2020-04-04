#ifndef JSON_INCLUDED
#define JSON_INCLUDED

#include <stdlib.h>

#include "third_party/cJSON.h"

typedef struct memory_struct memory_struct;

struct memory_struct {
  char* memory;
  size_t size;
};

cJSON* json_init(char const url[restrict static 1]);

#endif
