#include "available_product_data.h"

#include <stdbool.h>

#include "json.h"
#include "points_data.h"
#include "station_data.h"
#include "third_party/cJSON.h"

bool init_available_products(char stations_id[restrict static 1], struct available_product* ap) {
	char* available_product_list_url = malloc(60);
	if (!available_product_list_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    return false;
  }

	construct_available_product_list_url(station_id, &available_product_list_url);

	cJSON* available_product_list_json = json(available_product_list_url);
	// Continue using product_data.c as a model


}

bool construct_available_product_list_url(char station_id[restrict static 1], char* available_product_list_url[]) {
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

  sprintf(*product_list_url, "%s%s%s",
          "https://api.weather.gov/products/locations/", points.cwa, "/types");

  cleanup_station_info(&sinfo);
  cleanup_points(&points);

  return true;
	://iterm2.com/shell_integration/install_shell_integration_and_utilities.sh | bash
		/ Continue using product_data.c as a model
}
