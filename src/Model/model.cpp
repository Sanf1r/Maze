#include "model.h"

namespace s21 {

bool Model::Load(const std::string &path) {
  std::ifstream inFile(path);
  std::string temp;
  std::getline(inFile, temp);
  std::istringstream ss(temp);
  int c = 0;

  ss >> rows_ >> cols_;

  if (rows_ < 1 || cols_ < 1) return false;

  data_vert_.Clear();
  data_hor_.Clear();

  data_vert_.SetCol(cols_);
  data_hor_.SetCol(cols_);

  for (int i = 0; i < rows_; ++i) {
    std::getline(inFile, temp);
    std::istringstream ss(temp);
    int x;
    c = 0;
    while (ss >> x || !ss.eof()) {
        if ((x != 1 && x != 0) || ss.fail()) return false;
      data_vert_.Push(x);
      c++;
    }
    if (c != cols_) return false;
  }

  std::getline(inFile, temp);

  for (int i = 0; i < rows_; ++i) {
    std::getline(inFile, temp);
    std::istringstream ss(temp);
    c = 0;
    int x;
    while (ss >> x || !ss.eof()) {
        if ((x != 1 && x != 0) || ss.fail()) return false;
      data_hor_.Push(x);
      c++;
    }
    if (c != cols_) return false;
  }

  return true;
}

void Model::Save(const std::string &path) {
    std::ofstream f(path);

      f << rows_ << " " << cols_ << std::endl;
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (j != 0) f << ' ';
          f << data_vert_(i,j);
        }
        f << std::endl;
      }

      f << std::endl;

      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (j != 0) f << ' ';
          f << data_hor_(i,j);
        }
        f << std::endl;
      }

      f.close();

}

bool Model::RandomBool() {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> gen(0, 1);
  return (gen(rng) == 1) ? true : false;
}

void Model::GenerateMaze(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  counter_ = 1;

  gen_string_.clear();

  data_vert_.Init(rows_ * cols_, 0);
  data_hor_.Init(rows_ * cols_, 0);

  data_vert_.SetCol(cols_);
  data_hor_.SetCol(cols_);

  FillEmpty();
  for (int j = 0; j < rows_ - 1; j++) {
    AssignUniqueSet();
    AddingVerticalWalls(j);
    AddingHorizontalWalls(j);
    CheckedHorizontalWalls(j);
    PreparatingNewLine(j);
  }
  AddingEndLine();
}

void Model::FillEmpty() {
  for (int i = 0; i < cols_; i++) {
    gen_string_.push_back(0);
  }
}

void Model::AssignUniqueSet() {
  for (int i = 0; i < cols_; i++) {
    if (gen_string_[i] == 0) {
      gen_string_[i] = counter_++;
    }
  }
}

void Model::AddingVerticalWalls(int row) {
  for (int i = 0; i < cols_ - 1; i++) {
    bool choise = RandomBool();
    if (choise == true || gen_string_[i] == gen_string_[i + 1]) {
      data_vert_(row, i) = 1;
    } else {
      MergeSet(i, gen_string_[i]);
    }
  }
  data_vert_(row, cols_ - 1) = 1;
}

void Model::MergeSet(int index, int element) {
  int mutableSet = gen_string_[index + 1];
  for (int j = 0; j < cols_; j++) {
    if (gen_string_[j] == mutableSet) {
      gen_string_[j] = element;
    }
  }
}

void Model::AddingHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    bool choise = RandomBool();
    if (CalculateUniqueSet(gen_string_[i]) != 1 && choise == true) {
      data_hor_(row, i) = 1;
    }
  }
}

int Model::CalculateUniqueSet(int element) {
  int countUniqSet = 0;
  for (int i = 0; i < cols_; i++) {
    if (gen_string_[i] == element) {
      countUniqSet++;
    }
  }
  return countUniqSet;
}

void Model::CheckedHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    if (CalculateHorizontalWalls(gen_string_[i], row) == 0) {
      data_hor_(row, i) = 0;
    }
  }
}

int Model::CalculateHorizontalWalls(int element, int row) {
  int countHorizontalWalls = 0;
  for (int i = 0; i < cols_; i++) {
    if (gen_string_[i] == element && data_hor_(row, i) == 0) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

void Model::PreparatingNewLine(int row) {
  for (int i = 0; i < cols_; i++) {
    if (data_hor_(row, i) == 1) {
      gen_string_[i] = 0;
    }
  }
}

void Model::AddingEndLine() {
  AssignUniqueSet();
  AddingVerticalWalls(rows_ - 1);
  CheckedEndLine();
}

void Model::CheckedEndLine() {
  for (int i = 0; i < cols_ - 1; i++) {
    if (gen_string_[i] != gen_string_[i + 1]) {
      data_vert_(rows_ - 1, i) = 0;
      MergeSet(i, gen_string_[i]);
    }
    data_hor_(rows_ - 1, i) = 1;
  }
  data_hor_(rows_ - 1, cols_ - 1) = 1;
}

void Model::CreateMap() {
  map_.Clear();
  map_.SetCol(cols_);
  map_.Init(rows_ * cols_, -1);
}

int Model::EnterBox(int value, int box) {
  if (box == -1)
    box = value;
  else
    box = std::min(box, value);
  return box;
}

void Model::ForwardMaze(int step) {
  int result = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (map_(i, j) == step) {
        result++;
        if (i < rows_ - 1 && !data_hor_(i, j)) {
          map_(i + 1, j) = EnterBox(step + 1, map_(i + 1, j));
        }
        if (i > 0 && !data_hor_(i - 1, j)) {
          map_(i - 1, j) = EnterBox(step + 1, map_(i - 1, j));
        }
        if (j < cols_ - 1 && !data_vert_(i, j)) {
          map_(i, j + 1) = EnterBox(step + 1, map_(i, j + 1));
        }
        if (j > 0 && !data_vert_(i, j - 1)) {
          map_(i, j - 1) = EnterBox(step + 1, map_(i, j - 1));
        }
      }
    }
  }
}

void Model::MakeWay(int i_start, int j_start, int i_end, int j_end) {
  map_(i_start, j_start) = 0;
  int step = 0;
  while (map_(i_end, j_end) == -1) {
    ForwardMaze(step++);
  }
  int i = i_end, j = j_end;
  right__path_.clear();
  right__path_.push_back(std::pair(i_end, j_end));
  while (step != 0) {
    // move down
    if (i < rows_ - 1 && !data_hor_(i, j) && map_(i + 1, j) == step - 1) i++;
    // move up
    else if (i > 0 && !data_hor_(i - 1, j) && map_(i - 1, j) == step - 1)
      i--;
    // move right_
    else if (j < cols_ - 1 && !data_vert_(i, j) && map_(i, j + 1) == step - 1)
      j++;
    // move left_
    else if (j > 0 && !data_vert_(i, j - 1) && map_(i, j - 1) == step - 1)
      j--;
    right__path_.push_back(std::pair(i, j));
    step--;
  }
}

void Model::SolveMaze(int i_start, int j_start, int i_end, int j_end) {
  CreateMap();
  MakeWay(i_start, j_start, i_end, j_end);
}

void Model::ClearMap() {
  map_.Clear();
  right__path_.clear();
}

}  // namespace s21
