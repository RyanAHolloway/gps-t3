#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"
#include <stdexcept>

using namespace GPS;


BOOST_AUTO_TEST_SUITE( maxLatitude )

/* Route.maxLatitude() should return the maximum latitude of the route, which is taken from the content of
 * the <rte pt> element (within the <rte> element) in the GPX data that the Route was
 * constructed from.
 *
 * The main testing consideration is whether a latitude value is present or absent in the GPX data.
 *
 * We start by testing a typical input: a route containing a single position with just a latitude value
 *
 * We next test for absent values.  There are two possibilities: the <rte pt> element may be
 * missing, or the content of the element may be entirely blank space.
 *
 * Finally, we test that blank space before and after the name is dropped, including
 * the corner case where there is blank space at both the front and the back of the
 * same name.  We also test that blank space within the name is not dropped.
 */

const bool isFileName = true; // All GPX data in this suite is loaded from files.
const metres horizontalGridUnit = 100000;

//DUMMY FUNCTION FOR maxLatitude
double poleLatitude = 90.0000;
double dummyMaxLatitude(double value)
{
	degrees maxLat = value;
		if (maxLat > poleLatitude){
			throw std::invalid_argument("Latitude values must not exceed " + std::to_string(poleLatitude) + " degrees.");
		}
		else{

		}

    return maxLat;
}

//Dummy Function to display awareness of what would happen if string is passed
std::string dummyFunction(std::string value)
{
	std::string maxLat = value;

	throw std::invalid_argument("std::string is not a valid latitude data type");

    return maxLat;
}


//Check a string value throws an invalid argument
BOOST_AUTO_TEST_CASE( stringLatitudeValue )
{
	BOOST_CHECK_THROW( dummyFunction("AAA"), std::invalid_argument);
}

//Check a invalid latitude value throws an invalid argument
BOOST_AUTO_TEST_CASE( invalidLatitudeValue )
{
	BOOST_CHECK_THROW( dummyMaxLatitude(91.0000), std::invalid_argument);
}

// Check that a negative latitude value is accepted
BOOST_AUTO_TEST_CASE( acceptNegativeLatitudePresent )
{
	//Arrange
	const std::string gpxData = "<gpx><rte><name>MyRoute</name><rtept lat=\"-1.00000\" lon=\"0\"></rtept></rte></gpx>";

	//Act
	Route route = Route(gpxData, false);

	//Assert
	BOOST_CHECK_EQUAL( route.maxLatitude(), -1.00000);
}

// Check that a positive latitude value is accepted
BOOST_AUTO_TEST_CASE( acceptPositiveLatitudePresent )
{
	const std::string gpxData = "<gpx><rte><name>MyRoute</name><rtept lat=\"1\" lon=\"0\"></rtept></rte></gpx>";
	 Route route = Route(gpxData, false);

	 BOOST_CHECK_EQUAL( route.maxLatitude() , 1 );
}

//Check that a negative max latitude value is accepted in a route log
BOOST_AUTO_TEST_CASE( check_negative_max_latitude_from_log )
{
	 Route route = Route(LogFiles::GPXRoutesDir + "GPXTTestLog1.gpx", isFileName);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), -0.89 );
}

//Check that a positive max latitude value is accepted in a route log
BOOST_AUTO_TEST_CASE( positiveMaxLatitudeFromLog )
{
	 Route route = Route(LogFiles::GPXRoutesDir + "GPXTestLog2.gpx", isFileName);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), 51.991295693805299);
}

//Check the max latitude value in a route log where all route points when granularity is taken into consideration.
BOOST_AUTO_TEST_CASE( granularityAccountedFor )
{
	 const metres granularity = horizontalGridUnit;
	 Route route = Route(LogFiles::GPXRoutesDir + "GPXTestLog3.gpx", isFileName, granularity);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), 57.129264346442604);
}

//Check that a max latitude value in a route log when the granularity is increased 10 times over.
BOOST_AUTO_TEST_CASE( positionsCloseMaxLatitudeFromLog )
{
	 const metres granularity = horizontalGridUnit * 10; //Granularity is set to 10 times the size
	 Route route = Route(LogFiles::GPXRoutesDir + "GPXTestLog3.gpx", isFileName, granularity);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), 53.112691358937397 );
	 //Actual max is 57.129264346442604 but due to granularity change the max is 53.112691358937397 as the higher values are discarded due to the granularity
}

//Check that a max latitude value in a route log when the granularity is increased 10 times over.
BOOST_AUTO_TEST_CASE( spacedPositionsMaxLatitudeFromLog )
{
	 const metres granularity = horizontalGridUnit / 10; //Granularity is set to 10 times the size
	 Route route = Route(LogFiles::GPXRoutesDir + "GPXTestLog3.gpx", isFileName, granularity);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), 57.129264346442604 );
	 //Actual max is 57.129264346442604 but due to granularity change the max is 53.112691358937397 as the higher values are discarded due to the granularity
}


BOOST_AUTO_TEST_SUITE_END()
