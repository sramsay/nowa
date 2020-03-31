#include "stations.h"

#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "stations_data.h"
#include "third_party/cJSON.h"

int print_stations(char lat_long[static 1]) {

	struct station* station_list = init_stations(lat_long);
	puts("here");

	for (size_t i = 0; i < sizeof(*station_list) / sizeof(struct station); i++) {
		printf("%s: %s\n", station_list[i].station_id, station_list[i].name);
	}

  return 0;
}
