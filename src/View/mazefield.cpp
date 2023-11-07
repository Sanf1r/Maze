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

  cell_width_ = 500.0 / controller_->GetCols();
  cell_height_ = 500.0 / controller_->GetRows();

  for (int i = 0; i < controller_->GetRows(); i++) {
    for (int j = 0; j < controller_->GetCols(); j++) {
      int x0 = cell_width_ * j;
      int y0 = cell_height_ * i;
      int x1 = cell_width_ * (j + 1);
      int y1 = cell_height_ * (i + 1);
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

void MazeField::StartPoint() {
  i_start_ = begin_.y() / cell_height_;
  j_start_ = begin_.x() / cell_width_;
  begin_.setX((int)j_start_ * cell_width_ + cell_width_ / 2);
  begin_.setY((int)i_start_ * cell_height_ + cell_height_ / 2);
}

void MazeField::EndPoint() {
  i_end_ = end_.y() / cell_height_;
  j_end_ = end_.x() / cell_width_;
  end_.setX((int)j_end_ * cell_width_ + cell_width_ / 2);
  end_.setY((int)i_end_ * cell_height_ + cell_height_ / 2);
}

QPoint MazeField::MakePointCoords(std::pair<int, int> path_index) {
  int xpos = path_index.second * cell_width_ + cell_width_ / 2;
  int ypos = path_index.first * cell_height_ + cell_height_ / 2;
  return QPoint(xpos, ypos);
}

void MazeField::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton && !left_) {
    begin_ = event->pos();
    left_ = true;
    StartPoint();
  } else if (event->button() == Qt::LeftButton && !right_) {
    end_ = event->pos();
    right_ = true;
    EndPoint();
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
