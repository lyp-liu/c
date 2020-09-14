#include "outputscore.h"
#include "ui_outputscore.h"
#include<fstream>
#include<QString>
#include<QMessageBox>
#include<stdlib.h>
#include<QTabWidget>
using namespace std;
outputscore::outputscore(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::outputscore),
  m_course_size(-1)
{
    ui->setupUi(this);
    setStyleSheet("border-image:url(:/yiyiyi.jpg);");
    ui->output->setRowCount(30);
    ui->output->setColumnCount(5);
    ui->output->setAlternatingRowColors(true);
    ui->output->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->output->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->output->setItem(0,0,new QTableWidgetItem(tr("课程编号")));
    ui->output->setItem(0,1,new QTableWidgetItem(tr("课程名称")));
    ui->output->setItem(0,2,new QTableWidgetItem(tr("成绩")));
    ui->output->setItem(0,3,new QTableWidgetItem(tr("是否通过")));
    ui->output->setItem(0,4,new QTableWidgetItem(tr("学分")));

    ifstream get_course ;
    get_course.open("F:\\qtprogramme\\kechengsheji\\data\\module.txt");
    if(!get_course){
        QMessageBox::information(this,"ERROR","没有module文件！\n");
        return;
    }
    string id,name,credit,time,type;
    get_course>>id>>name>>credit>>time>>type;
    while(get_course>>id>>name>>credit>>time>>type){
        const char* c_s3 = credit.c_str();
        QString _credit=QString::fromLocal8Bit(c_s3);
        const char* c_s2 = id.c_str();
        QString _id=QString::fromLocal8Bit(c_s2);
        if(_id=="#END")break;
        const char* c_s = name.c_str();
        QString _name=QString::fromLocal8Bit(c_s);
        const char* c_s1 = time.c_str();
        QString _time=QString::fromLocal8Bit(c_s1);
        const char* c_s4 = type.c_str();
        QString _type=QString::fromLocal8Bit(c_s4);

        Course course(_id,_name,_credit,_time,_type);
        m_courses.push_back(course);
    }
    get_course.close();

}

outputscore::~outputscore()
{
    delete ui;
}


void outputscore::initial()
{
    QString __tr="学号为\**/";
    __tr.append(m_id_Edit);
    __tr.append("\\**/的同学的成绩如下");
    ui->label->setText(__tr);

    ifstream get_score ;
    get_score.open("F:\\qtprogramme\\kechengsheji\\data\\score.txt");
    if(!get_score){
        QMessageBox::information(this,"ERROR","没有score文件！\n");
        return;
    }

    int j=0;
    string _id_,_name_,_course_,_score_;
    get_score>>_id_>>_name_>>_course_>>_score_;

    while(get_score>>_id_>>_name_>>_course_>>_score_){
        const char* c_name = _name_.c_str();
        QString _name=QString::fromLocal8Bit(c_name);
        const char* c_id = _id_.c_str();

        QString _id=QString::fromLocal8Bit(c_id);
        if(_id=="#END")break;
        const char* c_course = _course_.c_str();
        QString _course=QString::fromLocal8Bit(c_course);
        const char* c_score = _score_.c_str();
        QString _score=QString::fromLocal8Bit(c_score);
        if(m_id_Edit==_id){

            m_stu_course[++m_course_size]=_course;
            m_stu_score[m_course_size]=_score;
            j++;
        }
        else if(j)break;
    }
    get_score.close();


    int row=0;
    for(int i=0;i<m_courses._size();i++){
        if(m_stu_course[row]==m_courses[i]._name()){

            string id1=m_courses[i]._ID().toStdString();
            string name1=m_courses[i]._name().toStdString();
            string credit1=m_courses[i]._credit().toStdString();
            string score1=m_stu_score[row].toStdString();

            const char* c_id1 = id1.c_str();
            const char* c_name1 = name1.c_str();
            const char* c_credit1 = credit1.c_str();
            const char* c_score1 = score1.c_str();

            ui->output->setItem(++row,0,new QTableWidgetItem(tr(c_id1)));
            ui->output->setItem(row,1,new QTableWidgetItem(tr(c_name1)));
            ui->output->setItem(row,2,new QTableWidgetItem(tr(c_score1)));
            ui->output->setItem(row,4,new QTableWidgetItem(tr(c_credit1)));

            int s=m_stu_score[row-1].toInt();
            if(s<60)
                ui->output->setItem(row,3,new QTableWidgetItem(tr("未通过")));
            else
                ui->output->setItem(row,3,new QTableWidgetItem(tr("通过")));
            i=0;
        }
    }
    //显示总学分
    int all_credit {0};
    QString cre;
    for(int i=1;i<=row;i++)
        if(ui->output->item(i,3)->text()=="通过"){
            cre=ui->output->item(i,4)->text();
            all_credit+=cre.toInt();
        }
    cre.setNum(all_credit);
    string _cre=cre.toStdString();
    const char* c_cre = _cre.c_str();
    ui->output->setItem(row+1,4,new QTableWidgetItem(tr(c_cre)));

}
void outputscore::on_pushButton_clicked()
{
    this->hide();
}
