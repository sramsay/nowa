#ifndef ZONEINFO_DATA_INCLUDED
#define ZONEINFO_DATA_INCLUDED

#include <stdbool.h>

typedef struct zoneinfo zoneinfo;

struct zoneinfo {
  char* id;
  char* name;
  char* state;
};

bool init_zoneinfo(char station_id[restrict static 1], struct zoneinfo* zone);

#endif
