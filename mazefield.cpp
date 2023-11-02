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
    if (left) {
        painter.setPen(pen_2);
        painter.drawEllipse(begin_, 5, 5);
    }
    if (right) {
        painter.setPen(pen_2);
        painter.drawEllipse(end_, 5, 5);
    }


    if (!model_->GetPath().empty()) {
        painter.setPen(pen_2);
    for (unsigned i = 0; i < model_->GetPath().size() - 1; i++) {
        painter.drawLine(axisToPos(model_->GetPath()[i]), axisToPos(model_->GetPath()[i + 1]));
    }
    }
}

void mazefield::startPoint() {
    i_start_ = begin_.y() / cellHeight_;
    j_start_ = begin_.x() / cellWidth_;
    begin_.setX((int)j_start_ * cellWidth_ + cellWidth_ / 2);
    begin_.setY((int)i_start_ * cellHeight_ + cellHeight_ / 2);
}

void mazefield::endPoint() {
    i_end_ = end_.y() / cellHeight_;
    j_end_ = end_.x() / cellWidth_;
    end_.setX((int)j_end_ * cellWidth_ + cellWidth_ / 2);
    end_.setY((int)i_end_ * cellHeight_ + cellHeight_ / 2);
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
            startPoint();
        } else if (event->button() == Qt::LeftButton && !right) {
            end_ = event->pos();
            right = true;
            endPoint();
        } else if (event->button() == Qt::RightButton) {
            left = false;
            right = false;
            model_->clearMap();
        }
        if (left && right) {
            model_->mapOut(i_start_, j_start_, i_end_, j_end_);

        }
        update();
}

double mazefield::j_end() const
{
    return j_end_;
}

void mazefield::resetFlags()
{
left = false;
right = false;
}

double mazefield::i_end() const
{
    return i_end_;
}

double mazefield::i_start() const
{
    return i_start_;
}

double mazefield::j_start() const
{
    return j_start_;
}



//void mazefield::keyPressEvent(QKeyEvent* event) {
//    qDebug() << event->key();
//}

