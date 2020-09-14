#ifndef STUDENT_FUNCTION_H
#define STUDENT_FUNCTION_H
#include"course_function.h"
#include"outputscore.h"
#include <QWidget>

namespace Ui {
class student_function;
}

class student_function : public QWidget
{
    Q_OBJECT

public:
    explicit student_function(QWidget *parent = 0);
    ~student_function();

     void get_id_accountdata(const QString&rhs){m_id_user=rhs;}
private slots:
     void on_function_del_clicked();

     void on_search_score_clicked();

     void on_search_score_2_clicked();

private:
    Ui::student_function *ui;
    course_function *m_scourse;
    outputscore *m_show;

    QString m_id_user;
};

#endif // STUDENT_FUNCTION_H
