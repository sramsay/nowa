#include "points_data.h"

#include <assert.h>
#include <stdlib.h>
#include <pcre.h>
#include <stdio.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

/*
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
*/

static char* construct_points_url(char lat_long[restrict static 1]);

struct points_info* init_points(char lat_long[restrict static 1]) {
	char* points_url = construct_points_url(lat_long);
	cJSON* points_json = json_init(points_url);

	struct points_info* points = malloc(sizeof(points_info));

	cJSON* properties_json = cJSON_GetObjectItemCaseSensitive(points_json, "properties");

	cJSON* forecast_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecast");
	strlcpy(points->forecast_url, forecast_url_json->valuestring, sizeof(points->forecast_url));

	cJSON* forecast_hourly_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecastHourly");
	strlcpy(points->forecast_hourly_url, forecast_hourly_url_json->valuestring, sizeof(points->forecast_hourly_url));

	cJSON* forecast_grid_data_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecastGridData");
	strlcpy(points->forecast_grid_data_url, forecast_grid_data_url_json->valuestring, sizeof(points->forecast_grid_data_url));

	cJSON* observation_stations_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "observationStations");
	strlcpy(points->observation_stations_url, observation_stations_url_json->valuestring, sizeof(points->observation_stations_url));

	cJSON* forecast_zone_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecastZone");
	strlcpy(points->forecast_zone_url, forecast_zone_url_json->valuestring, sizeof(points->forecast_zone_url));

	cJSON* county_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "county");
	strlcpy(points->county_url, county_url_json->valuestring, sizeof(points->county_url));

	cJSON* fire_weather_zone_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "fireWeatherZone");
	strlcpy(points->fire_weather_zone_url, fire_weather_zone_url_json->valuestring, sizeof(points->fire_weather_zone_url));

	cJSON* radar_station_json = cJSON_GetObjectItemCaseSensitive(properties_json, "radarStation");
	strlcpy(points->radar_station, radar_station_json->valuestring, sizeof(points->radar_station));

	free(points_url);
	cJSON_Delete(points_json);

	return points;

}


static char* construct_points_url(char lat_long[restrict static 1]) {
  // Matches lat/longs of the general form 39.809734,-98.555620
  char* regex_str = "(-?[0-9]*\\.[0-9]+),(-?[0-9]*\\.[0-9]+)";

  const char* pcre_error_msg = {0};
  int pcre_error_offset = {0};
  pcre* regex =
      pcre_compile(regex_str, 0, &pcre_error_msg, &pcre_error_offset, NULL);

  if (regex == NULL) {
    printf("Error: Could not compile '%s': %s\n", regex_str, pcre_error_msg);
    exit(1);
  }

  // Optimize the regex
  pcre_extra* extra = pcre_study(regex, 0, &pcre_error_msg);

  if (pcre_error_msg != NULL) {
    printf("ERROR: Could not study '%s': %s\n", regex_str, pcre_error_msg);
    exit(1);
  }

  // NWS will only accept four digits of precision (which is plenty), and
  // insists on truncated trailing zeros.  So this magic number is really just
  // based on something like -98.5556
  int sub_str[10] = {0};
  int pcre_exec_ret =
      pcre_exec(regex, extra, lat_long, strlen(lat_long), 0, 0, sub_str, 50);

  const char* latitude_match = {0};
  const char* longitude_match = {0};
  pcre_get_substring(lat_long, sub_str, pcre_exec_ret, 1, &(latitude_match));
  pcre_get_substring(lat_long, sub_str, pcre_exec_ret, 2, &(longitude_match));
  char* end = {0};
  assert(strlen(latitude_match) <= 10);
  assert(strlen(longitude_match) <= 10);
  // Converting these strings to actual doubles so we can set precision and
  // truncate zeros
  double latitude = strtod(latitude_match, &end);
  double longitude = strtod(longitude_match, &end);

  char* url = malloc(50);
  sprintf(url, "%s%.4g,%.4g", "https://api.weather.gov/points/", latitude,
          longitude);

  pcre_free_substring(latitude_match);
  pcre_free_substring(longitude_match);
  pcre_free(regex);

  if (extra != NULL) {
#ifdef PCRE_CONFIG_JIT
    pcre_free_study(extra);
#else
    pcre_free(extra);
#endif
  }
  return url;
}




