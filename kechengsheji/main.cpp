#include "course_score.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    course_score w;
    w.show();

    return a.exec();
}
