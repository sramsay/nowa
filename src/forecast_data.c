#include "forecast_data.h"

#include <stdio.h>
#include <string.h>

#include "json.h"
#include "points_data.h"
#include "station_data.h"
#include "third_party/cJSON.h"
#include "utils.h"

bool init_forecast(char station_id[restrict static 1], struct tm* last_updated,
                   struct forecast forecasts[static 14]) {
  struct station_info sinfo = {0};
  if (!init_station(station_id, &sinfo)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve station data");
    return false;
  }

  char lat_long[41];
  sprintf(lat_long, "%f,%f", sinfo.latitude, sinfo.longitude);

  struct points_info points = {0};
  if (!init_points(lat_long, &points)) {
    fprintf(stderr, "Error: %s\n", "Unable to retrieve points data");
    return false;
  }

  char* forecast_url = points.forecast_url;

  cJSON* forecast_json = json_init(forecast_url);

  cJSON* properties_json =
      cJSON_GetObjectItemCaseSensitive(forecast_json, "properties");
  cJSON* updated_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "updated");

  char* timestamp = updated_json->valuestring;
  convert_iso8601(timestamp, last_updated);

  cJSON* periods_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "periods");

  cJSON* period_json = {0};
  int count = 0;
  cJSON_ArrayForEach(period_json, periods_json) {
    cJSON* name_json = cJSON_GetObjectItemCaseSensitive(period_json, "name");
    size_t name_size = strlen(name_json->valuestring);
    forecasts[count].name = malloc(name_size + 1);
    strcpy(forecasts[count].name, name_json->valuestring);
    cJSON* detailed_forecast_json =
        cJSON_GetObjectItemCaseSensitive(period_json, "detailedForecast");
    size_t detailed_forecast_size = strlen(detailed_forecast_json->valuestring);
    forecasts[count].detailed_forecast = malloc(detailed_forecast_size + 1);
    strcpy(forecasts[count].detailed_forecast,
           detailed_forecast_json->valuestring);
    count++;
  }

  free(sinfo.name);
  free(sinfo.timezone);
  free(sinfo.forecast_url);
  free(sinfo.county_url);
  free(sinfo.fire_weather_zone_url);
  free(points.forecast_url);
  free(points.forecast_hourly_url);
  free(points.forecast_grid_data_url);
  free(points.observation_stations_url);
  free(points.forecast_zone_url);
  free(points.county_url);
  free(points.fire_weather_zone_url);
  free(points.radar_station);

  cJSON_Delete(forecast_json);

  return true;
}
