#include "station_list_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "points_data.h"
#include "third_party/cJSON.h"

struct station* init_station_list(char lat_long[restrict static 1]) {
  struct points_info points = {0};
  if (!init_points(lat_long, &points)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve points data\n");
    exit(1);
  }

  char* stations_url = points.observation_stations_url;

  cJSON* stations_json = json_init(stations_url);

  cJSON* features_json =
      cJSON_GetObjectItemCaseSensitive(stations_json, "features");

  station_count = cJSON_GetArraySize(features_json);
  struct station* station_list = malloc(sizeof(struct station) * station_count);
	if (!station_list) {
		fprintf(stderr, "Fatal Error: No available memory\n");
		exit(1);
	}

  cJSON* feature_json = {0};
  int count = 0;
  cJSON_ArrayForEach(feature_json, features_json) {
    cJSON* station_properties_json =
        cJSON_GetObjectItemCaseSensitive(feature_json, "properties");

    cJSON* station_identifier_json = cJSON_GetObjectItemCaseSensitive(
        station_properties_json, "stationIdentifier");
    size_t station_id_size = strlen(station_identifier_json->valuestring);
    station_list[count].station_id = malloc(station_id_size + 1);
		if (!station_list[count].station_id) {
			fprintf(stderr, "Fatal Error: No available memory\n");
			exit(1);
		}
    strcpy(station_list[count].station_id,
           station_identifier_json->valuestring);

    cJSON* name_json =
        cJSON_GetObjectItemCaseSensitive(station_properties_json, "name");
    size_t name_size = strlen(name_json->valuestring);
    station_list[count].name = malloc(name_size + 1);
		if (!station_list[count].name) {
			fprintf(stderr, "Fatal Error: No available memory\n");
			exit(1);
		}

    strcpy(station_list[count].name, name_json->valuestring);

    count++;
  }

  free(points.forecast_url);
  free(points.forecast_hourly_url);
  free(points.forecast_grid_data_url);
  free(points.observation_stations_url);
  free(points.forecast_zone_url);
  free(points.county_url);
  free(points.fire_weather_zone_url);
  free(points.radar_station);

  cJSON_Delete(stations_json);

  return station_list;
}
