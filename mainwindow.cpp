#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(Model *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      model_(model)
{
    ui->setupUi(this);
    ui->maze->SetModel(model);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::loadMaze);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMaze()
{

      QString fileName = QFileDialog::getOpenFileName(
          this, "Open Maze File", "", "Maze Files (*.txt);;All Files (*)");
      if (!fileName.isEmpty()) {
          model_->parse(fileName.toStdString());
          ui->maze->SetPaint(true);
          update();
      }
}
