#include "station_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "station_list_data.h"

extern size_t stations_count;

bool print_stations(char lat_long[static 1]) {
	struct station* station_list = init_station_list(lat_long);

  for (size_t i = 0; i < station_count; i++) {
    printf("%s: %s\n", station_list[i].station_id, station_list[i].name);
  }

  free(station_list);

  return true;
}
