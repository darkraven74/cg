#pragma once
#include <cg/primitives/circle.h>
#include <vector>
#include <time.h>
namespace cg
{
   circle_2 calc3(point_2 p1, point_2 p2, point_2 p3)
   {
      double ma = (p2.y - p1.y) / (p2.x - p1.x);
      double mb = (p3.y - p2.y) / (p3.x - p2.x);
      double x = (ma * mb * (p1.y - p3.y) + mb * (p1.x + p2.x) - ma * (p2.x + p3.x)) / (2.0 * (mb - ma));
      double y = -1.0 / (ma) * (x - (p1.x + p2.x) / 2.0) + (p1.y + p2.y) / 2.0;
      point_2 center(x, y);
      double radius = center.distance(p1);
      return circle_2(center, radius);
   }

   circle_2 calc2(point_2 p1, point_2 p2)
   {
      double x = (p1.x + p2.x) / 2.0;
      double y = (p1.y + p2.y) / 2.0;
      point_2 center(x, y);
      double radius = center.distance(p1);
      return circle_2(center, radius);
   }

   circle_2 radius_impl(std::vector<point_2> points, int n, std::vector<point_2> border, int b)
   {
      circle_2 ans;

      if (b == 3)
      {
         ans = calc3(border[0], border[1], border[2]);
      }
      else if (n == 1 && b == 0)
      {
         ans = circle_2(points[0], 0);
      }
      else if (n == 0 && b == 2)
      {
         ans = calc2(border[0], border[1]);
      }
      else if (n == 1 && b == 1)
      {
         ans = calc2(border[0], points[0]);
      }
      else
      {
         ans = radius_impl(points, n - 1, border, b);
         if (!ans.contains(points[n - 1]))
         {
            border[b++] = points[n - 1];
            ans = radius_impl(points, n - 1, border, b);
         }
      }
      return ans;
   }

   template <class BidIter>
   circle_2 radius(BidIter p, BidIter q)
   {
      std::vector<point_2> points;
      std::vector<point_2> border(3);
      srand(time(NULL));
      for (BidIter it = p; it != q; it++)
      {
         points.push_back(*it);
      }
      for (int i = 0; i < points.size(); i++)
      {
         int pos = rand() % points.size();
         std::swap(points[i], points[pos]);
      }
      return radius_impl(points, points.size(), border, 0);
   }
}
