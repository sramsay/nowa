#include "product_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "available_products_list_data.h"
#include "json.h"
#include "points_data.h"
#include "station_info.h"
#include "third_party/cJSON.h"
#include "utils.h"

void cleanup_product_list(product_id* pl);

bool init_product(char station_id[restrict static 1], struct product* pd,
                  char* product_code) {
  // First, check to make sure the requested product exists for the given
  // station
  struct product_id* product_list = init_available_products(station_id);

  bool contains_code = false;
  for (size_t i = 0; i < product_count; i++) {
    if (strcmp(product_list[i].product_code, product_code) == 0) {
      contains_code = true;
    }
  }

  if (contains_code) {
    char* product_list_url = malloc(60);
    if (!product_list_url) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      cleanup_product_list(product_list);
      return false;
    }
    construct_product_list_url(station_id, &product_list_url, product_code);

    cJSON* product_list_json = json_init(product_list_url);

    cJSON* graph_json =
        cJSON_GetObjectItemCaseSensitive(product_list_json, "@graph");

    // Error code
    cJSON* status_json = cJSON_GetObjectItemCaseSensitive(graph_json, "status");
    if (status_json) {
      cJSON* details_json =
          cJSON_GetObjectItemCaseSensitive(graph_json, "detail");
      printf("%s\n", details_json->valuestring);
      cleanup_product_list(product_list);
      free(product_list_url);
      return false;
    }

    cJSON* graph_item_json = cJSON_GetArrayItem(graph_json, 0);
    cJSON* graph_url = cJSON_GetObjectItemCaseSensitive(graph_item_json, "@id");
    cJSON* product_json = json_init(graph_url->valuestring);

    cJSON* product_code_json =
        cJSON_GetObjectItemCaseSensitive(product_json, "productName");
    size_t product_code_size = strlen(product_code_json->valuestring);
    pd->product_code = malloc(product_code_size + 1);
    if (!pd->product_code) {
      cleanup_product_list(product_list);
      free(product_list_url);
      fprintf(stderr, "Fatal Error: No available memory.");
      return false;
    }
    strcpy(pd->product_code, product_code_json->valuestring);
    cJSON* product_text_json =
        cJSON_GetObjectItemCaseSensitive(product_json, "productText");
    size_t product_text_size = strlen(product_text_json->valuestring);
    pd->product_text = malloc(product_text_size + 1);
    if (!pd->product_text) {
      cleanup_product_list(product_list);
      free(product_list_url);
      fprintf(stderr, "Fata Error: No available memory.");
      return false;
    }
    strcpy(pd->product_text, product_text_json->valuestring);

    free(product_list_url);
    cleanup_product_list(product_list);
    cJSON_Delete(product_list_json);
    cJSON_Delete(product_json);

    return true;
  } else {
    cleanup_product_list(product_list);
    printf("Product %s is not currently available for requested station %s\n",
           product_code, station_id);
    free(product_code);
    exit(0);
  }
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
  free(pd);
}

void cleanup_product_list(product_id* pl) {
  for (size_t i = 0; i < product_count; i++) {
    free(pl[i].product_code);
    free(pl[i].product_name);
  }
  free(pl);
}
