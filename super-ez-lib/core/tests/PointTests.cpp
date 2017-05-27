#define BOOST_TEST_MODULE POINT
#include <boost/test/unit_test.hpp>
#include "../include/Point.hpp"

BOOST_AUTO_TEST_CASE(constructor)
{
  Point p1, p2(10, 20), p3(p2);
  BOOST_REQUIRE_EQUAL(p1.x(), 0);
  BOOST_REQUIRE_EQUAL(p1.y(), 0);
  BOOST_REQUIRE_EQUAL(p2.x(), 10);
  BOOST_REQUIRE_EQUAL(p2.y(), 20);
  BOOST_REQUIRE_EQUAL(p3.x(), 10);
  BOOST_REQUIRE_EQUAL(p3.y(), 20);
}

BOOST_AUTO_TEST_CASE(setter)
{
  Point p;

  p.setX(10);
  BOOST_REQUIRE_EQUAL(p.x(), 10);
  BOOST_REQUIRE_EQUAL(p.y(), 0);

  p.setX(0);
  p.setY(20);
  BOOST_REQUIRE_EQUAL(p.x(), 0);
  BOOST_REQUIRE_EQUAL(p.y(), 20);

  p.set(30, 30);
  BOOST_REQUIRE_EQUAL(p.x(), 30);
  BOOST_REQUIRE_EQUAL(p.y(), 30);
}

BOOST_AUTO_TEST_CASE(group)
{
  Point p1(10, 10), p2(20, 20), p3(30, 30);

  p2.join(p1);
  p3.join(p1);
  BOOST_REQUIRE_EQUAL(p1, Point(10, 10));
  BOOST_REQUIRE_EQUAL(p1, p2);
  BOOST_REQUIRE_EQUAL(p1, p3);

  p1.set(40, 40);
  BOOST_REQUIRE_EQUAL(p1, Point(40, 40));
  BOOST_REQUIRE_EQUAL(p1, p2);
  BOOST_REQUIRE_EQUAL(p1, p3);

  p2.set(50, 50);
  BOOST_REQUIRE_EQUAL(p1, Point(50, 50));
  BOOST_REQUIRE_EQUAL(p1, p2);
  BOOST_REQUIRE_EQUAL(p1, p3);

  p3.set(60, 60);
  BOOST_REQUIRE_EQUAL(p1, Point(60, 60));
  BOOST_REQUIRE_EQUAL(p1, p2);
  BOOST_REQUIRE_EQUAL(p1, p3);

  p2.beAlone();
  p2.set(10, 10);
  p1.set(0, 0);
  BOOST_REQUIRE_EQUAL(p1, Point(0, 0));
  BOOST_REQUIRE_EQUAL(p2, Point(10, 10));
  BOOST_REQUIRE_EQUAL(p1, p3);

  p3.beAlone();
  p1.set(-10, -10);
  p3.set(30, 30);
  BOOST_REQUIRE_EQUAL(p1, Point(-10, -10));
  BOOST_REQUIRE_EQUAL(p2, Point(10, 10));
  BOOST_REQUIRE_EQUAL(p3, Point(30, 30));

  p2.join(p1);
  p3.join(p2);
  p1.set(0, 0);
  BOOST_REQUIRE_EQUAL(p1, Point(0, 0));
  BOOST_REQUIRE_EQUAL(p2, p1);
  BOOST_REQUIRE_EQUAL(p3, p1);

  p3.set(30, 30);
  BOOST_REQUIRE_EQUAL(p1, Point(30, 30));
  BOOST_REQUIRE_EQUAL(p2, p1);
  BOOST_REQUIRE_EQUAL(p3, p1);

  p1.beAlone();
  p2.beAlone();
  p3.beAlone();
  p1.set(0, 0);
  p2.set(1, 1);
  p3.set(2, 2);
  BOOST_REQUIRE_EQUAL(p1, Point(0, 0));
  BOOST_REQUIRE_EQUAL(p2, Point(1, 1));
  BOOST_REQUIRE_EQUAL(p3, Point(2, 2));
}