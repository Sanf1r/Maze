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


    double i_start() const;

    double j_start() const;

    double i_end() const;

    double j_end() const;

    void resetFlags();


protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Model *model_;
    QPoint begin_, end_;
    bool left = false, right = false;
    double cellWidth_ = 0.0;
    double cellHeight_ = 0.0;
    double i_start_, j_start_,i_end_,j_end_;

    QPoint axisToPos(std::pair<int, int> pathIndex);
    void startPoint();
    void endPoint();
};

#endif // MAZEFIELD_H
