#ifndef CONDITIONS_DATA_INCLUDED
#define CONDITIONS_DATA_INCLUDED

#include <stdbool.h>

typedef struct current_conditions current_conditions;

struct current_conditions {
	int elevation;
	char* timestamp;
	char* metar;
  char* summary;
  double temperature;
  double dewpoint;
  int wind_direction;
  double wind_speed;
	double wind_gust; // double?
	int pressure;
	int sl_pressure;
	int visibility;
	double max_temp_24;
	double min_temp_24;
	double precip_hour;
	double precip_3hour;
	double precip_6hour;
	double relative_humidity;
	double wind_chill;
	double heat_index;
};

// Also includes cloudLayers, though it's not clear if this is useful.

bool init_conditions(char station_id[restrict static 1],
                     struct current_conditions* current);
bool construct_conditions_url(char station_id[restrict static 1],
                              char* conditions_url[static 1]);
void cleanup_conditions(struct current_conditions* current);

#endif
