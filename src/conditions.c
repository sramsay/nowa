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

	struct current_conditions* current = malloc(sizeof(struct current_conditions));
	if (!current) {
		fprintf(stderr, "Fatal Error: No available memory.\n");
		return false;
	}

  if (!init_conditions(station_id, current)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve current conditions.\n");
    return false;
  }

  printf("Current conditions at %s (%s)\n", sinfo.name, station_id);

  char* dms_latitude = dd_to_dms(sinfo.latitude);
  char latdir = lat_dir(sinfo.latitude);
  char* dms_longitude = dd_to_dms(sinfo.longitude);
  char lngdir = lng_dir(sinfo.longitude);
  printf("%s %c, %s %c\n", dms_latitude, latdir, dms_longitude, lngdir);

  printf("   Summary: %s\n", current->summary);
  printf("   Temperature: %.1f\u00B0F\n", ftemp(current->temperature));
	printf("   Relative Humidity: %.1f%%\n", current->relative_humidity);
	double dewpoint = ftemp(current->dewpoint);
	printf("   Dewpoint: %.1f\u00B0F (%s)\n", dewpoint, comfort_scale(dewpoint)); // TODO: Move
	if (current->heat_index >= 26.7) { // 80°F
		printf("   Heat Index: %.1f\u00B0F\n", ftemp(current->heat_index));
	}
	if (current->wind_speed > 0.0) {
		printf("   Wind: From the %s (%d\u00B0) at %.1f mph", bearing_to_compass_dir(current->wind_direction), current->wind_direction, kph_to_mph(current->wind_speed));
		if (current->wind_gust > 0.0) {
			printf(", gusting to %.1f mph\n", kph_to_mph(current->wind_gust));
		} else {
			printf("\n");
		}
	}
	if (current->wind_chill > 0.0) {
		printf("   Wind Chill: %.1f\u00B0F\n", ftemp(current->wind_chill));
	}
	printf("   Pressure: %.1f mb\n", pa_to_mb(current->pressure)); 
	if (current->visibility > 0) {
		printf("   Visibility: %.1f mi\n", m_to_mi(current->visibility));
	}

  cleanup_conditions(current);
  cleanup_station_info(&sinfo);

	free(current);
  free(dms_latitude);
  free(dms_longitude);

  return true;
}


bool print_conditions_json(char station_id[restrict static 1]) {
  char* conditions_url = malloc(60);
	if (!conditions_url) {
		fprintf(stderr, "Fatal Error: No available memory\n");
		return false;
	}
  if (!construct_conditions_url(station_id, &conditions_url)) {
    fprintf(stderr, "Error: %s\n", "Unable to construction conditions URL.");
    return false;
  }
  cJSON* conditions_json = json_init(conditions_url);
  char* output = cJSON_Print(conditions_json);
  puts(output);
  cJSON_Delete(conditions_json);

  free(output);
	free(conditions_url);

  return true;
}
