#include "conditions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "conditions_data.h"
#include "json.h"
#include "station_data.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool print_conditions(char station_id[restrict static 1]) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve station info.\n");
    return false;
  }

  struct current_conditions current = {0};
  if (!init_conditions(station_id, &current)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve current conditions.\n");
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

  cleanup_conditions(&current);
  cleanup_station_info(&sinfo);

  free(dms_latitude);
  free(dms_longitude);

  return true;
}

bool print_conditions_json(char station_id[restrict static 1]) {
  char* conditions_url = {0};
  if (!construct_conditions_url(station_id, &conditions_url)) {
    fprintf(stderr, "Error: %s\n", "Unable to construction conditions URL.");
    return false;
  }
  cJSON* conditions_json = json_init(conditions_url);
  char* output = cJSON_Print(conditions_json);
  puts(output);
  free(conditions_url);
  cJSON_Delete(conditions_json);
  free(output);

  return true;
}
