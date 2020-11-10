#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <stdexcept>

#include "geometry.h"
#include "xml/element.h"
#include "xml/parser.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( maxLatitude )

/* Route.maxLatitude() should return the maximum latitude of the route, which is taken from the content of
 * the <rte pt> element (within the <re> element) in the GPX data that the Route was
 * constructed from.
 *
 * The main testing consideration is whether a latitude value is present or absent in the GPX data.
 *
 * We start by testing a typical input: a route containing a single position with just a latitude value
 *
 * We next test for absent values.  There are two possibilites: the <rte pt> element may be
 * missing, or the content of the element may be entirely blank space.
 *
 * Finally, we test that blank space before and after the name is dropped, including
 * the corner case where there is blank space at both the front and the back of the
 * same name.  We also test that blank space within the name is not dropped.
 */

const bool isFileName = true; // All GPX data in this suite is loaded from files.
const metres horizontalGridUnit = 100000;
const double percentageAccuracy = 0.0001;

//Check lat value is not over 90
BOOST_AUTO_TEST_CASE( test_injection_latitude_present )
{
	//Arrange
	std::vector<Position> positions;
	Position pos = Position("88","0","0");
	positions.push_back(pos);
	degrees maxLat = positions.front().latitude();

	std::string lat = std::to_string(maxLat);

	const std::string gpxData = "<gpx><rte><name>MyRoute</name><rtept lat=\"" + lat + "\" lon=\"0\"></rtept></rte></gpx>";

	//Act
	Route route = Route(gpxData, false);

	//Assert
	BOOST_CHECK_EQUAL( route.maxLatitude(), 88);
}

// Check that a negative latitude value is accepted
BOOST_AUTO_TEST_CASE( accept_negative_latitude_present )
{
	//Arrange
	const std::string gpxData = "<gpx><rte><name>MyRoute</name><rtept lat=\"-1.00000\" lon=\"0\"></rtept></rte></gpx>";

	//Act
	Route route = Route(gpxData, false);

	//Assert
	BOOST_CHECK_EQUAL( route.maxLatitude(), -1.00000);
}

// Check that a positive latitude value is accepted
BOOST_AUTO_TEST_CASE( accept_positive_latitude_present )
{
	const std::string gpxData = "<gpx><rte><name>MyRoute</name><rtept lat=\"1\" lon=\"0\"></rtept></rte></gpx>";
	 Route route = Route(gpxData, false);

	 BOOST_CHECK_EQUAL( route.maxLatitude() , 1 );
}

//Check that a negative max latitude value is accepted in a route log
BOOST_AUTO_TEST_CASE( check_negative_max_latitude_from_log )
{
	 Route route = Route(LogFiles::GPXRoutesDir + "GPXTTestLog1.gpx", isFileName);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), -0.89982 );
}

//Check that a positive max latitude value is accepted in a route log
BOOST_AUTO_TEST_CASE( check_positive_max_latitude_from_log )
{
	 Route route = Route(LogFiles::GPXRoutesDir + "GPXTestLog2.gpx", isFileName);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), 2.79964 );
}

BOOST_AUTO_TEST_SUITE_END()
