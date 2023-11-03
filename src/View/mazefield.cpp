#include "mazefield.h"

namespace s21 {

MazeField::MazeField(QWidget *parent) : QWidget{parent} {
  setFocusPolicy(Qt::ClickFocus);
}

void MazeField::SetControl(s21::Controller *c) { controller_ = c; }

void MazeField::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  QPen pen(QApplication::palette().text().color(), 2);
  QPen pen_2(Qt::red, 2);
  painter.setPen(pen);

  painter.drawLine(0, 1, 499, 1);
  painter.drawLine(1, 0, 1, 499);

  cellWidth_ = 500.0 / controller_->GetCols();
  cellHeight_ = 500.0 / controller_->GetRows();

  for (int i = 0; i < controller_->GetRows(); i++) {
    for (int j = 0; j < controller_->GetCols(); j++) {
      int x0 = cellWidth_ * j;
      int y0 = cellHeight_ * i;
      int x1 = cellWidth_ * (j + 1);
      int y1 = cellHeight_ * (i + 1);
      if (controller_->GetVert()(i, j)) {
        if (j + 1 == controller_->GetCols()) {
          x0--;
          x1--;
        }
        painter.drawLine(x1, y0, x1, y1);
      }
      if (controller_->GetHor()(i, j)) {
        if (i + 1 == controller_->GetRows()) {
          y0--;
          y1--;
        }
        if (j + 1 == controller_->GetCols()) {
          x0++;
          x1++;
        }
        painter.drawLine(x0, y1, x1, y1);
      }
    }
  }
  if (left_) {
    painter.setPen(pen_2);
    painter.drawEllipse(begin_, 5, 5);
  }
  if (right_) {
    painter.setPen(pen_2);
    painter.drawEllipse(end_, 5, 5);
  }

  if (!controller_->GetPath().empty()) {
    painter.setPen(pen_2);
    for (unsigned i = 0; i < controller_->GetPath().size() - 1; i++) {
      painter.drawLine(MakePointCoords(controller_->GetPath()[i]),
                       MakePointCoords(controller_->GetPath()[i + 1]));
    }
  }
}

void MazeField::startPoint() {
  i_start_ = begin_.y() / cellHeight_;
  j_start_ = begin_.x() / cellWidth_;
  begin_.setX((int)j_start_ * cellWidth_ + cellWidth_ / 2);
  begin_.setY((int)i_start_ * cellHeight_ + cellHeight_ / 2);
}

void MazeField::endPoint() {
  i_end_ = end_.y() / cellHeight_;
  j_end_ = end_.x() / cellWidth_;
  end_.setX((int)j_end_ * cellWidth_ + cellWidth_ / 2);
  end_.setY((int)i_end_ * cellHeight_ + cellHeight_ / 2);
}

QPoint MazeField::MakePointCoords(std::pair<int, int> pathIndex) {
  int xpos = pathIndex.second * cellWidth_ + cellWidth_ / 2;
  int ypos = pathIndex.first * cellHeight_ + cellHeight_ / 2;
  return QPoint(xpos, ypos);
}

void MazeField::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton && !left_) {
    begin_ = event->pos();
    left_ = true;
    startPoint();
  } else if (event->button() == Qt::LeftButton && !right_) {
    end_ = event->pos();
    right_ = true;
    endPoint();
  } else if (event->button() == Qt::RightButton) {
    left_ = false;
    right_ = false;
    controller_->ClearMap();
  }
  if (left_ && right_) {
    controller_->SolveMaze(i_start_, j_start_, i_end_, j_end_);
  }
  update();
}

void MazeField::ResetFlags() {
  left_ = false;
  right_ = false;
}

}  // namespace s21
