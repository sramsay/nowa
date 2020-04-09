#ifndef STATION_DATA_INCLUDED
#define STATION_DATA_INCLUDED

#include <stdbool.h>

typedef struct station_info station_info;

struct station_info {
  double latitude;
  double longitude;
  double elevation;  // meters
  char name[80];
	char forecast_url[50];
	char county_url[50];
	char fire_weather_zone_url[50];
};

bool init_station(char station_id[restrict static 1], struct station_info* info);

#endif
