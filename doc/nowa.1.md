# NAME
nowa - a fast, command-line weather program

# SYNOPSIS
nowa --list-stations [LAT/LONG]  
nowa [OPTION...] -i [STATION_ID]  
nowa --product [PRODUCT_CODE] -i [STATION_ID]  
nowa -j [OPTION...] -i [STATION_ID]  

# DESCRIPTION
nowa is a command-line client that displays data from  U.S. National Weather Service's web API.

Technically, nowa is capable of displaying any data product made available through the NWS API.  If you know the id of the station in a particular area, know the data product you are interested in displaying, and that data product is available at that station, nowa can display it.  What's more, all of this information is discoverable through nowa itself.  For example,

	nowa --list-stations "39.833333,-98.583333"

will list all the stations within Weather Forecast Office area.

	nowa -list-products -i KCNK

will list all the forecast products available for the station located Blosser Municipal Airport in Concordia, Kansas (KCNK).

	nowa --product RVD -i KCNK

will display the Daily River forecasts for that station.

nowa also provides a number of convenience options for commonly requested (and mostly universal) information, including current conditions, 7-day forecast, active alerts, and so forth.  So if you'd simply like to see the current conditions:

	nowa -c -i KLNK

For the seven-day forecast summary:

	nowa -f -i KLNK

Note that the -i [STATION ID] option is frequently required for other options to work.

# OPTIONS
**-c**, **--conditions**
: Output the current conditions

**-f**, **--forecast**
: Output the 7-day forecast

**-a**, **--air-quality**
: Output the current air quality forecast

**-d**, **--discussion**
: Output the scientific forecast discussion

**-x**, **--alerts**
: Output active alerts (if any)

**-z**, **--hazards**
: Output the hazardous weather outlook

**-t**, **--totals**
: Output yesterday's precipitation totals

**-r**, **--storm-report**
: Output the most recent storm report

**-l**, **--list-products**
: Output list of available NWS products (requires the -i switch)

**-s** [LAT/LONG], **--list-stations** [LAT/LONG]
: Output a list of area stations.  Latitude and longitude expressed in decimal format (e.g. 39.833333,-98.583333)

**-p** [CODE], **--product** [CODE]
: Output a particular NWS product (if available)

**-i** [STATION ID], **--station-id**
: Station id.  Note that this option is required for most operations.

**-j**, **--json**
: Print raw JSON

**-h**, **--help**
: Output a usage mesage and exit.

**-V**, **--version**
: Output the version number of nowa and exit.
