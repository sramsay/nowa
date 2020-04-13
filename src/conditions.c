#include "conditions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "conditions_data.h"
#include "station_data.h"
#include "utils.h"

bool print_conditions(char station_id[restrict static 1]) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s", "Unable to restrieve station info.\n");
    return false;
  }

  struct current_conditions current = {0};
  if (!init_conditions(station_id, &current)) {
    return false;
  }

  printf("Current conditions at %s (%s)\n", sinfo.name, station_id);

  char* dms_latitude = dd_to_dms(sinfo.latitude);
  char latdir = lat_dir(sinfo.latitude);
  char* dms_longitude = dd_to_dms(sinfo.longitude);
  char lngdir = lng_dir(sinfo.longitude);
  printf("%s %c, %s %c\n", dms_latitude, latdir, dms_longitude, lngdir);

  printf("   Summary: %s\n", current.summary);
  printf("   Temperature: %.1f\u00B0F\n", ftemp(current.temperature));

  free(sinfo.name);
  free(sinfo.timezone);
  free(sinfo.forecast_url);
  free(sinfo.county_url);
  free(sinfo.fire_weather_zone_url);
  free(dms_latitude);
  free(dms_longitude);
  free(current.summary);

  return true;
}
