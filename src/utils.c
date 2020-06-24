
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define C1 32.0
#define C2 5.0
#define C3 9.0

#define TOTAL_MINUTES 60;


double ftemp(const double raw_temp) {
  double f_temp = raw_temp * C3 / C2 + C1;
  return f_temp;
}


double ctemp(const double raw_temp) {
  double c_temp = (raw_temp - C1) * C2 / C3;
  return c_temp;
}


char* dd_to_dms(const double coordinate) {
  char* dms = malloc(15 * sizeof(char));
	if (!dms) {
		fprintf(stderr, "Fatal Error: No available memory\n");
		exit(1);
	}
  double degrees = 0.0;
  double minutes = 0.0;

  double x = modf(coordinate, &degrees) * TOTAL_MINUTES;
  double seconds = modf(x, &minutes) * TOTAL_MINUTES;

  sprintf(dms, "%.0f\u00B0 %.0f' %.0f\"", degrees, fabs(minutes),
          fabs(seconds));

  return dms;
}


double m_to_mi(double m) {
	double mi = m / 1609.344;
	return mi;
}


double mps_to_mph(double mps) {
	double mph = mps / 0.44704;
	return mph;
}


double kph_to_mph(double kph) {
	double mph = kph / 1.609344;
	return mph;
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


int convert_iso8601(const char date_string[restrict static 1],
                    struct tm* date_data) {
  int year;
  int month;
  int day;
  int hours;
  int minutes;
  int seconds;
  int z_hours;
  int z_minutes;

  // 2020-04-05T23:29:22+00:00
  sscanf(date_string, "%d-%d-%dT%d:%d:%d+%d:%d", &year, &month, &day, &hours,
         &minutes, &seconds, &z_hours, &z_minutes);

  date_data->tm_year = year - 1900;
  date_data->tm_mon = month - 1;
  date_data->tm_mday = day;
  date_data->tm_hour = hours;
  date_data->tm_min = minutes;
  date_data->tm_sec = seconds;

  return 0;
}


const char* bearing_to_compass_dir(int bearing) {
	char* direction = {0};
	if ((bearing >= 349 && bearing <= 360) || (bearing >= 0 && bearing <= 11)) {
		direction = "N";
	} else if (bearing >= 12 && bearing <= 33) {
		direction = "NNE";
	} else if (bearing >= 34 && bearing <= 56) {
		direction = "NE";
	} else if (bearing >= 57 && bearing <= 78) {
		direction = "ENE";
	} else if (bearing >= 79 && bearing <= 101) {
		direction = "E";
	} else if (bearing >= 102 && bearing <= 123) {
		direction = "ESE";
	} else if (bearing >= 124 && bearing <= 146) {
		direction = "SE";
	} else if (bearing >= 147 && bearing <= 168) {
		direction = "SSE";
	} else if (bearing >= 169 && bearing <= 191) {
		direction = "S";
	} else if (bearing >= 192 && bearing <= 213) {
		direction = "SSW";
	} else if (bearing >= 214 && bearing <= 236) {
		direction = "SW";
	} else if (bearing >= 237 && bearing <= 258) {
		direction = "WSW";
	} else if (bearing >= 259 && bearing <= 281) {
		direction = "W";
	} else if (bearing >= 282 && bearing <= 303) {
		direction = "WNW";
	} else if (bearing >= 304 && bearing <= 326) {
		direction = "NW";	
	} else if (bearing >= 327 && bearing <= 348) {
		direction = "NNW";
	}
	return direction;
}


// Categories from Lin, Tzu Ping.  "Thermal Perception, Adaptation and
// Attendance in a Public Square in Hot and Humid Regions."  *Building and
// Environment*  44.10 (2009): 2017-2026
const char* comfort_scale(double dewpoint) {
	char* comfort = {0};
	if (dewpoint < 50.0) {
		comfort = "dry";
	} else if (dewpoint >= 50.0 && dewpoint < 55.0) {
		comfort = "very comfortable";
	} else if (dewpoint >= 55.0 && dewpoint < 60.0) {
		comfort = "comfortable";
	} else if (dewpoint >= 60.0 && dewpoint < 65.0) {
		comfort = "okay for most";
	} else if (dewpoint >= 65.0 && dewpoint < 70.0) {
		comfort = "somewhat uncomfortable";
	} else if (dewpoint >= 70.0 && dewpoint < 75.0)  {
		comfort = "very humid";
	} else if (dewpoint >= 75.0 && dewpoint < 80.0) {
		comfort = "oppressive";
	} else if (dewpoint >= 80.0) {
		comfort = "dangerously high";
	}

	return comfort;
}


double pa_to_mb(int pascals) {
	double pressure = pascals * .01;

	return pressure;
}

char* latlong_string(double latitude, double longitude) {
	char* lat_long = malloc(25 * sizeof(char));
	if (!lat_long) {
		fprintf(stderr, "Fatal Error: No available memory\n");
		exit(1);
	}

	sprintf(lat_long, "%.4f,%.4f", latitude, longitude);

	return lat_long;
}


