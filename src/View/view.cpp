#include "view.h"

namespace s21 {

View::View(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::View), controller_(c) {
  ui_->setupUi(this);
  ui_->maze->SetControl(controller_);
  connect(ui_->pushButton, &QPushButton::released, this, &View::LoadMaze);
  connect(ui_->pushButton_2, &QPushButton::released, this, &View::GenMaze);
  connect(ui_->pushButton_4, &QPushButton::released, this, &View::Redme);
}

View::~View() { delete ui_; }

void View::LoadMaze() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open Maze File", "", "Maze Files (*.txt);;All Files (*)");
  if (!fileName.isEmpty()) {
    controller_->Load(fileName.toStdString());
    controller_->ClearMap();
    ui_->maze->ResetFlags();
    update();
  }
}

void View::GenMaze() {
  controller_->ClearMap();
  ui_->maze->ResetFlags();
  controller_->GenerateMaze(ui_->spinBox->value(), ui_->spinBox_2->value());
  update();
}

void View::Redme() {
  QMessageBox msgBox;
  msgBox.setText(
      "Instructions:\n"
      "- Load button - load the maze from a file\n"
      "- Save button - save the maze in the file\n"
      "- Generate - generate a perfect maze according to Eller's algorithm\n"
      "- To solve the maze use LMB to sets the starting and ending points\n"
      "- RMB removes path from the maze");
  msgBox.exec();
}

}  // namespace s21
