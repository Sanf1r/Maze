#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>

class Model
{
public:
    Model() {generateMaze(5,5);};
    void parse(const std::string &path);
    int GetRows() {return rows_;}
    int GetCols() {return cols_;}
    std::vector<std::vector<int>> &GetVert() {return data_vert;}
    std::vector<std::vector<int>> &GetHor() {return data_hor;}
    std::vector<std::pair<int,int>> &GetPath() {return rightPath_;}
    void generateMaze(int rows, int cols);


    void mapOut();
private:
    bool paint_ = false;
    int rows_ = 0;
    int counter_ = 1;

    int cols_ = 0;

    std::vector<int> genString;

    std::vector<std::vector<int>> data_vert;

    std::vector<std::vector<int>> data_hor;

    std::vector<std::vector<int>> map_;

    std::vector<std::pair<int,int>> rightPath_;

    bool randomBool();
    void fillEmpty();
    void assignUniqueSet();
    void mergeSet(int index, int element);
    void addingVerticalWalls(int row);
    int calculateUniqueSet(int element);
    void addingHorizontalWalls(int row);
    int calculateHorizontalWalls(int element, int row);
    void checkedHorizontalWalls(int row);
    void checkedEndLine();
    void addingEndLine();
    void preparatingNewLine(int row);
    void createMap();
    int enterBox(int value, int box);
    void makeWay();
    void solveMaze(int step);
};

#endif // MODEL_H
