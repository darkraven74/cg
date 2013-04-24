#pragma once

#include <boost/range/algorithm/sort.hpp>
#include <algorithm>
#include <cg/operations/orientation.h>
#include "graham.h"

namespace cg
{
   template <class RandIter>
   RandIter andrew_hull(RandIter p, RandIter q)
   {
      if (p == q)
         return p;

      std::iter_swap(p, std::min_element(p, q));
      RandIter t = p;
      t++;
      if (t == q)
         return t;

      std::iter_swap(t, std::max_element(t, q));
      t++;
      if (t == q)
         return t;

      RandIter pmin = p;
      RandIter pmax = p;
      pmax++;

      RandIter i1 = std::partition(t, q, [pmin, pmax] (point_2 const & a)
                              {
                                 return (orientation(*pmin, *pmax, a) != CG_LEFT);
                              }
                     );
      i1--;
      std::iter_swap(pmax, i1);
      std::sort(pmin, i1);
      i1++;
      std::sort(i1, q);
      std::reverse(i1, q);

      return contour_graham_hull(p, q);

   }
}
