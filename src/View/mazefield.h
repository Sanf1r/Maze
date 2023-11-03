#ifndef MAZEFIELD_H
#define MAZEFIELD_H

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
  s21::Controller *controller_;
  QPoint begin_, end_;
  bool left_ = false, right_ = false;
  double cellWidth_ = 0.0;
  double cellHeight_ = 0.0;
  double i_start_, j_start_, i_end_, j_end_;

  QPoint MakePointCoords(std::pair<int, int> pathIndex);
  void startPoint();
  void endPoint();
};

}  // namespace s21

#endif  // MAZEFIELD_H
