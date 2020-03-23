#ifndef JSON_INCLUDED
#define JSON_INCLUDED

#include <stdlib.h>

#include "cJSON.h"

typedef struct memoryStruct memoryStruct;
struct memoryStruct {
  char* memory;
  size_t size;
};

cJSON* json_init(char* url);

#endif
