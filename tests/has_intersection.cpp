#include <gtest/gtest.h>

#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/has_intersection/triangle_segment.h>
#include <cg/operations/has_intersection/rectangle_segment.h>

TEST(has_intersection, segment_segment0)
{
   using cg::point_2;
   using cg::segment_2;


   segment_2 s[] =
   {
      segment_2(point_2(0, 0), point_2(2, 2)),
      segment_2(point_2(1, 0), point_2(0, 1)),
      segment_2(point_2(0, 0), point_2(2, 0)),
      segment_2(point_2(0, 0), point_2(2, -1))
   };

   EXPECT_TRUE(cg::has_intersection(s[0], s[1]));
   EXPECT_TRUE(cg::has_intersection(s[1], s[2]));
   EXPECT_TRUE(cg::has_intersection(s[0], s[2]));

   EXPECT_FALSE(cg::has_intersection(s[1], s[3]));

   segment_2 a(point_2(1.0, 0.0), point_2(4.0, 0.0));
   EXPECT_TRUE(cg::has_intersection(a, segment_2(point_2(2.0, -2.0), point_2(2.0, 2.0))));
   EXPECT_TRUE(cg::has_intersection(a, segment_2(point_2(2.0, 0.0), point_2(2.0, 2.0))));
   EXPECT_FALSE(cg::has_intersection(a, segment_2(point_2(1.0, 2.0), point_2(2.0, 2.0))));

   point_2 a1(0.5, 0), a2(0.5, 0), a3(0, 0), a4(1, 0);
   segment_2 se1(a1, a2), se2(a3, a4);
   EXPECT_TRUE(cg::has_intersection(se1, se2));
}

TEST(has_intersection, segment_segment1)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(10, 10), point_2t<double>(10, -10));
    EXPECT_FALSE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment2)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(3, 10), point_2t<double>(3, -10));
    EXPECT_TRUE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment3)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(3, 3), point_2t<double>(1, 1));
    segment_2t<double> s2(point_2t<double>(5, 5), point_2t<double>(4, 4));
    EXPECT_FALSE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment4)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(3, 3), point_2t<double>(1, 1));
    segment_2t<double> s2(point_2t<double>(2, 2), point_2t<double>(4, 4));
    EXPECT_TRUE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment5)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(5, 5));
    segment_2t<double> s2(point_2t<double>(4, 4), point_2t<double>(3, -7));
    EXPECT_TRUE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment6)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(3, 7), point_2t<double>(3, 10));
    EXPECT_FALSE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment7)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(7, 7), point_2t<double>(10, 10));
    EXPECT_FALSE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment8)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(5, 0), point_2t<double>(5, 10));
    EXPECT_TRUE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment9)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(5, 5));
    segment_2t<double> s2(point_2t<double>(7, 7), point_2t<double>(7, 7));
    EXPECT_FALSE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment10)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(5, 5));
    segment_2t<double> s2(point_2t<double>(4, 4), point_2t<double>(4, 4));
    EXPECT_TRUE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment11)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(1, 1));
    segment_2t<double> s2(point_2t<double>(1, 1), point_2t<double>(1, 1));
    EXPECT_TRUE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, segment_segment12)
{
    using cg::segment_2t;
    using cg::point_2t;
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(3, 3));
    segment_2t<double> s2(point_2t<double>(100, 100), point_2t<double>(100, 1));
    EXPECT_FALSE(cg::has_intersection(s1, s2));
}

TEST(has_intersection, triangle_segment)
{
   using cg::point_2;
   using cg::segment_2;
   using cg::triangle_2;

   triangle_2 t(point_2(0, 0), point_2(1, 1), point_2(2, 0));

   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 0), point_2(-1, -1))));

   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 1), point_2(2, 1))));
   EXPECT_FALSE(cg::has_intersection(t, segment_2(point_2(0, 2), point_2(2, 2))));

   triangle_2 t1(point_2(0.0, 0.0), point_2(2.0, 0.0), point_2(2.0, 2.0));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(0.0, 1.0), point_2(3.0, 1.0))));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(2.0, 1.0), point_2(3.0, 1.0))));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(2.0, 0.0), point_2(3.0, -1.0))));
   EXPECT_TRUE(cg::has_intersection(t1, segment_2(point_2(0.2, 0.1), point_2(1.5, 1.0))));
   EXPECT_FALSE(cg::has_intersection(t1, segment_2(point_2(-1.0, 1.0), point_2(2.0, 3.0))));
}

TEST(has_intersection, rectangle_segment)
{
   using cg::point_2;
   using cg::segment_2;
   using cg::rectangle_2;
   using cg::range;

   rectangle_2 r(range(0.0, 4.0), range(0.0, 4.0));
   EXPECT_FALSE(cg::has_intersection(r, segment_2(point_2(-2.0, -2.0), point_2(-1.0, -1.0))));
   EXPECT_TRUE(cg::has_intersection(r, segment_2(point_2(-1.0, -1.0), point_2(1.0, 1.0))));
   EXPECT_TRUE(cg::has_intersection(r, segment_2(point_2(-2.0, -2.0), point_2(0.0, 0.0))));

   range a(0, 2), b(0, 2);
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(-2, 2), point_2(2, 2))));
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(1, 1), point_2(1, 1.5))));
   EXPECT_FALSE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(0, 3), point_2(3, 3))));
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(-1, -1), point_2(3, 3))));
   EXPECT_TRUE(cg::has_intersection(rectangle_2(a, b), segment_2(point_2(1, -1), point_2(1, 3))));
}
