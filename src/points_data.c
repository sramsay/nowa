#include "points_data.h"

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <pcre.h>
#include <stdio.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

bool construct_points_url(char lat_long[restrict static 1], char points_url[static 1]);

bool init_points(char lat_long[restrict static 1], struct points_info* points) {
	char* points_url = malloc(50); // TODO: check??
	if (!construct_points_url(lat_long, points_url)) {
		puts("Bad things happened!"); // TODO: exit out
	}

	cJSON* points_json = json_init(points_url);

	cJSON* properties_json = cJSON_GetObjectItemCaseSensitive(points_json, "properties");

	cJSON* forecast_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecast");
	strcpy(points->forecast_url, forecast_url_json->valuestring);

	cJSON* forecast_hourly_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecastHourly");
	strcpy(points->forecast_hourly_url, forecast_hourly_url_json->valuestring);

	cJSON* forecast_grid_data_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecastGridData");
	strcpy(points->forecast_grid_data_url, forecast_grid_data_url_json->valuestring);

	cJSON* observation_stations_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "observationStations");
	strcpy(points->observation_stations_url, observation_stations_url_json->valuestring);

	cJSON* forecast_zone_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "forecastZone");
	strcpy(points->forecast_zone_url, forecast_zone_url_json->valuestring);

	cJSON* county_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "county");
	strcpy(points->county_url, county_url_json->valuestring);

	cJSON* fire_weather_zone_url_json = cJSON_GetObjectItemCaseSensitive(properties_json, "fireWeatherZone");
	strcpy(points->fire_weather_zone_url, fire_weather_zone_url_json->valuestring);

	cJSON* radar_station_json = cJSON_GetObjectItemCaseSensitive(properties_json, "radarStation");
	strcpy(points->radar_station, radar_station_json->valuestring);

	free(points_url);
	cJSON_Delete(points_json);

	return points;
}


bool construct_points_url(char lat_long[restrict static 1], char points_url[static 1]) {
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

  sprintf(points_url, "%s%.4g,%.4g", "https://api.weather.gov/points/", latitude,
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
  return true;
}
