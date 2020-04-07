
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define C1 32.0
#define C2 5.0
#define C3 9.0

#define TOTAL_MINUTES 60;

double ftemp(const double raw_temp) {
  double f_temp = raw_temp * C3 / C2 + C1;
  return f_temp;
}

/*
double ctemp(const double raw_temp) {
  double c_temp = (raw_temp - C1) * C2 / C3;
  return c_temp;
}
*/

char* dd_to_dms(const double coordinate) {
  char* dms = malloc(15);
  double degrees = 0.0;
  double minutes = 0.0;

  double x = modf(coordinate, &degrees) * TOTAL_MINUTES;
  double seconds = modf(x, &minutes) * TOTAL_MINUTES;

  sprintf(dms, "%.0f\u00B0 %.0f' %.0f\"", degrees, fabs(minutes),
          fabs(seconds));

  return dms;
}

char lat_dir(double latitude) {
  if (latitude >= 0.0) {
    return 'N';
  } else {
    return 'S';
  }
}

char lng_dir(double longitude) {
  if (longitude >= 0.0) {
    return 'E';
  } else {
    return 'W';
  }
}

int convert_iso8601(const char date_string[restrict static 1], struct tm* date_data) {

	int year;
	int month;
	int day;
	int hours;
	int minutes;
	int seconds;
	int z_hours;
	int z_minutes;

	// 2020-04-05T23:29:22+00:00
	sscanf(date_string, "%d-%d-%dT%d:%d:%d+%d:%d", &year, &month, &day, &hours, &minutes, &seconds, &z_hours, &z_minutes);

	date_data->tm_year = year - 1900;
	date_data->tm_mon = month - 1;
	date_data->tm_mday = day;
	date_data->tm_hour = hours;
	date_data->tm_min = minutes;
	date_data->tm_sec = seconds;

	return 0;
}
