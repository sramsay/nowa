#include "air_quality.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "air_quality_data.h"
#include "json.h"
#include "station_data.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool print_air_quality(char station_id[restrict static 1]) {

	struct air_quality* aqi = malloc(sizeof(struct air_quality));
	if (!aqi) {
		fprintf(stderr, "Fatal Error: No available memory.\n");
		return false;
	}

  if (!init_air_quality(station_id, aqi)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve air quality index.\n");
    return false;
  }

  printf("%s", aqi->product_name);
  printf("%s", aqi->product_text);

  cleanup_air_quality(aqi); // if only . . .

	free(aqi);

  return true;
}
