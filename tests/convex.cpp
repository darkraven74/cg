
#include <gtest/gtest.h>
#include <boost/assign/list_of.hpp>
#include <cg/operations/convex.h>
#include <cg/convex_hull/graham.h>
#include <misc/random_utils.h>

#include "random_utils.h"

using namespace util;


TEST(convex, 1)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0));

   EXPECT_TRUE(cg::convex(cg::contour_2(pts)));
}

TEST(convex, 2)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(1, 0));

   EXPECT_TRUE(cg::convex(cg::contour_2(pts)));
}

TEST(convex, 3)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(2, 2));



   EXPECT_TRUE(cg::convex(cg::contour_2(pts)));
}

TEST(convex, 4)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(5, 5))
                                                    (point_2(0, 5));

   EXPECT_TRUE(cg::convex(cg::contour_2(pts)));
}

TEST(convex, 5)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(5, 5))
                                                    (point_2(4, 5))
                                                    (point_2(0, 5));

   EXPECT_TRUE(cg::convex(cg::contour_2(pts)));
}

TEST(convex, 6)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(4, 11))
                                                    (point_2(5, 10));

   EXPECT_FALSE(cg::convex(cg::contour_2(pts)));
}

TEST(convex, 7)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(7, 10))
                                                    (point_2(4, 2))
                                                    (point_2(3, 20));

   EXPECT_FALSE(cg::convex(cg::contour_2(pts)));
}

TEST(convex, uniform)
{
   using cg::point_2;

   std::vector<point_2> pts = uniform_points(100);
   std::vector<point_2>::iterator it = cg::graham_hull(pts.begin(), pts.end());
   pts.resize(std::distance(pts.begin(), it));
   EXPECT_TRUE(cg::convex(cg::contour_2(pts)));
}

