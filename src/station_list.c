#include "station_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "json.h"
#include "points_data.h"
#include "station_list_data.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool print_stations(char lat_long[static 1]) {
  struct station* station_list = init_station_list(lat_long);
 
	printf("%s%s\n", "Available Weather Stations for ", lat_long);
  puts("ID    Location");
  puts("----  --------");
  for (size_t i = 0; i < station_count; i++) {
    printf("%s: %s\n", station_list[i].station_id, station_list[i].name);
    free(station_list[i].station_id);
    free(station_list[i].name);
  }

  free(station_list);

  return true;
}

bool print_stations_json(char lat_long[static 1]) {
  struct points_info points = {0};
  if (!init_points(lat_long, &points)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve points data.");
    return false;
  }

  char* stations_url = points.observation_stations_url;

  cJSON* stations_json = json_init(stations_url);
  char* output = cJSON_Print(stations_json);
  puts(output);

  free(points.forecast_url);
  free(points.forecast_hourly_url);
  free(points.forecast_grid_data_url);
  free(points.observation_stations_url);
  free(points.forecast_zone_url);
  free(points.county_url);
  free(points.fire_weather_zone_url);
  free(points.radar_station);

  cJSON_Delete(stations_json);
  free(output);

  return true;
}
