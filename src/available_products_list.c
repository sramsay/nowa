#include "available_products_list.h"

#include <stdbool.h>
#include <stdio.h>

#include "available_products_list_data.h"
#include "json.h"
#include "third_party/cJSON.h"

bool print_available_products(char station_id[restrict static 1]) {
  struct product* product_list = init_available_products(station_id);

  printf("%s %s:\n\n", "Forecast Office Products Available for", station_id);
  puts("Code  Description");
  puts("----  -----------");
  for (size_t i = 0; i < product_count; i++) {
    printf("%s   %s\n", product_list[i].product_code,
           product_list[i].product_name);
    free(product_list[i].product_code);
    free(product_list[i].product_name);
  }

  free(product_list);

  return true;
}

bool print_available_products_json(char station_id[restrict static 1]) {
	char* available_product_list_url = malloc(60);
	if(!available_product_list_url) {
		fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
	}

	construct_available_product_list_url(station_id, &available_product_list_url);

	cJSON* available_product_list_json = json_init(available_product_list_url);
	char* output = cJSON_Print(available_product_list_json);
	puts(output);

	free(available_product_list_url);
	cJSON_Delete(available_product_list_json);

	return true;
}
