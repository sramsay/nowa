#include "product.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "product_data.h"
#include "json.h"
#include "station_data.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool print_product(char station_id[restrict static 1], char* product_code) {

	struct product* pd = malloc(sizeof(struct product));
	if (!pd) {
		fprintf(stderr, "Fatal Error: No available memory.\n");
		return false;
	}

  if (!init_product(station_id, pd, product_code)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve air quality index.\n");
    return false;
  }

  printf("%s", pd->product_name);
  printf("%s", pd->product_text);

  cleanup_product(pd); // if only . . .

	free(pd);

  return true;
}
