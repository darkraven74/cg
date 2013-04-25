#include <gtest/gtest.h>
#include <boost/assign/list_of.hpp>
#include <cg/operations/orientation.h>
#include "cg/convex_hull/graham.h"
#include <misc/random_utils.h>

#include "random_utils.h"

using namespace util;

TEST(orientation, uniform_line)
{
   uniform_random_real<double, std::mt19937> distr(-(1LL << 53), (1LL << 53));

   std::vector<cg::point_2> pts = uniform_points(100);
   for (size_t l = 0, ln = 1; ln < pts.size(); l = ln++)
   {
      cg::point_2 a = pts[l];
      cg::point_2 b = pts[ln];

      for (size_t k = 0; k != 1000; ++k)
      {
         double t = distr();
         cg::point_2 c = a + t * (b - a);
         EXPECT_EQ(cg::orientation(a, b, c), *cg::orientation_r()(a, b, c));
      }
   }
}

TEST(orientation, counterclockwise)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0));

   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(pts)));
}

TEST(orientation, counterclockwise2)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(1, 0));

   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(pts)));
}

TEST(orientation, counterclockwise3)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(2, 2));



   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(pts)));
}

TEST(orientation, counterclockwise4)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(5, 5))
                                                    (point_2(0, 5));

   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(pts)));
}

TEST(orientation, counterclockwise5)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(5, 5))
                                                    (point_2(4, 5))
                                                    (point_2(0, 5));

   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(pts)));
}

TEST(orientation, counterclockwise6)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(-1, 0))
                                                    (point_2(1, 1))
                                                    (point_2(0, 5));

   EXPECT_FALSE(cg::counterclockwise(cg::contour_2(pts)));
}

TEST(orientation, counterclockwise7)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(-5, 5))
                                                    (point_2(5, 5));

   EXPECT_FALSE(cg::counterclockwise(cg::contour_2(pts)));
}

TEST(orientation, counterclockwise_uniform)
{
   using cg::point_2;

   std::vector<point_2> pts = uniform_points(100);
   std::vector<point_2>::iterator it = cg::graham_hull(pts.begin(), pts.end());
   pts.resize(std::distance(pts.begin(), it));
   EXPECT_TRUE(cg::counterclockwise(cg::contour_2(pts)));
}

