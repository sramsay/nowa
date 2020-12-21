#include "available_products_list_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "json.h"
#include "points_data.h"
#include "station_info.h"
#include "third_party/cJSON.h"
#include "utils.h"

size_t product_count;

struct product_id* init_available_products(char station_id[restrict static 1]) {
  char* available_product_list_url = malloc(60);
  if (!available_product_list_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(available_product_list_url);
    return false;
  }

  construct_available_product_list_url(station_id, &available_product_list_url);

  cJSON* available_product_list_json = json_init(available_product_list_url);

  cJSON* graph_json =
      cJSON_GetObjectItemCaseSensitive(available_product_list_json, "@graph");

  // Error code
  cJSON* status_json = cJSON_GetObjectItemCaseSensitive(graph_json, "status");
  if (status_json) {
    cJSON* details_json =
        cJSON_GetObjectItemCaseSensitive(graph_json, "detail");
    printf("%s\n", details_json->valuestring);
    free(available_product_list_url);
    return false;
  }

  product_count = cJSON_GetArraySize(graph_json);
  struct product_id* product_list =
      malloc(sizeof(struct product_id) * product_count);
  if (!product_list) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    cJSON_Delete(available_product_list_json);
    cJSON_Delete(graph_json);
    free(available_product_list_url);
    exit(1);
  }

  cJSON* product_json = {0};
  int count = 0;
  cJSON_ArrayForEach(product_json, graph_json) {
    cJSON* product_code_json =
        cJSON_GetObjectItemCaseSensitive(product_json, "productCode");
    size_t product_code_size = strlen(product_code_json->valuestring);
    product_list[count].product_code = malloc(product_code_size + 1);
    if (!product_list[count].product_code) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      cJSON_Delete(available_product_list_json);
      cJSON_Delete(graph_json);
      free(available_product_list_url);
      exit(1);
    }
    strcpy(product_list[count].product_code, product_code_json->valuestring);

    cJSON* product_name_json =
        cJSON_GetObjectItemCaseSensitive(product_json, "productName");
    size_t product_name_size = strlen(product_name_json->valuestring);
    product_list[count].product_name = malloc(product_name_size + 1);
    if (!product_list[count].product_name) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      cJSON_Delete(available_product_list_json);
      cJSON_Delete(graph_json);
      free(available_product_list_url);
      exit(1);
    }
    strcpy(product_list[count].product_name, product_name_json->valuestring);

    count++;
  }

  cJSON_Delete(available_product_list_json);
  free(available_product_list_url);

  return product_list;
}

bool construct_available_product_list_url(char station_id[restrict static 1],
                                          char* available_product_list_url[]) {
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

  sprintf(*available_product_list_url, "%s%s%s",
          "https://api.weather.gov/products/locations/", points.cwa, "/types");

  cleanup_station_info(&sinfo);
  cleanup_points(&points);

  return true;
}
