#ifndef POINTS_DATA_INCLUDED
#define POINTS_DATA_INCLUDED

#include <stdbool.h>

typedef struct points_info points_info;

struct points_info {
  char forecast_url[55];
  char forecast_hourly_url[62];
  char forecast_grid_data_url[46];
  char observation_stations_url[55];
  char forecast_zone_url[47];
  char county_url[45];
  char fire_weather_zone_url[43];
  char radar_station[5];
};
// This JSON also includes bearing and distance (from what, exactly?) and
// timezone.

bool init_points(char lat_long[restrict static 1], struct points_info* points);

#endif
