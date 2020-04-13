#include "conditions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "conditions_data.h"
#include "station_data.h"
#include "utils.h"

bool print_conditions(char station_id[restrict static 1], bool json_output) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve station info.\n");
    return false;
  }

  struct current_conditions current = {0};
  if (!init_conditions(station_id, &current, json_output)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve current conditions.\n");
    return false;
  }

	if (json_output) {
		cleanup_conditions(&current);
		cleanup_station_info(&sinfo);
		return true;
	}

  printf("Current conditions at %s (%s)\n", sinfo.name, station_id);

  char* dms_latitude = dd_to_dms(sinfo.latitude);
  char latdir = lat_dir(sinfo.latitude);
  char* dms_longitude = dd_to_dms(sinfo.longitude);
  char lngdir = lng_dir(sinfo.longitude);
  printf("%s %c, %s %c\n", dms_latitude, latdir, dms_longitude, lngdir);

  printf("   Summary: %s\n", current.summary);
  printf("   Temperature: %.1f\u00B0F\n", ftemp(current.temperature));

	cleanup_conditions(&current);
	cleanup_station_info(&sinfo);
	
  free(dms_latitude);
  free(dms_longitude);

  return true;
}
