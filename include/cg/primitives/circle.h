#pragma once

#include <cg/primitives/point.h>

namespace cg
{
   template <class Scalar>
   struct circle_2t;

   typedef circle_2t<double> circle_2;

   template <class Scalar>
   struct circle_2t
   {
      circle_2t() {}
      circle_2t(point_2t<Scalar> const & _center, Scalar const & _radius)
         : center(_center), radius(_radius) {}

      bool contains(point_2 p)
      {
         return ((p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y)) <= (radius * radius);
      }

      std::vector<point_2> points()
      {
         std::vector<point_2> ans;
         for (double x = center.x - radius; x <= center.x + radius; x += 0.01)
         {
            double y1 = center.y + sqrt(radius * radius - (x - center.x) * (x - center.x));
            double y2 = center.y - sqrt(radius * radius - (x - center.x) * (x - center.x));
            ans.push_back(point_2(x, y1));
            ans.push_back(point_2(x, y2));
         }
         return ans;
      }

      point_2t<Scalar> center;
      Scalar radius;
   };
}
