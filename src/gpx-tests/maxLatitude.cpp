#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
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

// Check the name of a GPX route containing a non-empty <rte pt> element within <rte>.
BOOST_AUTO_TEST_CASE( position_location_present )
{
	 Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
	 BOOST_CHECK_EQUAL( route.maxLatitude(), -0.89982 );
}

BOOST_AUTO_TEST_SUITE_END()
