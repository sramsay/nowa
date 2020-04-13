#ifndef STATION_LIST_DATA_INCLUDED
#define STATION_LIST_DATA_INCLUDED

#include <stdlib.h>

typedef struct station station;

struct station {
  char* station_id;
  char* name;
};

struct station* init_station_list(char lat_long[restrict static 1]);

size_t station_count;

#endif
