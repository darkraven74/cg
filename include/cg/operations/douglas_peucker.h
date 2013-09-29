#pragma once
#include <cg/primitives/segment.h>
#include <cg/primitives/vector.h>


namespace cg
{
   double dist(point_2 a, point_2 b, point_2 o)
   {
      segment_2 s1(o, a);
      segment_2 s2(o, b);
      segment_2 s12(a, b);
      double l1 = s1.length();
      double l2 = s2.length();
      double l12 = s12.length();
      if (l1 >= sqrt(l2 * l2 + l12 * l12))
      {
         return l2;
      }
      if (l2 >= sqrt(l1 * l1 + l12 * l12))
      {
         return l1;
      }
      vector_2 v12(s12[1].x - s12[0].x, s12[1].y - s12[0].y);
      vector_2 v1(s1[1].x - s1[0].x, s1[1].y - s1[0].y);
      return abs(abs(v12 ^ v1) / (l12));
   }


   template <class BidIter, class OutIter>
   OutIter simplify_impl(BidIter p, BidIter q, double eps, OutIter out)
   {
      point_2 begin = *p;
      point_2 end = *(q - 1);

      BidIter far;
      double far_dist = 0;
      for (BidIter it = p + 1; it != q - 1; it++)
      {
         double d = dist(begin, end, *it);
         if (d > far_dist)
         {
            far_dist = d;
            far = it;
         }
      }
      if (far_dist < eps)
      {
         *out++ = *(q - 1);
         return out;
      }

      out = simplify_impl(p, far + 1, eps, out);
      out = simplify_impl(far, q, eps, out);
      return out;
   }

   template <class BidIter, class OutIter>
   OutIter simplify(BidIter p, BidIter q, double eps, OutIter out)
   {
      *out++ = *p;
      return simplify_impl(p, q, eps, out);
   }
}
