#include "conditions.h"

#include <stdio.h>
#include <stdlib.h>

#include "conditions_data.h"
#include "station_data.h"
#include "utils.h"

int print_conditions(char station_id[restrict static 1]) {
  struct station_info* info = init_station(station_id);
  struct current_conditions* current = init_conditions(station_id);

  printf("Current conditions at %s (%s)\n", info->name, station_id);

  char* dms_latitude = dd_to_dms(info->latitude);
  char latdir = lat_dir(info->latitude);
  char* dms_longitude = dd_to_dms(info->longitude);
  char lngdir = lng_dir(info->longitude);
  printf("%s %c, %s %c\n", dms_latitude, latdir, dms_longitude, lngdir);

  printf("   Summary: %s\n", current->summary);
  printf("   Temperature: %.1f\u00B0F\n", ftemp(current->temperature));

  free(info);
  free(current);
  free(dms_latitude);
  free(dms_longitude);

  return 0;
}
