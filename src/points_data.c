#include "points_data.h"

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
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
  PCRE2_SPTR pattern = (PCRE2_SPTR)"(-?[0-9]*\\.[0-9]+),(-?[0-9]*\\.[0-9]+)";
	PCRE2_SPTR subject = (PCRE2_SPTR)lat_long;


  int error_num_pcre2 = {0};
  PCRE2_SIZE error_offset_pcre2 = {0};
  pcre2_code* regex_pcre2 =
      pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &error_num_pcre2, &error_offset_pcre2, NULL);

	// TODO: Maybe check the value of pcre2_error_num and see if there's a "success" code we
	// can initialize the variable with?

  if (regex_pcre2 == NULL) {
		PCRE2_UCHAR buffer[256];
		pcre2_get_error_message(error_num_pcre2, buffer, sizeof(buffer));
		printf("PCRE2 compilation failed at offset %d: %s\n", (int)error_offset_pcre2, buffer);
    exit(1);
  }

	pcre2_match_data* match_data = pcre2_match_data_create_from_pattern(regex_pcre2, NULL);

	int return_code_pcre2 = pcre2_match(regex_pcre2, subject, strlen((char *)subject), 0, 0, match_data, NULL);

	if (return_code_pcre2 < 0) {
		switch (return_code_pcre2) {
		case PCRE2_ERROR_NOMATCH:
			printf("No match\n");
			break;
    default:
			printf("Matching error %d\n", return_code_pcre2);
			break;
    }
		pcre2_match_data_free(match_data);   /* Release memory used for the match */
		pcre2_code_free(regex_pcre2);        /* data and the compiled pattern.    */
		return false;
  }

  PCRE2_UCHAR8* latitude_match = {0};
  PCRE2_UCHAR8* longitude_match = {0};
	size_t latitude_length;
	size_t longitude_length;
  pcre2_substring_get_bynumber(match_data, 1, &(latitude_match), &latitude_length);
  pcre2_substring_get_bynumber(match_data, 2, &(longitude_match), &longitude_length);
  char* end = {0};
  assert(latitude_length <= 10);
  assert(longitude_length <= 10);
  // Converting these strings to actual doubles so we can set precision and
  // truncate zeros
  double latitude = strtod((const char*)latitude_match, &end);
  double longitude = strtod((const char*)longitude_match, &end);

  sprintf(points_url, "%s%.4g,%.4g", "https://api.weather.gov/points/", latitude,
          longitude);

	pcre2_match_data_free(match_data);
	pcre2_code_free(regex_pcre2);

  return true;
}
