#include <gtest/gtest.h>

#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>

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
