#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
QPainter painter(this);
QPen pen = (QApplication::palette().text().color());  // creates a default pen
pen.setWidth(2);
painter.setPen(pen);
int max_size = 500;
int x_start = 200;
int y_start = 10;
//painter.drawRect(QRect(x_start,y_start,max_size,max_size));


std::string file = "/Users/morfinov/Downloads/A1_Maze-1-sabina/src/maze-1/mazes/10_5_test.txt";

std::ifstream inFile(file);
std::string temp;
int row, cols;
std::getline(inFile, temp);
std::istringstream ss(temp);
ss >> row >> cols;

std::cout << "row = " << row << std::endl;
std::cout << "cols = " << cols << std::endl;

data_vert.resize(row);
data_hor.resize(row);

for (int i = 0; i < row; ++i) {
        std::getline(inFile, temp);
        std::istringstream ss(temp);
        int x;
        while (ss >> x) {
        data_vert[i].push_back(x);

    }
}

std::getline(inFile, temp);

for (int i = 0; i < row; ++i) {
        std::string temp;
        std::getline(inFile, temp);
        std::istringstream ss(temp);
        int x;
        while (ss >> x) {
        data_hor[i].push_back(x);
    }
}

//cell sizes
int cell_size = std::min(max_size / cols, max_size / row);

painter.drawLine(x_start,y_start,x_start + (cols * cell_size),y_start);
painter.drawLine(x_start,y_start,x_start,y_start + (row * cell_size));

for (int i = y_start, k = 0; k < row; i += cell_size) {
    for (int j = x_start + cell_size, l = 0; l < cols; j += cell_size) {
        if (data_vert[k][l++] == 1) {
            painter.drawLine(j,i,j,i + cell_size);
        }
    }
    k++;
}
for (int i = y_start + cell_size, k = 0; k < row; i += cell_size) {
    for (int j = x_start, l = 0; l < cols; j += cell_size) {
        if (data_hor[k][l++] == 1) {
            painter.drawLine(j,i,j + cell_size,i);
        }
    }
    k++;
}
}

