#ifndef POINTS_DATA_INCLUDED
#define POINTS_DATA_INCLUDED

#include <stdbool.h>

typedef struct points_info points_info;

struct points_info {
  char* forecast_url;
  char* forecast_hourly_url;
  char* forecast_grid_data_url;
  char* observation_stations_url;
  char* forecast_zone_url;
  char* county_url;
  char* fire_weather_zone_url;
  char* radar_station;
};
// This JSON also includes bearing and distance (from what, exactly?) and
// timezone.

bool init_points(char lat_long[restrict static 1], struct points_info* points);

#endif
