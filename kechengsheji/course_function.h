#ifndef COURSE_FUNCTION_H
#define COURSE_FUNCTION_H

#include <QTabWidget>
#include"extravector.h"
#include"course.h"
namespace Ui {
class course_function;
}

class course_function : public QTabWidget
{
    Q_OBJECT

public:
    explicit course_function(QWidget *parent = 0);
    ~course_function();

private slots:
    void on_search_textChanged(const QString &arg1);

    void on_Btn_function_1_clicked();

    void on_Btn_function_2_clicked();

    void on_search_2_textChanged(const QString &arg1);

    void on_Btn_function_3_clicked();

private:
    Ui::course_function *ui;

    extravector<Course> m_courses;
    extravector<Course>m_mycourse;

    int m_mycourse_row;                 //记录行数
};

#endif // COURSE_FUNCTION_H
