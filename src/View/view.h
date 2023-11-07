#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../Controller/controller.h"
#include "mazefield.h"
#include "ui_view.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(Controller *c, QWidget *parent = nullptr);
  ~View();

  void LoadMaze();
  void SaveMaze();
  void GenMaze();
  void Redme();

 private:
  Ui::View *ui_;
  Controller *controller_;
};

}  // namespace s21

#endif  // MAINWINDOW_H
