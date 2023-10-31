#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Model
{
public:
    Model() = default;
    void parse(const std::string &path);
    int GetRows() {return rows_;}
    int GetCols() {return cols_;}
    std::vector<std::vector<int>> &GetVert() {return data_vert;}
    std::vector<std::vector<int>> &GetHor() {return data_hor;}
    void generateMaze(int rows, int cols);
    void fillEmpty();
    void assignUniqueSet();

private:
    bool paint_ = false;
    int rows_ = 0;
    int counter_ = 1;

    int cols_ = 0;

    std::vector<int> genString;

    std::vector<std::vector<int>> data_vert;

    std::vector<std::vector<int>> data_hor;

};

#endif // MODEL_H
