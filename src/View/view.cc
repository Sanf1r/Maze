#include "view.h"

namespace s21 {

View::View(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::View), controller_(c) {
  ui_->setupUi(this);
  ui_->maze->SetControl(controller_);
  connect(ui_->pushButton, &QPushButton::released, this, &View::LoadMaze);
  connect(ui_->pushButton_2, &QPushButton::released, this, &View::GenMaze);
  connect(ui_->pushButton_3, &QPushButton::released, this, &View::SaveMaze);
  connect(ui_->pushButton_4, &QPushButton::released, this, &View::Readme);
}

View::~View() { delete ui_; }

/**
 * @brief Method that calls a window to select a file and starts reading the
 * file
 *
 */
void View::LoadMaze() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open Maze File", "",
                                                  "Maze Files (*.txt)");
  if (!fileName.isEmpty()) {
    controller_->ClearMap();
    ui_->maze->ResetFlags();
    update();
    if (controller_->Load(fileName.toStdString())) {
    } else {
      controller_->GenerateMaze(5, 5);
      update();
      QMessageBox messageBox;
      messageBox.critical(0, "Error",
                          "Error with maze file!\n"
                          "Random maze generated.");
      messageBox.setFixedSize(500, 200);
    }
  }
}

/**
 * @brief Method that calls a window for choosing where to save the file and
 * starts saving the file
 *
 */
void View::SaveMaze() {
  QString fileName = QFileDialog::getSaveFileName(this, "Save Maze File", "",
                                                  "Maze Files (*.txt)");
  if (!fileName.isEmpty()) {
    controller_->Save(fileName.toStdString());
  }
}

/**
 * @brief The method cleans the map, resets the flags and starts generating a
 * new maze
 *
 */
void View::GenMaze() {
  controller_->ClearMap();
  ui_->maze->ResetFlags();
  controller_->GenerateMaze(ui_->spinBox->value(), ui_->spinBox_2->value());
  update();
}

/**
 * @brief The method calls an information window with a detailed description of
 * the buttons operation
 *
 */
void View::Readme() {
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
