#include "conditions_data.h"

#include <stdio.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"


currentConditions* init_conditions(char station_id[restrict static 1]) {

	char* url = malloc(50); // TODO: ??
	sprintf(url, "%s%s%s", "https://api.weather.gov/stations/", station_id, "/observations/latest");
	puts(url);
  cJSON* json = json_init(url);

  cJSON* json_properties = cJSON_GetObjectItemCaseSensitive(json, "properties");

  cJSON* json_text_description =
      cJSON_GetObjectItemCaseSensitive(json_properties, "textDescription");
  cJSON* json_temperature =
      cJSON_GetObjectItemCaseSensitive(json_properties, "temperature");
  cJSON* json_dewpoint =
      cJSON_GetObjectItemCaseSensitive(json_properties, "dewpoint");
  cJSON* json_wind_direction =
      cJSON_GetObjectItemCaseSensitive(json_properties, "windDirection");
  cJSON* json_wind_speed =
      cJSON_GetObjectItemCaseSensitive(json_properties, "windSpeed");

  cJSON* json_temperature_v =
      cJSON_GetObjectItemCaseSensitive(json_temperature, "value");
  cJSON* json_dewpoint_v =
      cJSON_GetObjectItemCaseSensitive(json_dewpoint, "value");
  cJSON* json_wind_direction_v =
      cJSON_GetObjectItemCaseSensitive(json_wind_direction, "value");
  cJSON* json_wind_speed_v =
      cJSON_GetObjectItemCaseSensitive(json_wind_speed, "value");

	currentConditions *current = malloc(sizeof(currentConditions));

  strcpy(current->summary, json_text_description->valuestring);
  current->temperature = json_temperature_v->valuedouble;
  current->dewpoint = json_dewpoint_v->valuedouble;
  current->wind_direction = json_wind_direction_v->valueint;
  current->wind_speed = json_wind_speed_v->valuedouble;

	free(url);
  cJSON_Delete(json);
	
	return current;
}
