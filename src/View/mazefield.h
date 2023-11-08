#ifndef A1_MAZE_SRC_VIEW_MAZEFIELD_H_
#define A1_MAZE_SRC_VIEW_MAZEFIELD_H_

#include <QApplication>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "../Controller/controller.h"

namespace s21 {

class MazeField : public QWidget {
  Q_OBJECT
 public:
  explicit MazeField(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *) override;
  void SetControl(s21::Controller *c);
  void ResetFlags();

 protected:
  void mousePressEvent(QMouseEvent *event) override;

 private:
  Controller *controller_ = nullptr;
  QPoint begin_, end_;
  bool left_ = false, right_ = false;
  double cell_width_ = 0.0;
  double cell_height_ = 0.0;
  double i_start_ = 0, j_start_ = 0, i_end_ = 0, j_end_ = 0;

  QPoint MakePointCoords(std::pair<int, int> path_index);
  void StartPoint();
  void EndPoint();
};

}  // namespace s21

#endif  //  A1_MAZE_SRC_VIEW_MAZEFIELD_H_
