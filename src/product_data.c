#include "product_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "points_data.h"
#include "station_data.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool init_product(char station_id[restrict static 1], struct product* pd,
                  char* product_code) {
  char* product_list_url = malloc(60);
  if (!product_list_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
  }
  construct_product_list_url(station_id, &product_list_url, product_code);

  cJSON* product_list_json = json_init(product_list_url);

  cJSON* graph_json =
      cJSON_GetObjectItemCaseSensitive(product_list_json, "@graph");

  cJSON* graph_item_json = cJSON_GetArrayItem(graph_json, 0);
  cJSON* graph_url = cJSON_GetObjectItemCaseSensitive(graph_item_json, "@id");
  cJSON* product_json = json_init(graph_url->valuestring);

  cJSON* product_code_json =
      cJSON_GetObjectItemCaseSensitive(product_json, "productName");
  size_t product_code_size = strlen(product_code_json->valuestring);
  pd->product_code = malloc(product_code_size + 1);
  if (!pd->product_code) {
    fprintf(stderr, "Fata Error: No available memory.");
    free(product_list_url);
    return false;
  }
  strcpy(pd->product_code, product_code_json->valuestring);
  cJSON* product_text_json =
      cJSON_GetObjectItemCaseSensitive(product_json, "productText");
  size_t product_text_size = strlen(product_text_json->valuestring);
  pd->product_text = malloc(product_text_size + 1);
  if (!pd->product_text) {
    fprintf(stderr, "Fata Error: No available memory.");
    free(product_list_url);
    return false;
  }
  strcpy(pd->product_text, product_text_json->valuestring);

  free(product_list_url);
  cJSON_Delete(product_list_json);
  cJSON_Delete(product_json);

  return true;
}

bool construct_product_list_url(char station_id[restrict static 1],
                                char* product_list_url[], char* product_code) {
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

  sprintf(*product_list_url, "%s%s%s%s",
          "https://api.weather.gov/products/types/", product_code,
          "/locations/", points.cwa);

  cleanup_station_info(&sinfo);
  cleanup_points(&points);

  free(lat_long);

  return true;
}

void cleanup_product(struct product* pd) {
  free(pd->product_code);
  free(pd->product_text);
}
