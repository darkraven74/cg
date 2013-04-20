#pragma once

#include <boost/range/algorithm/sort.hpp>
#include <algorithm>
#include <cg/operations/orientation.h>

namespace cg
{
   template <class BidIter>
   BidIter contour_andrew_hull(BidIter p, BidIter q)
   {
      if (p == q)
      {
         return p;
      }

      BidIter b = p;
      BidIter pt = p++;

      if (p == q)
      {
         return p;
      }

      BidIter t = p++;

      if (p == q)
      {
         return p;
      }

      for (; p != q; )
      {
         switch (orientation(*pt, *t, *p))
         {
         case CG_LEFT:
            pt = t++;
            std::iter_swap(t, p++);
            break;
         case CG_RIGHT:
            t = pt--;
            break;
         case CG_COLLINEAR:
            std::iter_swap(t, p++);
         }
      }

      while (orientation(*pt, *t, *b) != CG_LEFT)
      {
         t = pt--;
      }

      return ++t;
   }

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

      return contour_andrew_hull(p, q);
   }
}
