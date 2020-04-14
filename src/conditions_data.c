#include "conditions_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "json.h"
#include "third_party/cJSON.h"

bool init_conditions(char station_id[restrict static 1],
                     struct current_conditions* current) {
	char* conditions_url = {0};
	if (!construct_conditions_url(station_id, &conditions_url)) {
		fprintf(stderr, "Error: %s\n", "Unable to construct conditions URL.");
		return false;
	}
  cJSON* conditions_json = json_init(conditions_url);

  cJSON* properties_json =
      cJSON_GetObjectItemCaseSensitive(conditions_json, "properties");

  cJSON* text_description_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "textDescription");

  size_t size = strlen(text_description_json->valuestring);
  current->summary = malloc(size + 1);
  strcpy(current->summary, text_description_json->valuestring);

  cJSON* temperature_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "temperature");
  cJSON* temperature_value_json =
      cJSON_GetObjectItemCaseSensitive(temperature_json, "value");

  current->temperature = temperature_value_json->valuedouble;

  cJSON* dewpoint_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "dewpoint");
  cJSON* dewpoint_value_json =
      cJSON_GetObjectItemCaseSensitive(dewpoint_json, "value");

  current->dewpoint = dewpoint_value_json->valuedouble;

  cJSON* wind_direction_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "windDirection");
  cJSON* wind_direction_value_json =
      cJSON_GetObjectItemCaseSensitive(wind_direction_json, "value");

  current->wind_direction = wind_direction_value_json->valueint;

  cJSON* wind_speed_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "windSpeed");
  cJSON* wind_speed_value_json =
      cJSON_GetObjectItemCaseSensitive(wind_speed_json, "value");

  current->wind_speed = wind_speed_value_json->valuedouble;

  free(conditions_url);
  cJSON_Delete(conditions_json);

  return true;
}


void cleanup_conditions(struct current_conditions* current) {
	free(current->summary);
}


bool construct_conditions_url(char station_id[restrict static 1], char* conditions_url[static 1]) {
  *conditions_url = malloc(60);
  sprintf(*conditions_url, "%s%s%s", "https://api.weather.gov/stations/", station_id,
          "/observations/latest");
	return true;
}
