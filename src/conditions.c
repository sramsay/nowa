#include "conditions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conditions_data.h"
#include "station_data.h"
#include "utils.h"

bool print_conditions(char station_id[restrict static 1]) {
  struct station_info info = {0};
	if (!init_station(station_id, &info)) {
		puts("Bad things"); // TODO return value
	}

	struct current_conditions current = {0};
	if (!init_conditions(station_id, &current)) {
		puts("Bad things"); // TODO return value
	}

  printf("Current conditions at %s (%s)\n", info.name, station_id);

  char* dms_latitude = dd_to_dms(info.latitude);
  char latdir = lat_dir(info.latitude);
  char* dms_longitude = dd_to_dms(info.longitude);
  char lngdir = lng_dir(info.longitude);
  printf("%s %c, %s %c\n", dms_latitude, latdir, dms_longitude, lngdir);

  printf("   Summary: %s\n", current.summary);
  printf("   Temperature: %.1f\u00B0F\n", ftemp(current.temperature));

  free(dms_latitude);
  free(dms_longitude);

  return true;
}
