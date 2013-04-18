#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include "cg/io/point.h"

#include <cg/primitives/triangle.h>
#include <cg/primitives/point.h>

#include <cg/operations/has_intersection/segment_segment.h>


using cg::point_2f;
using cg::point_2;
using cg::segment_2;

struct segment_intersect_segment_viewer : cg::visualization::viewer_adapter
{
   segment_intersect_segment_viewer()
      : seg1_(point_2(0, 0), point_2(0, 100)),
        seg2_(point_2(100, 0), point_2(100, 100))

   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      if (cg::has_intersection(seg1_, seg2_))
      {
         drawer.set_color(Qt::blue);
      }
      drawer.draw_line(seg1_[0], seg1_[1]);
      drawer.draw_line(seg2_[0], seg2_[1]);
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near segment end to move it"
                        << cg::visualization::endl
                        << "if segment is blue then segments are intersect"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
      {
         for (size_t i = 0; i != 2; ++i)
         {
            if ((fabs(p.x - seg1_[i].x) < 15) && (fabs(p.y -seg1_[i].y) < 15))
            {
               id_segmentx_ = &seg1_;
               idx_ = i;
               return true;
            }
         }

         for (size_t i = 0; i != 2; ++i)
         {
            if ((fabs(p.x - seg2_[i].x) < 15) && (fabs(p.y - seg2_[i].y) < 15))
            {
               id_segmentx_ = &seg2_;
               idx_ = i;
               return true;
            }
         }

         return false;
      }

      bool on_release(const point_2f & p)
      {
         id_segmentx_.reset();
         return false;
      }

      bool on_move(const point_2f & p)
      {
         if (!id_segmentx_)
         {
            return true;
         }

         (**id_segmentx_)[*idx_] = p;
         return true;
      }

private:
   cg::segment_2 seg1_, seg2_;
   boost::optional<segment_2*> id_segmentx_;
   boost::optional<size_t> idx_;

};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   segment_intersect_segment_viewer viewer;
   cg::visualization::run_viewer(&viewer, "segment intersect segment");
}

