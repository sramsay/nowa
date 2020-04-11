#include "alerts_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alerts_data.h"
#include "json.h"
#include "third_party/cJSON.h"
#include "zoneinfo_data.h"

struct alert* init_alerts(char station_id[restrict static 1]) {
  struct zoneinfo info = {0};
  if (!init_zoneinfo(station_id, &info)) {
    puts("Bad things");  // TODO return value
  }

  char* alerts_url = malloc(50);
  sprintf(alerts_url, "%s%s", "https://api.weather.gov/alerts/active/zone/",
          info.id);
  cJSON* alerts_json = json_init(alerts_url);

  cJSON* features_json =
      cJSON_GetObjectItemCaseSensitive(alerts_json, "features");

  alerts_count = cJSON_GetArraySize(features_json);
  struct alert* alerts_list = malloc(sizeof(struct alert) * alerts_count);

  cJSON* feature_json = 0;
  int count = 0;
  cJSON_ArrayForEach(feature_json, features_json) {
    cJSON* properties_json =
        cJSON_GetObjectItemCaseSensitive(feature_json, "properties");

    cJSON* headline_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "headline");
    alerts_list[count].headline =
        malloc(sizeof(headline_json->valuestring) + 1);  // TODO: +1?
    alerts_list[count].headline = strdup(headline_json->valuestring);

    cJSON* description_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "description");
    alerts_list[count].description =
        malloc(sizeof(description_json->valuestring) + 1);  // TODO: +1?
    alerts_list[count].description = strdup(description_json->valuestring);

    cJSON* instruction_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "instruction");
    alerts_list[count].instruction =
        malloc(sizeof(instruction_json->valuestring) + 1);  // TODO: +1?
    alerts_list[count].instruction = strdup(instruction_json->valuestring);

    count++;
  }

  // TODO: These needs a destructor object for all these inner strings

  cJSON_Delete(alerts_json);

  return alerts_list;
}
