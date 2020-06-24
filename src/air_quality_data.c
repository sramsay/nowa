#include "air_quality_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "utils.h"
#include "station_data.h"
#include "points_data.h"
#include "third_party/cJSON.h"

bool init_air_quality(char station_id[restrict static 1],
                     struct air_quality* aqi) {
  char* air_quality_list_url = malloc(60);
	if (!air_quality_list_url) {
		fprintf(stderr, "Fatal Error: No available memory\n");
		return false;
	}
	construct_air_quality_list_url(station_id, &air_quality_list_url);

  cJSON* air_quality_list_json = json_init(air_quality_list_url);


  cJSON* graph_json = cJSON_GetObjectItemCaseSensitive(air_quality_list_json, "@graph");

	// TODO: Just grabbing the first item, because it's not entirely clear what differentiates them
	cJSON* graph_item_json = cJSON_GetArrayItem(graph_json, 0);
	cJSON* graph_url = cJSON_GetObjectItemCaseSensitive(graph_item_json, "@id");
	cJSON* air_quality_json = json_init(graph_url->valuestring);

	cJSON* product_name_json = cJSON_GetObjectItemCaseSensitive(air_quality_json, "productName");
	size_t product_name_size = strlen(product_name_json->valuestring);
	aqi->product_name = malloc(product_name_size + 1);
	if (!aqi->product_name) {
		fprintf(stderr, "Fata Error: No available memory.");
		return false;
	}
	strcpy(aqi->product_name, product_name_json->valuestring);
	cJSON* product_text_json = cJSON_GetObjectItemCaseSensitive(air_quality_json, "productText");
	size_t product_text_size = strlen(product_text_json->valuestring);
	aqi->product_text = malloc(product_text_size + 1);
	if (!aqi->product_text) {
		fprintf(stderr, "Fata Error: No available memory.");
		return false;
	}
	strcpy(aqi->product_text, product_text_json->valuestring);

  free(air_quality_list_url);
  cJSON_Delete(air_quality_list_json);
  cJSON_Delete(air_quality_json);

  return true;
}

bool construct_air_quality_list_url(char station_id[restrict static 1],
                              char* air_quality_list_url[]) {
	struct station_info sinfo = {0};
	if (!init_station(station_id, &sinfo)) {
		fprintf(stderr, "Error: %s", "Unable to retrieve station info.\n");
		return false;
	}

	char* lat_long = latlong_string(sinfo.latitude, sinfo.longitude);

	struct points_info points = {0};
	if (!init_points(lat_long, &points)) {
		fprintf(stderr, "Error: %s", "Unable to retrieve points data\n");
    return false;
  }

  sprintf(*air_quality_list_url, "%s%s", "https://api.weather.gov/products/types/AQI/locations/",
          points.cwa);
  return true;
}

void cleanup_air_quality(struct air_quality* aqi) { // if only . . .
	free(aqi->product_name);
	free(aqi->product_text);
}
