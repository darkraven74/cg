#pragma once

#include <cg/primitives/point.h>
#include <cg/primitives/segment.h>
#include <cg/primitives/range.h>
#include <cg/operations/contains/segment_point.h>
#include <cg/operations/orientation.h>

namespace cg
{
   template<class Scalar>
   bool contains_convex(contour_2t<Scalar> const & c, point_2t<Scalar> const & q)
   {
      if (c.vertices_num() == 0)
      {
         return false;
      }
      if (c.vertices_num() == 1)
      {
         return (c[0] == q);
      }
      if (c.vertices_num() == 2)
      {
         return (contains(segment_2t<Scalar>(c[0], c[1]), q));
      }
      //TODO: ...
   }
}
