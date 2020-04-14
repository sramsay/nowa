#include "forecast.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "forecast_data.h"
#include "station_data.h"
#include "points_data.h"
#include "json.h"

#include "third_party/cJSON.h"

bool print_forecast(char station_id[restrict static 1]) {
  struct tm last_updated;
  struct forecast forecasts[14];

  init_forecast(station_id, &last_updated, forecasts);

  char* buf = malloc(53);
  long ts = mktime(&last_updated) - timezone;
  localtime_r(&ts, &last_updated);
  strftime(buf, sizeof(buf), "Last Updated: %A, %d %B %Y, %I:%M:%S %p %Z",
           &last_updated);

  for (size_t i = 0; i < 14; i++) {
    printf("%s: %s\n", forecasts[i].name, forecasts[i].detailed_forecast);
		free(forecasts[i].name);
		free(forecasts[i].detailed_forecast);
  }

	free(buf);

  return 0;
}


bool print_forecast_json(char station_id[restrict static 1]) {
	struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve station data");
    return false;
  }

	char lat_long[41];
  sprintf(lat_long, "%f,%f", sinfo.latitude, sinfo.longitude);

  struct points_info points = {0};
  if (!init_points(lat_long, &points)) {
		fprintf(stderr, "Error: %s\n", "Unable to retrieve points data.");
    return false;
  }

  char* forecast_url = points.forecast_url;
  cJSON* forecast_json = json_init(forecast_url);
	char* output = cJSON_Print(forecast_json);
	puts(output);
	free(points.forecast_url);
	cJSON_Delete(forecast_json);
	free(output);

	return true;
}
