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
    puts("Bad things");  // TODO return value
  }

  char* stations_url = points.observation_stations_url;

  cJSON* stations_json = json_init(stations_url);

  cJSON* features_json =
      cJSON_GetObjectItemCaseSensitive(stations_json, "features");

  station_count = cJSON_GetArraySize(features_json);
  struct station* station_list = malloc(sizeof(struct station) * station_count);

  cJSON* feature_json = {0};
  int count = 0;
  cJSON_ArrayForEach(feature_json, features_json) {
    cJSON* station_properties_json =
        cJSON_GetObjectItemCaseSensitive(feature_json, "properties");

    cJSON* station_identifier_json = cJSON_GetObjectItemCaseSensitive(
        station_properties_json, "stationIdentifier");
    strcpy(station_list[count].station_id,
           station_identifier_json->valuestring);

    cJSON* name_json =
        cJSON_GetObjectItemCaseSensitive(station_properties_json, "name");
    strcpy(station_list[count].name, name_json->valuestring);

    count++;
  }

  cJSON_Delete(stations_json);

  return station_list;
}
