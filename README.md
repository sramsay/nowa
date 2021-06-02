[![Release version](https://img.shields.io/github/v/release/sramsay/nowa?sort=semver)](https://img.shields.io/github/v/release/sramsay/nowa?sort=semver)
[![C/C++ CI](https://github.com/sramsay/nowa/workflows/C/C++%20CI/badge.svg)](https://github.com/sramsay/nowa/workflows/C/C++%20CI/badge.svg)
[![Build Status](https://travis-ci.org/sramsay/nowa.svg?branch=master)](https://travis-ci.org/sramsay/nowa)
[![Build Status](https://circleci.com/gh/sramsay/nowa.svg?style=svg)](https://app.circleci.com/github/sramsay/nowa/pipelines?branch=master)
[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/20749.svg)](https://scan.coverity.com/projects/sramsay-nowa)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/fafa33d720a84726838a83c60be1e183)](https://app.codacy.com/manual/sramsay/nowa?utm_source=github.com&utm_medium=referral&utm_content=sramsay/nowa&utm_campaign=Badge_Grade_Settings)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/sramsay/nowa.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/sramsay/nowa/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/sramsay/nowa.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/sramsay/nowa/context:cpp)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/4487/badge)](https://bestpractices.coreinfrastructure.org/projects/4487)
[![Percentage of issues still open](http://isitmaintained.com/badge/open/sramsay/nowa.svg)](http://isitmaintained.com/project/sramsay/nowa "Percentage of issues still open")
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

nowa
=============

Version 0.18.8

`nowa` is a small, fast command-line application that retrieves weather data from the United States [National Weather Service](https://www.weather.gov/).

**PLEASE NOTE: This is pre-release software.  It may contains bugs, errors, and other misprisions.  Use at your own risk.  [Reports of misbehavior](https://github.com/sramsay/nowa/issues) warmly welcomed.**

Quickstart
----------

[See notes on building and installing `nowa` below]

First, figure out the coordinates of the place for which you'd like to see weather information (there are lots of tools on the web for doing this).  Once you have this, you can ask `nowa` to list nearby weather stations:

	$ nowa --list-stations 65.846004,-150.725719

	Available Weather Stations for 65.846,-150.725719
	ID    Location
	----  --------
	PATA: Tanana, Calhoun Memorial Airport
	PABT: Bettles, Bettles Airport
	PAIM: Utopia Creek, Indian Mountain LRRS Airport
	PANN: Nenana Municipal Airport
	PAFA: Fairbanks, Fairbanks International Airport
	PAMH: Minchumina, Minchumina Airport
	PAIN: McKinley Park, McKinley National Park Airport
	PFYU: Fort Yukon, Fort Yukon Airport
	[...]

Now, that's the middle of the [Yukon-Koyukuk Census Area](https://en.wikipedia.org/wiki/Yukon%E2%80%93Koyukuk_Census_Area%2C_Alaska) in Alaska&mdash;one of the least populated places in the country.  Nonetheless, there are over a hundred stations in the region.

Let's look at the [Elfin Cove Seaplane Base](https://www.flyalaskaseaplanes.com/destinations/Elfin-Cove/).  We can use its station id (`PAEL`) to ask what products the NWS API offers:

	$ nowa --list-products -i PAEL

	Forecast Office Products Available for PAEL:

	Code  Description
	----  -----------
	AFD   Area Forecast Discussion
	CAP   Common Alerting Protocol
	CLM   Climatological Report (Monthly)
	CWF   Coastal Waters Forecast
	FWF   Routine Fire Wx Fcst (With/Without 6-10 Day Outlook)
	HML   AHPS XML
	NOW   Short Term Forecast
	OFF   Offshore Forecast
	PFM   Point Forecast Matrices
	RER   Record Report
	RR3   Hydro-Met Data Report Part 3
	RRS   HADS Data
	[...]

(Note the -i/--station_id  switch.  That's required for a lot of operations with `nowa`)

That station has lots of data products, including an Offshore Waters Forecast (OFF).  So let's grab that:

	$ nowa --product OFF -i PAEL

	Offshore Forecast
	000
	FZAK67 PAJK 021145
	OFFAJK

	Offshore Waters Forecast
	National Weather Service Juneau AK
	345 AM AKDT Wed Jun 2 2021

	Offshore waters forecast for Gulf of Alaska east of 144W

	Wind forecasts reflect the predominant speed and direction
	expected. Sea forecasts represent the average of the highest
	one-third of the combined windwave and swell height.
	[...]

Usage
-----

`nowa` is capable of displaying any data product made available through the [NWS API](https://www.weather.gov/documentation/services-web-api).  If you know the id of a station in a particular area, know the data product you are interested in displaying, and that data product is available at that station, `nowa` can display it.  And all of this information (save the lat/long of the location you're interested in) can be determined using `nowa` itself.

But `nowa` also provides a number of convenience options for commonly requested (and mostly universal) information, including current conditions, 7-day forecast, active alerts, and scientific forecast discussions.  So if you'd simply like to see the current conditions in my hometown (Lincoln, NE):

	$ nowa -c -i KLNK

For the seven-day forecast:

	$ nowa -f -i KLNK

To see if there are any active alerts:

	$ nowa -a -i KLNK

And to completely geek out:

	$ nowa -d -i KLNK

Once you know what products are available at a station, it's easy to set up aliases for particular products like the hazardous weather outlook (HWO), air quality report (AQI), yesterday's precipitation totals (CLI), and so forth.

Building and Installing `nowa`
------------------------------

`nowa` is written in C, and so requires a C compiler (it takes advantage of some C99 features, and so probably won't get along well with very old compilers).  Its only external dependencies are [libcurl](https://curl.se/libcurl/) and [pcre2](https://www.pcre.org/).  These are very common libraries on UNIX-like systems, and are easily installed through systems like [Homebrew](https://brew.sh/) (for MacOS) and the package managers of the various Linux distructions.  In fact, chances are good that they are already installed in your environment.  Assuming you have downloaded the latest release, you should be able to run:

	$ ./configure
	$ make
	$ sudo make install

License(s)
----------

`nowa` is written and maintained by Stephen Ramsay (sramsay{at}protonmail{dot}com).

This program is free software: you can redistribute it and/or modify it under the terms of the [GNU General Public License](https://www.gnu.org/licenses/gpl-3.0.html) as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

`nowa` is distributed with Dave Gamble's (amazing) [cJSON library](https://github.com/DaveGamble/cJSON), and usage of `nowa` implies acceptance of its [MIT License](https://opensource.org/licenses/MIT), a copy of which is in the src/third_party directory of the `nowa` distribution.

NOAA/NWS data is in the public domain.  However users of NOAA/NWS data should be familiar with the terms and conditions set forth in their [disclaimer](https://www.weather.gov/disclaimer).

`nowa` is neither endorsed by, nor in any way affiliated with, either the [National Oceanic and Atmospheric Administration](https://www.noaa.gov/) or the [National Weather Service](https://www.weather.gov/).

Last Modified: Wed Jun 02 16:52:08 CDT 2021
