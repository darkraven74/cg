#pragma once

#include <cg/primitives/segment.h>

#include <cg/operations/orientation.h>

namespace cg
{
   template<class Scalar>
   inline bool has_intersection(segment_2t<Scalar> const & a, segment_2t<Scalar> const & b)
   {

      orientation_t ab1, ab2;
      ab1 = orientation(a[0], a[1], b[0]);
      ab2 = orientation(a[0], a[1], b[1]);

      if ((ab1 == ab2) && (ab1 == CG_COLLINEAR))
      {
         return (min(a) <= b[0] && max(a) >= b[0])
            || (min(a) <= b[1] && max(a) >= b[1])
            || (min(b) <= a[0] && max(b) >= a[0])
            || (min(b) <= a[1] && max(b) >= a[1]);
      }

      if (ab1 == ab2)
      {
         return false;
      }

      ab1 = orientation(b[0], b[1], a[0]);
      ab2 = orientation(b[0], b[1], a[1]);

      return (ab1 != ab2);
   }
}
