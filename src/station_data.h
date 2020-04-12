#ifndef STATION_DATA_INCLUDED
#define STATION_DATA_INCLUDED

#include <stdbool.h>

typedef struct station_info station_info;

struct station_info {
  double latitude;
  double longitude;
  double elevation;  // meters
  char* name;
  char* timezone;
  char* forecast_url;
  char* county_url;
  char* fire_weather_zone_url;
};

bool init_station(char station_id[restrict static 1],
                  struct station_info* info);

#endif
