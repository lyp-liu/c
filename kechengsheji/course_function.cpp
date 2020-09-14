#include "course_function.h"
#include "ui_course_function.h"
#include<fstream>
#include<QString>
#include<QMessageBox>
#include<stdlib.h>
using namespace std;
course_function::course_function(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::course_function),
  m_mycourse_row(1)
{
    ui->setupUi(this);
    setStyleSheet("border-image:url(:/yiyiyi.jpg);");
    ui->search->setPlaceholderText(" Search... ");
    ui->allcourse->setRowCount(30);
    ui->allcourse->setColumnCount(5);
    ui->allcourse->setAlternatingRowColors(true);
    ui->allcourse->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->allcourse->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->allcourse->setItem(0,0,new QTableWidgetItem(tr("课程编号")));
    ui->allcourse->setItem(0,1,new QTableWidgetItem(tr("课程名称")));
    ui->allcourse->setItem(0,2,new QTableWidgetItem(tr("学分")));
    ui->allcourse->setItem(0,3,new QTableWidgetItem(tr("学时")));
    ui->allcourse->setItem(0,4,new QTableWidgetItem(tr("课程类别")));

    ui->search_2->setPlaceholderText(" Search... ");
    ui->mycourse->setRowCount(30);
    ui->mycourse->setColumnCount(5);
    ui->mycourse->setAlternatingRowColors(true);
    ui->mycourse->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mycourse->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->mycourse->setItem(0,0,new QTableWidgetItem(tr("课程编号")));
    ui->mycourse->setItem(0,1,new QTableWidgetItem(tr("课程名称")));
    ui->mycourse->setItem(0,2,new QTableWidgetItem(tr("学分")));
    ui->mycourse->setItem(0,3,new QTableWidgetItem(tr("学时")));
    ui->mycourse->setItem(0,4,new QTableWidgetItem(tr("课程类别")));

    ifstream get_course ;
    get_course.open("F:\\qtprogramme\\kechengsheji\\data\\module.txt");
    if(!get_course){
        QMessageBox::information(this,"ERROR","没有该文件！\n");
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

    for(int row=1;row<m_courses._size();row++){

        string id=m_courses[row-1]._ID().toStdString();
        string name=m_courses[row-1]._name().toStdString();
        string credit=m_courses[row-1]._credit().toStdString();
        string time=m_courses[row-1]._time().toStdString();
        string type=m_courses[row-1]._charactor().toStdString();

        const char* c_s = id.c_str();
        const char* c_s1 = name.c_str();
        const char* c_s2 = credit.c_str();
        const char* c_s3 = time.c_str();
        const char* c_s4 = type.c_str();

        ui->allcourse->setItem(row,0,new QTableWidgetItem(tr(c_s)));
        ui->allcourse->setItem(row,1,new QTableWidgetItem(tr(c_s1)));
        ui->allcourse->setItem(row,2,new QTableWidgetItem(tr(c_s2)));
        ui->allcourse->setItem(row,3,new QTableWidgetItem(tr(c_s3)));
        ui->allcourse->setItem(row,4,new QTableWidgetItem(tr(c_s4)));

    }
}

course_function::~course_function()
{
    delete ui;
}

void course_function::on_search_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->allcourse->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->allcourse->showRow(row);
        }
        return ;
    }

    int rowCount = ui->allcourse->rowCount();
    int columnCount = ui->allcourse->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->allcourse->item(row,column)){
                rowData += ui->allcourse->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->allcourse->showRow(row);
            }
            else{
                ui->allcourse->hideRow(row);
            }
        }
        else{
            ui->allcourse->hideRow(row);
        }
    }

}

void course_function::on_Btn_function_1_clicked()
{
    QString id,name,credit,time,type;
    int currentRow = ui->allcourse->currentRow();
    id=ui->allcourse->item(currentRow,0)->text();
    name=ui->allcourse->item(currentRow,1)->text();
    credit=ui->allcourse->item(currentRow,2)->text();
    time=ui->allcourse->item(currentRow,3)->text();
    type=ui->allcourse->item(currentRow,4)->text();

    Course course(id,name,credit,time,type);
    m_mycourse.push_back(course);

    ui->allcourse->removeRow(currentRow);

    string _id=id.toStdString();
    string _name=name.toStdString();
    string _credit=credit.toStdString();
    string _time=time.toStdString();
    string _type=type.toStdString();

    const char* c_id = _id.c_str();
    const char* c_name = _name.c_str();
    const char* c_credit = _credit.c_str();
    const char* c_time = _time.c_str();
    const char* c_type = _type.c_str();

    ui->mycourse->setItem(m_mycourse_row,0,new QTableWidgetItem(tr(c_id)));
    ui->mycourse->setItem(m_mycourse_row,1,new QTableWidgetItem(tr(c_name)));
    ui->mycourse->setItem(m_mycourse_row,2,new QTableWidgetItem(tr(c_credit)));
    ui->mycourse->setItem(m_mycourse_row,3,new QTableWidgetItem(tr(c_time)));
    ui->mycourse->setItem(m_mycourse_row,4,new QTableWidgetItem(tr(c_type)));

    m_mycourse_row++;
}

void course_function::on_Btn_function_2_clicked()
{
    this->hide();
}

void course_function::on_search_2_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->mycourse->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->mycourse->showRow(row);
        }
        return ;
    }

    int rowCount = ui->mycourse->rowCount();
    int columnCount = ui->mycourse->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->mycourse->item(row,column)){
                rowData += ui->mycourse->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->mycourse->showRow(row);
            }
            else{
                ui->mycourse->hideRow(row);
            }
        }
        else{
            ui->mycourse->hideRow(row);
        }
    }
}

void course_function::on_Btn_function_3_clicked()
{
    int currentRow = ui->mycourse->currentRow();
    ui->mycourse->removeRow(currentRow);
    m_mycourse.erase(currentRow-1);
}
