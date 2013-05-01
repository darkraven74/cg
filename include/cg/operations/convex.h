#pragma once

#include <cg/primitives/contour.h>
#include "orientation.h"

namespace cg
{
   // c is ccw contour
   inline bool convex(contour_2 const & c)
   {

      if (c.vertices_num() < 3)
      {
         return true;
      }

      contour_2::circulator_t v1 = c.circulator();
      contour_2::circulator_t v2 = c.circulator();
      v2++;
      contour_2::circulator_t v3 = v2;
      v3++;
      for (int i = 0; i < c.vertices_num(); i++, v1++, v2++, v3++)
      {
         if (orientation(*v1, *v2, *v3) == CG_RIGHT)
         {
            return false;
         }
      }
      return true;
   }
}
