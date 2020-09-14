#ifndef SYSTEM_H
#define SYSTEM_H

#include <QTabWidget>
#include"extravector.h"
#include"teacher.h"
#include"student.h"
#include"score.h"
namespace Ui {
class SYSTEM;
}

class SYSTEM : public QTabWidget
{
    Q_OBJECT

public:
    explicit SYSTEM(QWidget *parent = 0);
    ~SYSTEM();

    void write(const extravector<Teacher>& lhs,const extravector<Student>& rhs){m_sys_teacher=lhs;m_sys_student=rhs;}
    void initial_show();

private slots:
    void on_search_1_textChanged(const QString &arg1);

    void on_search_2_textChanged(const QString &arg1);

    void on_search_3_textChanged(const QString &arg1);

    void on_add_1_clicked();

    void on_del_1_clicked();

    void on_save_1_clicked();

    void on_add_2_clicked();

    void on_del_2_clicked();



    void on_add_3_clicked();

    void on_del_3_clicked();



    void on_save_2_clicked();

    void on_save_3_clicked();

private:
    Ui::SYSTEM *ui;

    extravector<Teacher>m_sys_teacher;
    extravector<Student>m_sys_student;
    extravector<Course>m_sys_course;

    int m_s1,m_s2,m_s3;
};

#endif // SYSTEM_H
