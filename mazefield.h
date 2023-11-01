#ifndef MAZEFIELD_H
#define MAZEFIELD_H

#include <QWidget>
#include <QPainter>
#include <QMainWindow>
#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>

#include "model.h"

class mazefield : public QWidget
{
    Q_OBJECT
public:
    explicit mazefield(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void SetModel(Model *model);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Model *model_;
    QPoint begin_, end_;
    bool left = false, right = false;
    double cellWidth_ = 0.0;
    double cellHeight_ = 0.0;
    double x_start_, y_start_,x_end_,y_end_;

    void posToAxis();
    QPoint axisToPos(std::pair<int, int> pathIndex);
};

#endif // MAZEFIELD_H
