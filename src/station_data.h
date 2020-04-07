#ifndef STATION_DATA_INCLUDED
#define STATION_DATA_INCLUDED

#include <stdbool.h>

typedef struct station_info station_info;

struct station_info {
  double latitude;
  double longitude;
  double elevation;  // meters
  char name[80];
};

// TODO: Note that this JSON structure contains links for forecast, "county,"
// and "fireWeatherZone"

bool init_station(char station_id[restrict static 1], struct station_info* info);

#endif
