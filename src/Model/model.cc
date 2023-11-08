#include "model.h"

namespace s21 {

/**
 * @brief The method reads data from a file and fills two
 * vectors for vertical and horizontal lines and the size of the maze
 *
 * @param path
 * @return true
 * @return false
 */
bool Model::Load(const std::string &path) {
  std::ifstream inFile(path);
  std::string temp;
  std::getline(inFile, temp);
  std::istringstream ss(temp);
  int c;

  ss >> rows_ >> cols_;

  if (rows_ < 1 || cols_ < 1) return false;

  data_vert_.Clear();
  data_hor_.Clear();

  data_vert_.SetCol(cols_);
  data_hor_.SetCol(cols_);

  for (int i = 0; i < rows_; ++i) {
    std::getline(inFile, temp);
    std::istringstream vss(temp);
    int x;
    c = 0;
    while (vss >> x || !vss.eof()) {
      if ((x != 1 && x != 0) || vss.fail()) return false;
      data_vert_.Push(x);
      c++;
    }
    if (c != cols_) return false;
  }

  std::getline(inFile, temp);

  for (int i = 0; i < rows_; ++i) {
    std::getline(inFile, temp);
    std::istringstream hss(temp);
    c = 0;
    int x;
    while (hss >> x || !hss.eof()) {
      if ((x != 1 && x != 0) || hss.fail()) return false;
      data_hor_.Push(x);
      c++;
    }
    if (c != cols_) return false;
  }

  return true;
}

/**
 * @brief The method reads the maze data and stores it as the size of the
 * maze as well as a matrix of vertical lines and a matrix of horizontal lines
 *
 * @param path
 */
void Model::Save(const std::string &path) {
  std::ofstream f(path);

  f << rows_ << " " << cols_ << std::endl;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (j != 0) f << ' ';
      f << data_vert_(i, j);
    }
    f << std::endl;
  }

  f << std::endl;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (j != 0) f << ' ';
      f << data_hor_(i, j);
    }
    f << std::endl;
  }

  f.close();
}

/**
 * @brief Generates random responses to requests for drawing maze walls
 *
 * @return true
 * @return false
 */
bool Model::RandomBool() {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> gen(0, 1);
  return (gen(rng) == 1) ? true : false;
}

/**
 * @brief Generates a maze randomly and with a certain size
 *
 * @param rows
 * @param cols
 */
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

/**
 * @brief Fills the line of maze with 0
 *
 */
void Model::FillEmpty() {
  for (int i = 0; i < cols_; i++) {
    gen_string_.push_back(0);
  }
}

/**
 * @brief Checks cells and fills with unique values as needed
 *
 */
void Model::AssignUniqueSet() {
  for (int i = 0; i < cols_; i++) {
    if (gen_string_[i] == 0) {
      gen_string_[i] = counter_++;
    }
  }
}

/**
 * @brief Fills an array with data on the vertical walls of the maze
 *
 * @param row
 */
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

/**
 * @brief
 *
 * @param index
 * @param element
 */
void Model::MergeSet(int index, int element) {
  int mutableSet = gen_string_[index + 1];
  for (int j = 0; j < cols_; j++) {
    if (gen_string_[j] == mutableSet) {
      gen_string_[j] = element;
    }
  }
}

/**
 * @brief Fills an array with data on the horizontal walls of the maze
 *
 * @param row
 */
void Model::AddingHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    bool choise = RandomBool();
    if (CalculateUniqueSet(gen_string_[i]) != 1 && choise == true) {
      data_hor_(row, i) = 1;
    }
  }
}

/**
 * @brief
 *
 * @param element
 * @return int
 */
int Model::CalculateUniqueSet(int element) {
  int countUniqSet = 0;
  for (int i = 0; i < cols_; i++) {
    if (gen_string_[i] == element) {
      countUniqSet++;
    }
  }
  return countUniqSet;
}

/**
 * @brief
 *
 * @param row
 */
void Model::CheckedHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    if (CalculateHorizontalWalls(gen_string_[i], row) == 0) {
      data_hor_(row, i) = 0;
    }
  }
}

/**
 * @brief Counts the number of horizontal walls in row
 *
 * @param element
 * @param row
 * @return int
 */
int Model::CalculateHorizontalWalls(int element, int row) {
  int countHorizontalWalls = 0;
  for (int i = 0; i < cols_; i++) {
    if (gen_string_[i] == element && data_hor_(row, i) == 0) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

/**
 * @brief
 *
 * @param row
 */
void Model::PreparatingNewLine(int row) {
  for (int i = 0; i < cols_; i++) {
    if (data_hor_(row, i) == 1) {
      gen_string_[i] = 0;
    }
  }
}

/**
 * @brief
 *
 */
void Model::AddingEndLine() {
  AssignUniqueSet();
  AddingVerticalWalls(rows_ - 1);
  CheckedEndLine();
}

/**
 * @brief
 *
 */
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

/**
 * @brief
 *
 */
void Model::CreateMap() {
  map_.Clear();
  map_.SetCol(cols_);
  map_.Init(rows_ * cols_, -1);
}

/**
 * @brief
 *
 * @param value
 * @param box
 * @return int
 */
int Model::EnterBox(int value, int box) {
  if (box == -1)
    box = value;
  else
    box = std::min(box, value);
  return box;
}

/**
 * @brief
 *
 * @param step
 */
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

/**
 * @brief Fills an array with the coordinates of the path between two points
 *
 * @param i_start
 * @param j_start
 * @param i_end
 * @param j_end
 */
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

/**
 * @brief Draws a maze and also draws a path between two points
 *
 * @param i_start
 * @param j_start
 * @param i_end
 * @param j_end
 */
void Model::SolveMaze(int i_start, int j_start, int i_end, int j_end) {
  CreateMap();
  MakeWay(i_start, j_start, i_end, j_end);
}

/**
 * @brief Clears maze data
 *
 */
void Model::ClearMap() {
  map_.Clear();
  right__path_.clear();
}

}  // namespace s21
