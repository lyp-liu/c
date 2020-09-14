#ifndef OPERATE_SCORE_H
#define OPERATE_SCORE_H

#include <QTabWidget>
#include"extravector.h"
#include<score.h>
#include<QString>
#include<QTableWidgetItem>
namespace Ui {
class operate_score;
}

class operate_score : public QTabWidget
{
    Q_OBJECT

public:
    explicit operate_score(QWidget *parent =0);
    ~operate_score();


    void initial_show();//用来显示数据
    void initial_course(const QString&, const QString&, const QString&,const QString&);



private slots:
    void on_search_1_textChanged(const QString &arg1);
 void sortByColumn1(int col);
 void sortByColumn2(int col);
 void sortByColumn3(int col);
 void sortByColumn4(int col);
    void on_search_2_textChanged(const QString &arg1);

    void on_search_3_textChanged(const QString &arg1);

    void on_Btn_add_1_clicked();

    void on_Btn_erase_1_clicked();

    void on_Btn_ave_1_clicked();

    void on_Btn_pass_1_clicked();

    void on_Btn_BZC_1_clicked();

    void on_Btn_add_2_clicked();

    void on_Btn_erase_2_clicked();

    void on_Btn_ave_2_clicked();

    void on_Btn_pass_2_clicked();

    void on_Btn_BZC_2_clicked();

    void on_Btn_add_3_clicked();

    void on_Btn_erase_3_clicked();

    void on_Btn_ave_3_clicked();

    void on_Btn_pass_3_clicked();

    void on_Btn_BZC_3_clicked();

    void on_pushButton_clicked();


    void on_search_4_textChanged(const QString &arg1);

    void on_Btn_add_4_clicked();

    void on_Btn_erase_4_clicked();

    void on_Btn_ave_4_clicked();

    void on_Btn_pass_4_clicked();

    void on_Btn_BZC_4_clicked();




private:
    Ui::operate_score *ui;

    extravector<Score> m_scores;
QStringList headers;
    QString m_courses[4];
    double m_ave1,m_BZC1,m_JGL1;
    double m_ave2,m_BZC2,m_JGL2;
    double m_ave3,m_BZC3,m_JGL3;
  double m_ave4,m_BZC4,m_JGL4;


operate_score *m_operate;//operate_score是窗口类

   int m_s1,m_s2,m_s3,m_s4;                       //记录4个列表的目前行数
};
class MyTableWidgetItem : public QTableWidgetItem
{
public:
    MyTableWidgetItem(const QString& text):
        QTableWidgetItem(text)
    {
    }
public:
    bool operator <(const QTableWidgetItem &other) const
    {
        return text().toFloat() < other.text().toFloat();
    }
};
#endif // OPERATE_SCORE_H
