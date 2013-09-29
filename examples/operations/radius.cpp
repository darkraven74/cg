#include <QColor>
#include <QApplication>
#include <vector>
#include <boost/optional.hpp>
#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"
#include <cg/primitives/circle.h>
#include <cg/primitives/point.h>
#include <cg/operations/radius.h>
using cg::point_2;
using cg::point_2f;

struct radius : cg::visualization::viewer_adapter
{
   radius()
   {
      is_finished_ = false;
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::red);
      for (int i = 0; i < (int)points_.size(); i++)
      {
         drawer.draw_point(points_[i], 3);
      }
      drawer.set_color(Qt::green);
      if (is_finished_)
      {
         cg::circle_2 ans = cg::radius(points_.begin(), points_.end());
         std::vector<cg::point_2> circle_pts = ans.points();
         drawer.draw_point(ans.center, 3);
         for (int i = 0; i < circle_pts.size(); i++)
         {
            drawer.draw_point(circle_pts[i], 2);
         }
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near vertex to move it"
                        << cg::visualization::endl
                        << "press r to restart"
                        << cg::visualization::endl
                        << "press f when finish"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
      if (!is_finished_)
       {
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
      if (key == Qt::Key_F)
      {
         is_finished_ = true;
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

      cur_p_ = p;
      if (cur_v_)
      {
         points_[*cur_v_] = p;
      }

      return true;
   }

private:


   boost::optional<int> cur_v_;
   cg::point_2 cur_p_;
   bool is_finished_;
   std::vector<cg::point_2> points_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   radius viewer;
   cg::visualization::run_viewer(&viewer, "radius");
}
