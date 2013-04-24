#pragma once

#include <boost/range/algorithm/sort.hpp>
#include <algorithm>
#include <cg/operations/orientation.h>
#include "graham.h"

namespace cg
{
   template <class BidIter>
   BidIter andrew_hull(BidIter p, BidIter q)
   {
      if (p == q)
         return p;

      std::iter_swap(p, std::min_element(p, q));
      BidIter t = p;
      t++;
      if (t == q)
         return p;
      std::iter_swap(t, std::max_element(p, q));
      t++;
      BidIter pmin = p;
      BidIter pmax = p;
      pmax++;

      BidIter i1 = std::partition(t, q, [pmin, pmax] (point_2 const & a)
                              {
                                 return (orientation(*pmin, *pmax, a) == CG_RIGHT);
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
