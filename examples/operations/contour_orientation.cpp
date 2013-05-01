
#include <QColor>
#include <QApplication>
#include <vector>
#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/primitives/point.h>
#include <cg/primitives/contour.h>
#include <cg/operations/orientation.h>

using cg::point_2;
using cg::point_2f;

struct contour_orientation2_viewer : cg::visualization::viewer_adapter
{
   contour_orientation2_viewer()
   {
      is_finished_ = false;
      points_.resize(0);
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);

      if (!is_finished_)
      {
         for (int i = 0; i < (int)points_.size() - 1; i++)
         {
            drawer.draw_line(points_[i], points_[i + 1]);
         }
         return;
      }

      cg::contour_2 c(points_);
      cg::counterclockwise(c) ? drawer.set_color(Qt::green) : drawer.set_color(Qt::red);

      for (int i = 0; i < (int)points_.size() - 1; i++)
      {
         drawer.draw_line(points_[i], points_[i + 1]);
      }
      drawer.draw_line(points_[0], points_.back());


   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near vertex to move it"
                        << cg::visualization::endl
                        << "press r to restart"
                        << cg::visualization::endl
                        << "if contour is green then it is ccw contour"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
      if (!is_finished_)
       {
          if (points_.size() > 1)
          {
             if (fabs(points_[0].x - p.x) < 15 && fabs(points_[0].y - p.y) < 15)
             {
                is_finished_ = true;
                return true;
             }
          }

          points_.push_back(p);
          return true;
       }

       for (size_t i = 0; i < points_.size(); i++)
       {
          if (fabs(points_[i].x - p.x) < 15 && fabs(points_[i].y - p.y) < 15)
          {
             cur_v_ = i;
             return true;
          }
       }

       return true;
   }

   bool on_release(const point_2f & p)
   {
      if (!is_finished_)
      {
         return true;
      }

     cur_v_.reset();

     return true;
   }

   bool on_key(int key) {
      if (key == Qt::Key_R)
      {
         is_finished_ = false;
         points_.clear();
         cur_v_.reset();
         return true;
      }
      return false;
   }

   bool on_move(const point_2f & p)
   {
      if (!is_finished_)
      {
         return true;
      }

      if (cur_v_)
      {
         points_[*cur_v_] = p;
      }

      return true;
   }

private:


   boost::optional<int> cur_v_;
   bool is_finished_;
   std::vector<cg::point_2> points_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   contour_orientation2_viewer viewer;
   cg::visualization::run_viewer(&viewer, "contour_orientation2");
}
