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

bool Model::randomBool() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> gen(0, 1);
    return (gen(rng) == 1) ? true : false;
}

void Model::generateMaze(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    counter_ = 1;

    data_vert.clear();
    data_hor.clear();
    genString.clear();

    data_vert.resize(rows_);
    for (int i = 0; i < (int)data_vert.size(); ++i) {
        data_vert[i].resize(cols_, 0);
    }
    data_hor.resize(rows_);
    for (int i = 0; i < (int)data_vert.size(); ++i) {
        data_hor[i].resize(cols_, 0);
    }

    fillEmpty();
    for (int j = 0; j < rows_ - 1; j++) {
            /* Шаг 2 */
            assignUniqueSet();
            /* Шаг 3 */
            addingVerticalWalls(j);
            /* Шаг 4 */
            addingHorizontalWalls(j);
            checkedHorizontalWalls(j);
            /* Шаг 5.1*/
            preparatingNewLine(j);
        }
    /* Шаг 5.2 */
        addingEndLine();
}

void Model::fillEmpty() {
    for (int i = 0; i < cols_; i++) {
            genString.push_back(0);
        }
}

void Model::assignUniqueSet() {
    for (int i = 0; i < cols_; i++) {
        if (genString[i] == 0) {
            genString[i] = counter_;
            counter_++;
        }
    }
}

void Model::addingVerticalWalls(int row) {
    for (int i = 0; i < cols_ - 1; i++) {
        bool choise = randomBool();
        if (choise == true || genString[i] == genString[i + 1]) {
            data_vert[row][i] = 1;
        } else {
            /* Объединение ячеек в одно множество */
            mergeSet(i, genString[i]);
        }
    }
    /* Добавление правой стенки в последней ячейки */
    data_vert[row][cols_ - 1] = 1;
}

/* Объединение ячеек в одно множество */
void Model::mergeSet(int index, int element) {
    int mutableSet = genString[index + 1];
    for (int j = 0; j < cols_; j++) {
        /* Проверка ячеек на одно множество */
        if (genString[j] == mutableSet) {
            /* Объединение ячейки в множество */
            genString[j] = element;
        }
    }
}

/* Добавление нижней горизонтальной стенки */
void Model::addingHorizontalWalls(int row) {
    for (int i = 0; i < cols_; i++) {
        /* Ставим стенку или нет */
        bool choise = randomBool();
        /* Проверка, что множество имеет более одной ячейки (это предовратит замкнутые области  */
        if (calculateUniqueSet(genString[i]) != 1 && choise == true) {
            /* Ставим горизонтальную стенку */
            data_hor[row][i] = 1;
        }
    }
}

/* Подсчет ячеек, которые содержаться в уникальном множестве */
int Model::calculateUniqueSet(int element) {
    int countUniqSet = 0;
    for (int i = 0; i < cols_; i++) {
        if (genString[i] == element) {
            countUniqSet++;
        }
    }
    return countUniqSet;
}

/* Проверка условие 4.1 и 4.2 */
void Model::checkedHorizontalWalls(int row) {
    for (int i = 0; i < cols_; i++) {
        if (calculateHorizontalWalls(genString[i], row) == 0) {
            data_hor[row][i] = 0;
        }
    }
}

/* Подсчет горизонтальных стен у ячеек уникального множества */
int Model::calculateHorizontalWalls(int element, int row) {
    int countHorizontalWalls = 0;
    for (int i = 0; i < cols_; i++) {
        if (genString[i] == element && data_hor[row][i] == 0) {
            countHorizontalWalls++;
        }
    }
    return countHorizontalWalls;
}

void Model::preparatingNewLine(int row) {
    for (int i = 0; i < cols_; i++) {
        if (data_hor[row][i] == 1) {
            /* Присваиваем ячейки пустое множество */
            genString[i] = 0;
        }
    }
}

/* Добавление последней строки */
void Model::addingEndLine() {
    assignUniqueSet();
    addingVerticalWalls(rows_ - 1);
    checkedEndLine();
}

/* Проверка условий на добавление последней строки */
void Model::checkedEndLine() {
    for (int i = 0; i < cols_ - 1; i++) {
        /* Проверка условия пункта 5.2.1 */
        if (genString[i] != genString[i + 1]) {
            /* Убираем вертикальную стенку */
            data_vert[rows_ - 1][i] = 0;
            /* Объединяем множества */
            mergeSet(i, genString[i]);
        }
        /* Добавляем горизонтальные стенки */
        data_hor[rows_ - 1][i] = 1;
    }
    /* Добавляем горизонтальную стенку в последней ячейке */
    data_hor[rows_ - 1][cols_ - 1] = 1;
}

void Model::createMap() {
    map_.clear();
    map_.resize(rows_);
    for (int i = 0; i < (int)map_.size(); ++i) {
        map_[i].resize(cols_, -1);
    }
}

int Model::enterBox(int value, int box) {
    if (box == -1)
            box = value;
        else
            box = std::min(box, value);
        return box;
}

void Model::solveMaze(int step) {
    int result = 0;
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (map_[i][j] == step) {
                    result++;
                    if (i < rows_ - 1 && !data_hor[i][j]) {
                        map_[i + 1][j] = enterBox(step + 1, map_[i + 1][j]);
                    }
                    if (i > 0 && !data_hor[i - 1][j]) {
                        map_[i - 1][j] = enterBox(step + 1, map_[i - 1][j]);
                    }
                    if (j < cols_ - 1 && !data_vert[i][j]) {
                        map_[i][j + 1] = enterBox(step + 1, map_[i][j + 1]);
                    }
                    if (j > 0 && !data_vert[i][j - 1]) {
                        map_[i][j - 1] = enterBox(step + 1, map_[i][j - 1]);
                    }
                }
            }
        }
//        return result;
}

void Model::makeWay() {
    int i_start = 0, j_start = 0, i_end = 0, j_end = 4;
    map_[i_start][j_start] = 0;
    int step = 0;
    while (map_[i_end][j_end] == -1) {
    solveMaze(step++);
    }
    int new_i = i_end, new_j = j_end;
    rightPath_.clear();
    rightPath_.push_back(std::pair(i_end,j_end));
    while (step != 0) {
                    // move down
                    if (new_i < rows_ - 1 && !data_hor[new_i][new_j] && map_[new_i + 1][new_j] == step - 1)
                        new_i++;
                    // move up
                    else if (new_i > 0 && !data_hor[new_i - 1][new_j] && map_[new_i - 1][new_j] == step - 1)
                        new_i--;
                    // move right
                    else if (new_j < cols_ - 1 && !data_vert[new_i][new_j] && map_[new_i][new_j + 1] == step - 1)
                        new_j++;
                    // move left
                    else if (new_j > 0 && !data_vert[new_i][new_j - 1] && map_[new_i][new_j - 1] == step - 1)
                        new_j--;
                    rightPath_.push_back(std::pair(new_i,new_j));
                    step--;
    }
}

void Model::mapOut() {
    createMap();
    makeWay();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << map_[i][j] << " ";
        }
        std::cout << std::endl;
        }
    for (int i = 0; i < (int)rightPath_.size(); i++) {
        std::cout << "i = " << rightPath_[i].first << " j = " << rightPath_[i].second << std::endl;
    }
}



