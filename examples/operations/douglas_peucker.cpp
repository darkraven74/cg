#include <QColor>
#include <QApplication>
#include <vector>
#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/primitives/point.h>
#include <cg/operations/douglas_peucker.h>

using cg::point_2;
using cg::point_2f;

struct douglas_peucker : cg::visualization::viewer_adapter
{
   douglas_peucker()
   {
      is_finished_ = false;
      eps = 1;
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

      drawer.set_color(Qt::red);
      for (int i = 0; i < (int)points_.size(); i++)
      {
         drawer.draw_point(points_[i], 3);
      }

      std::vector<cg::point_2> points_ans;
      cg::simplify(points_.begin(), points_.end(), eps, std::back_inserter(points_ans));

      drawer.set_color(Qt::green);
      for (int i = 0; i < (int)points_ans.size() - 1; i++)
      {
         drawer.draw_line(points_ans[i], points_ans[i + 1]);
         drawer.draw_point(points_ans[i], 3);
      }
      drawer.draw_point(points_ans.back(), 3);


   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near vertex to move it"
                        << cg::visualization::endl
                        << "press r to restart"
                        << cg::visualization::endl
                        << "press f when finish"
                        << cg::visualization::endl
                        << "press i/d to change eps"
                        << cg::visualization::endl
                        << "eps = " << eps
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
         eps = 1;
         points_.clear();
         cur_v_.reset();
         return true;
      }
      if (key == Qt::Key_F)
      {
         is_finished_ = true;
         return true;
      }
      if (key == Qt::Key_I)
      {
         eps += 1;
         return true;
      }
      if (key == Qt::Key_D)
      {
         if (eps > 1)
         {
            eps -= 1;
         }
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
   double eps;
   std::vector<cg::point_2> points_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   douglas_peucker viewer;
   cg::visualization::run_viewer(&viewer, "douglas_peucker");
}
