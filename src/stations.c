#include "stations.h"

#include <stdio.h>
#include <stdlib.h>

#include "stations_data.h"

extern int stations_count;

int print_stations(char lat_long[static 1]) {
  struct station* station_list = init_stations(lat_long);

  for (size_t i = 0; i < station_count; i++) {
    printf("%s: %s\n", station_list[i].station_id, station_list[i].name);
  }

  free(station_list);

  return 0;
}
