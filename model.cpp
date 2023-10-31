#include "model.h"

void Model::parse(const std::string &path)
{
        std::ifstream inFile(path);
        std::string temp;
        std::getline(inFile, temp);
        std::istringstream ss(temp);

        ss >> rows_ >> cols_;

        std::cout << "row = " << rows_ << std::endl;
        std::cout << "cols = " << cols_ << std::endl;

        data_vert.clear();
        data_hor.clear();

        data_vert.resize(rows_);
        data_hor.resize(rows_);

        for (int i = 0; i < rows_; ++i) {
                std::getline(inFile, temp);
                std::istringstream ss(temp);
                int x;
                while (ss >> x) {
                data_vert[i].push_back(x);
            }
        }

        std::getline(inFile, temp);

        for (int i = 0; i < rows_; ++i) {
                std::string temp;
                std::getline(inFile, temp);
                std::istringstream ss(temp);
                int x;
                while (ss >> x) {
                data_hor[i].push_back(x);
            }
        }
        paint_ = true;
}

void Model::generateMaze(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
}

void Model::fillEmpty() {
    for (int i = 0; i < cols_; i++) {
            genString.push_back(0);
        }
}

void Model::assignUniqueSet() {
    for (int i = 0; i < cols_; i++) {
        /* Проверяем на пустую ячейку */
        if (genString[i] == 0) {
            /* Присваиваем ячейки уникальное множество */
            genString[i] = counter_;
            counter_++;
        }
    }
}

