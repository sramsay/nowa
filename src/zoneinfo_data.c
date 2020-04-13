#include "zoneinfo_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "json.h"
#include "station_data.h"
#include "third_party/cJSON.h"

bool init_zoneinfo(char station_id[restrict static 1], struct zoneinfo* info) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    puts("Bad things");  // TODO return value
  }

  cJSON* zone_json =
      json_init(sinfo.forecast_url);  // This is actually a URL with a zone_id
                                      // and the resulting object is not real
                                      // forecast object

  cJSON* properties_json =
      cJSON_GetObjectItemCaseSensitive(zone_json, "properties");

  cJSON* id_json = cJSON_GetObjectItemCaseSensitive(properties_json, "id");
	size_t id_size = strlen(id_json->valuestring);
	info->id = malloc(id_size + 1);
  strcpy(info->id, id_json->valuestring);

  cJSON* name_json = cJSON_GetObjectItemCaseSensitive(properties_json, "name");
	size_t name_size = strlen(name_json->valuestring);
	info->name = malloc(name_size + 1);
  strcpy(info->name, name_json->valuestring);

  cJSON* state_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "state");
	size_t state_size = strlen(state_json->valuestring);
	info->state = malloc(state_size + 1);
  strcpy(info->state, state_json->valuestring);

	free(sinfo.name);
	free(sinfo.timezone);
	free(sinfo.forecast_url);
	free(sinfo.county_url);
	free(sinfo.fire_weather_zone_url);
  cJSON_Delete(zone_json);

  return true;
}