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
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::genMaze);
    connect(ui->pushButton_4, &QPushButton::released, this, &MainWindow::redme);
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
          model_->clearMap();
          ui->maze->resetFlags();
          update();
      }
}

void MainWindow::genMaze()
{
      model_->clearMap();
      ui->maze->resetFlags();
      model_->generateMaze(ui->spinBox->value(),ui->spinBox_2->value());

      update();
}

void MainWindow::redme()
{
    QMessageBox msgBox;
    msgBox.setText("Instructions:\n"
                   "- Load button - load the maze from a file\n"
                   "- Save button - save the maze in the file\n"
                   "- Generate - generate a perfect maze according to Eller's algorithm\n"
                   "- To solve the maze use LMB to sets the starting and ending points\n"
                   "- RMB removes path from the maze");
    msgBox.exec();
}

