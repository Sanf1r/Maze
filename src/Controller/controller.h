#ifndef A1_MAZE_SRC_CONTROLLER_CONTROLLER_H_
#define A1_MAZE_SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Model *m) : model_(m){};

  int GetRows() { return model_->GetRows(); }
  int GetCols() { return model_->GetCols(); }
  Data &GetVert() { return model_->GetVert(); }
  Data &GetHor() { return model_->GetHor(); }
  std::vector<std::pair<int, int>> &GetPath() { return model_->GetPath(); }

  bool Load(const std::string &path) { return model_->Load(path); }
  void Save(const std::string &path) { model_->Save(path); }
  void GenerateMaze(int rows, int cols) { model_->GenerateMaze(rows, cols); }
  void SolveMaze(int i_start, int j_start, int i_end, int j_end) {
    model_->SolveMaze(i_start, j_start, i_end, j_end);
  }
  void ClearMap() { model_->ClearMap(); }

 private:
  Model *model_;
};

}  // namespace s21

#endif  //  A1_MAZE_SRC_CONTROLLER_CONTROLLER_H_
