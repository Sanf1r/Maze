#include "mazefield.h"

mazefield::mazefield(QWidget *parent)
    : QWidget{parent}
{
    setFocusPolicy(Qt::ClickFocus);
}

void mazefield::SetModel(Model* model) {
    model_ = model;
}

void mazefield::paintEvent(QPaintEvent *event)
{
QPainter painter(this);
QPen pen(QApplication::palette().text().color(),2);
QPen pen_2(Qt::red, 2);
painter.setPen(pen);

painter.drawLine(0, 1, 499, 1);
painter.drawLine(1, 0, 1, 499);

cellWidth_ = 500.0 / model_->GetCols();
cellHeight_ = 500.0 / model_->GetRows();

for (int i = 0; i < model_->GetRows(); i++) {
        for (int j = 0; j < model_->GetCols(); j++) {
            int x0 = cellWidth_ * j;
            int y0 = cellHeight_ * i;
            int x1 = cellWidth_ * (j + 1);
            int y1 = cellHeight_ * (i + 1);
            if (model_->GetVert()[i][j]) {
                if (j + 1 == model_->GetCols()) {
                    x0--;
                    x1--;
                }
                painter.drawLine(x1, y0, x1, y1);
            }
            if (model_->GetHor()[i][j]) {
                if (i + 1 == model_->GetRows()) {
                    y0--;
                    y1--;
                }
                if (j + 1 == model_->GetCols()) {
                    x0++;
                    x1++;
                }
                painter.drawLine(x0, y1, x1, y1);
            }
        }
    }


    if (!model_->GetPath().empty()) {
        painter.setPen(pen_2);
    for (unsigned i = 0; i < model_->GetPath().size() - 1; i++) {
        painter.drawLine(axisToPos(model_->GetPath()[i]), axisToPos(model_->GetPath()[i + 1]));
    }
    }
}

void mazefield::posToAxis() {
    x_start_ = begin_.x() / cellWidth_;
    y_start_ = begin_.y() / cellHeight_;

    x_end_ = end_.x() / cellWidth_;
    y_end_ = end_.y() / cellHeight_;
}

QPoint mazefield::axisToPos(std::pair<int,int> pathIndex) {

        int xpos = pathIndex.second * cellWidth_ + cellWidth_ / 2;
        int ypos = pathIndex.first * cellHeight_ + cellHeight_ / 2;
        return QPoint(xpos, ypos);

}

void mazefield::mousePressEvent(QMouseEvent *event) {

        if (event->button() == Qt::LeftButton && !left) {
            begin_ = event->pos();
            left = true;
            std::cout << "LEFT" << std::endl;
        } else if (event->button() == Qt::RightButton && !right) {
            end_ = event->pos();
            right = true;
            std::cout << "RIGHT" << std::endl;
        }

        update();

}

void mazefield::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        left = false;
        right = false;
        update();
    }
}

//void mazefield::keyPressEvent(QKeyEvent* event) {
//    qDebug() << event->key();
//}

