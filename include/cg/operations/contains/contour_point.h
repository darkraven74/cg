#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>
#include <cg/primitives/range.h>
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
   inline bool contains(contour_2 const & c, point_2 const & q);
}
