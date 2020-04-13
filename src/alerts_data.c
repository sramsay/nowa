#include "alerts_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alerts_data.h"
#include "json.h"
#include "third_party/cJSON.h"
#include "zoneinfo_data.h"

struct alert* init_alerts(char station_id[restrict static 1], bool json_output) {
  struct zoneinfo zinfo = {0};
  if (!init_zoneinfo(station_id, &zinfo)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve zone info.\n");
    exit(1);
  }

  char* alerts_url = malloc(50);
  sprintf(alerts_url, "%s%s", "https://api.weather.gov/alerts/active/zone/",
          zinfo.id);
  cJSON* alerts_json = json_init(alerts_url);

	if (json_output) {
		struct alert* empty_struct = {0};
		char* output = cJSON_Print(alerts_json);
		puts(output);
		free(output);
		free(zinfo.id);
		free(zinfo.name);
		free(zinfo.state);
		free(alerts_url);
		cJSON_Delete(alerts_json);
		return empty_struct;
	}

  cJSON* features_json =
      cJSON_GetObjectItemCaseSensitive(alerts_json, "features");

  alerts_count = cJSON_GetArraySize(features_json);
  struct alert* alerts_list = malloc(sizeof(struct alert) * alerts_count);

  cJSON* feature_json = {0};
  int count = 0;
  cJSON_ArrayForEach(feature_json, features_json) {
    cJSON* properties_json =
        cJSON_GetObjectItemCaseSensitive(feature_json, "properties");

    cJSON* headline_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "headline");
    size_t headline_size = strlen(headline_json->valuestring);
    alerts_list[count].headline = malloc(headline_size + 1);
    strcpy(alerts_list[count].headline, headline_json->valuestring);

    cJSON* description_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "description");
    size_t description_size = strlen(description_json->valuestring);
    alerts_list[count].description = malloc(description_size + 1);
    strcpy(alerts_list[count].description, description_json->valuestring);

    cJSON* instruction_json =
        cJSON_GetObjectItemCaseSensitive(properties_json, "instruction");
    size_t instruction_size = strlen(instruction_json->valuestring);
    alerts_list[count].instruction = malloc(instruction_size + 1);
    strcpy(alerts_list[count].instruction, instruction_json->valuestring);

    count++;
  }

  free(zinfo.id);
  free(zinfo.name);
  free(zinfo.state);
  free(alerts_url);
  cJSON_Delete(alerts_json);

  return alerts_list;
}
