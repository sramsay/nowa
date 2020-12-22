#include "points_data.h"

#define PCRE2_CODE_UNIT_WIDTH 8
#include <assert.h>
#include <pcre2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

bool construct_points_url(char lat_long[restrict static 1],
                          char* points_url[static 1]);

bool init_points(char lat_long[restrict static 1], struct points_info* points) {
  char* points_url = {0};
  if (!construct_points_url(lat_long, &points_url)) {
    fprintf(stderr, "Error: %s", "Unable to retrieve points data\n");
    return false;
  }

  cJSON* points_json = json_init(points_url);

  // Error code
  cJSON* status_json = cJSON_GetObjectItemCaseSensitive(points_json, "status");
  if (status_json) {
    cJSON* details_json =
        cJSON_GetObjectItemCaseSensitive(points_json, "detail");
    printf("%s\n", details_json->valuestring);
    return false;
  }

  cJSON* properties_json =
      cJSON_GetObjectItemCaseSensitive(points_json, "properties");

  cJSON* cwa_json = cJSON_GetObjectItemCaseSensitive(properties_json, "cwa");
  strcpy(points->cwa, cwa_json->valuestring);

  cJSON* forecast_url_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "forecast");
  size_t forecast_size = strlen(forecast_url_json->valuestring);
  points->forecast_url = malloc(forecast_size + 1);
  if (!points->forecast_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(points_url);
    return false;
  }
  strcpy(points->forecast_url, forecast_url_json->valuestring);

  cJSON* forecast_hourly_url_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "forecastHourly");
  size_t forecast_hourly_size = strlen(forecast_hourly_url_json->valuestring);
  points->forecast_hourly_url = malloc(forecast_hourly_size + 1);
  if (!points->forecast_hourly_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(points_url);
    return false;
  }
  strcpy(points->forecast_hourly_url, forecast_hourly_url_json->valuestring);

  cJSON* forecast_grid_data_url_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "forecastGridData");
  size_t forecast_grid_size = strlen(forecast_grid_data_url_json->valuestring);
  points->forecast_grid_data_url = malloc(forecast_grid_size + 1);
  if (!points->forecast_grid_data_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(points_url);
    return false;
  }
  strcpy(points->forecast_grid_data_url,
         forecast_grid_data_url_json->valuestring);

  cJSON* observation_stations_url_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "observationStations");
  size_t observation_size = strlen(observation_stations_url_json->valuestring);
  points->observation_stations_url = malloc(observation_size + 1);
  if (!points->observation_stations_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(points_url);
    return false;
  }
  strcpy(points->observation_stations_url,
         observation_stations_url_json->valuestring);

  cJSON* forecast_zone_url_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "forecastZone");
  size_t zone_size = strlen(forecast_zone_url_json->valuestring);
  points->forecast_zone_url = malloc(zone_size + 1);
  if (!points->forecast_zone_url) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(points_url);
    return false;
  }
  strcpy(points->forecast_zone_url, forecast_zone_url_json->valuestring);

  cJSON* county_url_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "county");
  if (county_url_json != NULL) {
    size_t county_size = strlen(county_url_json->valuestring);
    points->county_url = malloc(county_size + 1);
    if (!points->county_url) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      free(points_url);
      return false;
    }
    strcpy(points->county_url, county_url_json->valuestring);
  } else {
    points->county_url = NULL;
  }

  cJSON* fire_weather_zone_url_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "fireWeatherZone");
  if (fire_weather_zone_url_json != NULL) {
    size_t fire_size = strlen(fire_weather_zone_url_json->valuestring);
    points->fire_weather_zone_url = malloc(fire_size + 1);
    if (!points->fire_weather_zone_url) {
      fprintf(stderr, "Fatal Error: No available memory\n");
      free(points_url);
      return false;
    }
    strcpy(points->fire_weather_zone_url,
           fire_weather_zone_url_json->valuestring);
  } else {
    points->fire_weather_zone_url = NULL;
  }

  cJSON* radar_station_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "radarStation");
  size_t radar_size = strlen(radar_station_json->valuestring);
  points->radar_station = malloc(radar_size + 1);
  if (!points->radar_station) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    free(points_url);
    return false;
  }
  strcpy(points->radar_station, radar_station_json->valuestring);

  free(points_url);
  cJSON_Delete(points_json);

  return true;
}

bool construct_points_url(char lat_long[restrict static 1],
                          char* points_url[static 1]) {
  // Matches lat/longs of the general form 39.809734,-98.555620
  PCRE2_SPTR pattern = (PCRE2_SPTR) "(-?[0-9]*\\.[0-9]+),(-?[0-9]*\\.[0-9]+)";
  PCRE2_SPTR subject = (PCRE2_SPTR)lat_long;

  int error_num_pcre2 = 0;
  PCRE2_SIZE error_offset_pcre2 = {0};
  pcre2_code* regex_pcre2 =
      pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &error_num_pcre2,
                    &error_offset_pcre2, NULL);

  if (regex_pcre2 == NULL) {
    PCRE2_UCHAR buffer[256];
    pcre2_get_error_message(error_num_pcre2, buffer, sizeof(buffer));
    printf("PCRE2 compilation failed at offset %d: %s\n",
           (int)error_offset_pcre2, buffer);
    exit(1);
  }

  pcre2_match_data* match_data =
      pcre2_match_data_create_from_pattern(regex_pcre2, NULL);

  int return_code_pcre2 = pcre2_match(
      regex_pcre2, subject, strlen((char*)subject), 0, 0, match_data, NULL);

  if (return_code_pcre2 < 0) {
    switch (return_code_pcre2) {
      case PCRE2_ERROR_NOMATCH:
        printf("No match\n");
        break;
      default:
        printf("Matching error %d\n", return_code_pcre2);
        break;
    }
    pcre2_match_data_free(match_data); /* Release memory used for the match */
    pcre2_code_free(regex_pcre2);      /* data and the compiled pattern.    */
    return false;
  }

  PCRE2_UCHAR8* latitude_match = {0};
  PCRE2_UCHAR8* longitude_match = {0};
  size_t latitude_length;
  size_t longitude_length;
  pcre2_substring_get_bynumber(match_data, 1, &(latitude_match),
                               &latitude_length);
  pcre2_substring_get_bynumber(match_data, 2, &(longitude_match),
                               &longitude_length);
  char* end = {0};
  assert(latitude_length <= 11);
  assert(longitude_length <= 11);
  // Converting these strings to actual doubles so we can set precision and
  // truncate zeros
  double latitude = strtod((const char*)latitude_match, &end);
  double longitude = strtod((const char*)longitude_match, &end);

  *points_url = malloc(50);
  sprintf(*points_url, "%s%.4g,%.4g", "https://api.weather.gov/points/",
          latitude, longitude);

  pcre2_match_data_free(match_data);
  pcre2_code_free(regex_pcre2);
  pcre2_substring_free(latitude_match);
  pcre2_substring_free(longitude_match);

  return true;
}

void cleanup_points(struct points_info* points) {
  free(points->forecast_url);
  free(points->forecast_hourly_url);
  free(points->forecast_grid_data_url);
  free(points->observation_stations_url);
  free(points->forecast_zone_url);
  free(points->county_url);
  free(points->fire_weather_zone_url);
  free(points->radar_station);
}
