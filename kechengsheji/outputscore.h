#ifndef OUTPUTSCORE_H
#define OUTPUTSCORE_H

#include <QTabWidget>
#include"extravector.h"
#include"course.h"
namespace Ui {
class outputscore;
}

class outputscore : public QTabWidget
{
    Q_OBJECT

public:
    explicit outputscore(QWidget *parent = 0);
    ~outputscore();

    void set_data_id(const QString&rhs){m_id_Edit=rhs;}
    void initial();          //初始化个人成绩表
private slots:
    void on_pushButton_clicked();

private:
    Ui::outputscore *ui;

    int m_course_size;

    extravector<Course> m_courses;
    QString m_id_Edit;
    QString m_stu_course[30];
    QString m_stu_score[30];

};

#endif // OUTPUTSCORE_H
