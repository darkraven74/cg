#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>
#include <cg/primitives/range.h>
#include <cg/primitives/contour.h>
#include <cg/operations/contains/segment_point.h>
#include <cg/operations/orientation.h>

namespace cg
{
   // c is convex contour ccw orientation
   inline bool convex_contains(contour_2 const & c, point_2 const & q)
   {
      switch (c.vertices_num())
      {
      case 0: return false;
      case 1: return c[0] == q;
      case 2: return contains(segment_2(c[0], c[1]), q);
      }

      if (cg::orientation(c[0], c[1], q) == CG_RIGHT)
      {
         return false;
      }

      contour_2::const_iterator it = std::lower_bound(c.begin() + 2, c.end(), q,
                       [&c] (point_2 const& a, point_2 const& b)
                              {
                                                      return orientation(c[0], a, b) == CG_LEFT;
                              }
                                                     );
   if (it == c.end())
   {
      return false;
   }

   return (orientation(*(it - 1), *it, q) != CG_RIGHT);

   }

   // c is ordinary contour
   inline bool contains(contour_2 const & c, point_2 const & q)
   {
      if (c.vertices_num() <= 3)
      {
         return convex_contains(c, q);
      }

      int ans = 0;
      contour_2::circulator_t v1 = c.circulator();
      contour_2::circulator_t v2 = v1;
      v2++;

      for (size_t i = 0; i < c.vertices_num(); i++, v1++, v2++)
      {
         point_2 p1 = *v1;
         point_2 p2 = *v2;
         if (p1.y > p2.y)
         {
            std::swap(p1, p2);
         }
         orientation_t orient = orientation(p1, p2, q);
         if ((orient == CG_COLLINEAR) && (std::min(p1, p2) <= q) && (q <= std::max(p1, p2)))
         {
            return true;
         }
         if ((p2.y <= q.y) || (p1.y > q.y))
         {
            continue;
         }
         if (orient == CG_LEFT)
         {
            ans++;
         }
      }
      return (ans % 2);
   }
}
