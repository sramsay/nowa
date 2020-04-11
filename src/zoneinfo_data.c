#include "zoneinfo_data.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "json.h"
#include "station_data.h"
#include "third_party/cJSON.h"

bool init_zoneinfo(char station_id[restrict static 1], struct zoneinfo* info) {

	struct station_info sinfo = {0};
	if (!init_station(station_id, &sinfo)) {
    puts("Bad things"); // TODO return value
  }

	cJSON* zone_json = json_init(sinfo.forecast_url); // This is actually a URL with a zone_id
																										// and the resulting object is not real
																										// forecast object


	cJSON* properties_json = cJSON_GetObjectItemCaseSensitive(zone_json, "properties");
	cJSON* id_json = cJSON_GetObjectItemCaseSensitive(properties_json, "id");

	strcpy(info->id, id_json->valuestring); 

	cJSON* name_json = cJSON_GetObjectItemCaseSensitive(properties_json, "name");

	strcpy(info->name, name_json->valuestring); 

	cJSON* state_json = cJSON_GetObjectItemCaseSensitive(properties_json, "state");

	strcpy(info->state, state_json->valuestring); 

  cJSON_Delete(zone_json);

  return true;
}
