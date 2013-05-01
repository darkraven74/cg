#include <gtest/gtest.h>
#include <boost/assign/list_of.hpp>
#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/contains/contour_point.h>

TEST(contains, triangle_point)
{
   using cg::point_2;

   cg::triangle_2 t(point_2(0, 0), point_2(1, 1), point_2(2, 0));

   for (size_t l = 0; l != 3; ++l)
      EXPECT_TRUE(cg::contains(t, t[l]));

   EXPECT_TRUE(cg::contains(t, point_2(1, 0.5)));

   EXPECT_TRUE(cg::contains(t, point_2(1, 0)));
   EXPECT_TRUE(cg::contains(t, point_2(0.5, 0.5)));
   EXPECT_TRUE(cg::contains(t, point_2(1.5, 0.5)));

   EXPECT_FALSE(cg::contains(t, point_2(0, 1)));
   EXPECT_FALSE(cg::contains(t, point_2(2, 1)));
   EXPECT_FALSE(cg::contains(t, point_2(1, -1)));

   cg::triangle_2 t2(point_2(0, 0), point_2(10, 0), point_2(0, 10));
   EXPECT_TRUE(cg::contains(t2, point_2(0, 0)));
   EXPECT_TRUE(cg::contains(t2, point_2(0, 10)));
   EXPECT_TRUE(cg::contains(t2, point_2(0, 5)));
   EXPECT_TRUE(cg::contains(t2, point_2(5, 0)));
   EXPECT_TRUE(cg::contains(t2, point_2(5, 5)));
   EXPECT_TRUE(cg::contains(t2, point_2(3, 7)));
   EXPECT_TRUE(cg::contains(t2, point_2(2, 2)));
   EXPECT_TRUE(cg::contains(t2, point_2(4, 0.1)));

   EXPECT_FALSE(cg::contains(t2, point_2(-4, -4)));
   EXPECT_FALSE(cg::contains(t2, point_2(0, -0.5)));
   EXPECT_FALSE(cg::contains(t2, point_2(100, 100)));
   EXPECT_FALSE(cg::contains(t2, point_2(11, 0)));
   EXPECT_FALSE(cg::contains(t2, point_2(0, 11)));
   EXPECT_FALSE(cg::contains(t2, point_2(5, 5.2)));
   EXPECT_FALSE(cg::contains(t2, point_2(-0.1, -0.1)));
   EXPECT_FALSE(cg::contains(t2, point_2(10, 10)));
   EXPECT_FALSE(cg::contains(t2, point_2(5, -0.1)));
   EXPECT_FALSE(cg::contains(t2, point_2(10, 10.1)));

}

TEST(contains, segment_point)
{
   using cg::point_2;

   cg::segment_2 s(point_2(0, 0), point_2(2, 2));
   for (size_t l = 0; l != 2; ++l)
      EXPECT_TRUE(cg::contains(s, s[l]));

   EXPECT_TRUE(cg::contains(s, point_2(1, 1)));

   EXPECT_FALSE(cg::contains(s, point_2(-1, -1)));
   EXPECT_FALSE(cg::contains(s, point_2(4, 4)));

   EXPECT_FALSE(cg::contains(s, point_2(1, 0)));
   EXPECT_FALSE(cg::contains(s, point_2(0, 1)));
}

TEST(contains, convex_contour_point)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0));


   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(0, 0)));
   EXPECT_FALSE(cg::convex_contains(cg::contour_2(pts), cg::point_2(0, 5)));
}

TEST(contains, convex_contour_point2)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0));


   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(0, 0)));
   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(3, 0)));
   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(5, 0)));
   EXPECT_FALSE(cg::convex_contains(cg::contour_2(pts), cg::point_2(2, 2)));
   EXPECT_FALSE(cg::convex_contains(cg::contour_2(pts), cg::point_2(3, 3)));
   EXPECT_FALSE(cg::convex_contains(cg::contour_2(pts), cg::point_2(4, 4)));
}

TEST(contains, convex_contour_point3)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(5, 5))
                                                    (point_2(0, 5));

   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(0, 0)));
   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(0, 5)));
   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(2, 2)));
   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(4, 4)));
   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(4, 5)));
   EXPECT_TRUE(cg::convex_contains(cg::contour_2(pts), cg::point_2(0, 2)));
   EXPECT_FALSE(cg::convex_contains(cg::contour_2(pts), cg::point_2(6, 0)));
   EXPECT_FALSE(cg::convex_contains(cg::contour_2(pts), cg::point_2(6, 6)));
   EXPECT_FALSE(cg::convex_contains(cg::contour_2(pts), cg::point_2(10, 0)));
}




TEST(contains, contour_point)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0));


   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 0)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(0, 5)));
}

TEST(contains, contour_point2)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0));


   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 0)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(3, 0)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(5, 0)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(2, 2)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(3, 3)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(4, 4)));
}

TEST(contains, contour_point3)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(5, 0))
                                                    (point_2(5, 5))
                                                    (point_2(0, 5));

   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 0)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 5)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(2, 2)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(4, 4)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(4, 5)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 2)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(6, 0)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(6, 6)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(10, 0)));
}


TEST(contains, contour_point4)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(10, 0))
                                                    (point_2(5, 5))
                                                    (point_2(10, 10))
                                                    (point_2(0, 10));

   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 0)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 5)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 10)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(5, 5)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 7)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(1, 1)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(4, 4)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(6, 1)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(1, 8)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(5, 4)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(6, 9)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(6, 5)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(9, 6)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(11, 0)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(15, 15)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(5, 11)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(-1, -1)));
}

TEST(contains, contour_point5)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(10, 0))
                                                    (point_2(8, 2))
                                                    (point_2(11, 5))
                                                    (point_2(8, 8))
                                                    (point_2(5, 5))
                                                    (point_2(5, 8))
                                                    (point_2(3, 8))
                                                    (point_2(1, 4))
                                                    (point_2(0, 6));

   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(1, 1)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(5, 2)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(10, 5)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(8, 1)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(8, 7)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(4, 7)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(2, 5)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0.5, 4)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(0, 6)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(9, 6)));
   EXPECT_TRUE(cg::contains(cg::contour_2(pts), cg::point_2(3, 3)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(-1, -1)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(100, 100)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(5, 20)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(20, 5)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(10, 2)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(11, 6)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(6, 7)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(2, 7)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(1, 5)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(5, -1)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(6, 8)));
   EXPECT_FALSE(cg::contains(cg::contour_2(pts), cg::point_2(6, 9)));
}
