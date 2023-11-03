#include <QApplication>

#include "Controller/controller.h"
#include "Model/model.h"
#include "View/view.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::locale::global(std::locale("C"));
    QLocale curLocale(QLocale("C"));
    QLocale::setDefault(curLocale);
    s21::Model model;
    s21::Controller controller(&model);
    s21::View view(&controller);
    view.show();
    return a.exec();
}
