#ifndef MAZEFIELD_H
#define MAZEFIELD_H

#include <QWidget>
#include <QPainter>
#include <QMainWindow>
#include <QApplication>

#include "model.h"

class mazefield : public QWidget
{
    Q_OBJECT
public:
    explicit mazefield(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void SetModel(Model *model);

    void SetPaint(bool flag) { paint = flag; }

signals:

private:
    Model *model_;
    bool paint = false;

};

#endif // MAZEFIELD_H
