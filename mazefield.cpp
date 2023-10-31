#include "mazefield.h"

mazefield::mazefield(QWidget *parent)
    : QWidget{parent}
{

}

void mazefield::SetModel(Model* model) {
    model_ = model;
}

void mazefield::paintEvent(QPaintEvent *event)
{
QPainter painter(this);
QPen pen = (QApplication::palette().text().color());  // creates a default pen
pen.setWidth(2);
painter.setPen(pen);

if (paint) {
painter.drawLine(0, 1, 499, 1);
painter.drawLine(1, 0, 1, 499);

double cellWidth_ = 500.0 / model_->GetCols();
double cellHeight_ = 500.0 / model_->GetRows();

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
} else {
    painter.drawText(QPoint(200, 250), "Let there be mazes!");
}
}

