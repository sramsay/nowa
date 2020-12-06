#include "product.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "json.h"
#include "product_data.h"
#include "station_data.h"
#include "third_party/cJSON.h"

bool print_product(char station_id[restrict static 1], char* product_code) {
  struct product* pd = malloc(sizeof(struct product));
  if (!pd) {
    fprintf(stderr, "Fatal Error: No available memory.\n");
    free(pd);
    return false;
  }

  if (!init_product(station_id, pd, product_code)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve requested product.\n");
    free(pd);
    return false;
  }

  printf("%s", pd->product_name);
  printf("%s", pd->product_text);

  cleanup_product(pd);  // if only . . .

  free(pd);

  return true;
}

bool print_product_json(char station_id[restrict static 1],
                        char* product_code) {
  char* product_list_url = malloc(60);

  if (!product_list_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
  }

  if (!construct_product_list_url(station_id, &product_list_url,
                                  product_code)) {
    fprintf(stderr, "Error: %s\n", "Unable to construct product URL.");
    return false;
  }
  cJSON* product_json = json_init(product_list_url);
  char* output = cJSON_Print(product_json);
  puts(output);
  cJSON_Delete(product_json);

  free(output);
  free(product_list_url);

  return true;
}
