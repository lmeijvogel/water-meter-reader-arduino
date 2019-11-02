#include "catch.hpp"

#include "../Filter.cpp"

#define USAGE true
#define NO_USAGE false

TEST_CASE("Starts with no signal", "[Filter]") {
  Filter filter;

  REQUIRE(filter.activated(true, false) == NO_USAGE); // below

  REQUIRE(filter.activated(false, false) == NO_USAGE); // between

  REQUIRE(filter.activated(false, true) == USAGE); // above

  // low state not reached yet, so false
  REQUIRE(filter.activated(false, true) == NO_USAGE); // above

  REQUIRE(filter.activated(false, false) == NO_USAGE); // not yet low

  REQUIRE(filter.activated(false, true) == NO_USAGE); // above again

  REQUIRE(filter.activated(false, false) == NO_USAGE); // descending

  REQUIRE(filter.activated(true, false) == NO_USAGE);

  REQUIRE(filter.activated(false, true) == USAGE);

  REQUIRE(filter.activated(false, true) == NO_USAGE);
}
