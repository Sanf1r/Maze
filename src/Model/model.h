#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "data.h"

namespace s21 {

class Model {
 public:
  Model() { GenerateMaze(5, 5); };
  void Load(const std::string &path);
  int GetRows() { return rows_; }
  int GetCols() { return cols_; }
  Data &GetVert() { return data_vert_; }
  Data &GetHor() { return data_hor_; }
  std::vector<std::pair<int, int>> &GetPath() { return right__path_; }
  void GenerateMaze(int rows, int cols);
  void SolveMaze(int i_start, int j_start, int i_end, int j_end);
  void ClearMap();

 private:
  int rows_ = 0;
  int cols_ = 0;
  int counter_ = 1;

  Data data_vert_;
  Data data_hor_;
  Data map_;
  std::vector<int> gen_string_;
  std::vector<std::pair<int, int>> right__path_;

  bool RandomBool();
  void FillEmpty();
  void AssignUniqueSet();
  void MergeSet(int index, int element);
  void AddingVerticalWalls(int row);
  int CalculateUniqueSet(int element);
  void AddingHorizontalWalls(int row);
  int CalculateHorizontalWalls(int element, int row);
  void CheckedHorizontalWalls(int row);
  void CheckedEndLine();
  void AddingEndLine();
  void PreparatingNewLine(int row);
  void CreateMap();
  int EnterBox(int value, int box);
  void SolveMaze(int step);
  void MakeWay(int i_start, int j_start, int i_end, int j_end);
};

}  // namespace s21

#endif  // MODEL_H
