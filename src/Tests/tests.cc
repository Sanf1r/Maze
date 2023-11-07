#include <gtest/gtest.h>

#include "../Model/model.h"

namespace {

s21::Model test;

TEST(ModelTest, 01) {
  test.GenerateMaze(5, 5);
  test.SolveMaze(0, 0, 4, 4);
}

TEST(ModelTest, 02) {
  std::string load_path = "PATH_SRC/Mazes/maze_10_10.txt";
  std::string save_path = "PATH_SRC/Mazes/maze_3_3_for_test.txt";
  test.Load(load_path);
  test.GenerateMaze(3, 3);
  test.Save(save_path);
}

}  // namespace
