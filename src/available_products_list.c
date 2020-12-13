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
    printf("%s  %s\n", product_list[i].product_code,
           product_list[i].product_name);
    free(product_list[i].product_code);
    free(product_list[i].product_name);
  }

  free(product_list);

  return true;
}

/*
TODO: bool print_forecast_json(char station_id[restrict static 1]) {

}
*/
