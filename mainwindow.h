#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QFileDialog>

#include <model.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Model *model, QWidget *parent = nullptr);
    ~MainWindow();

    void loadMaze();

   public:

private:
    Ui::MainWindow *ui;
    Model *model_;

};
#endif // MAINWINDOW_H
