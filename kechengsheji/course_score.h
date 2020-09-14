#ifndef COURSE_SCORE_H
#define COURSE_SCORE_H
#include"student_function.h"
#include"operate_score.h"
#include"system.h"

#include"extravector.h"
#include"student.h"
#include"teacher.h"
#include <QMainWindow>

namespace Ui {
class course_score;
}

class course_score : public QMainWindow
{
    Q_OBJECT

public:
    explicit course_score(QWidget *parent =0);
    ~course_score();

private slots:
    void on_login_clicked();

private:
    Ui::course_score *ui;
    QString accountdata;
    student_function *m_sstudent;
    operate_score *m_operator;
    SYSTEM *m_system;

    extravector<Student> m_students;
    extravector<Teacher> m_teachers;
};

#endif // COURSE_SCORE_H
