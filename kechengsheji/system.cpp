#include "system.h"
#include "ui_system.h"
#include<fstream>
#include<QString>
#include<QMessageBox>
#include<stdlib.h>
using namespace std;
SYSTEM::SYSTEM(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SYSTEM),
    m_s1(0),
    m_s2(0),
    m_s3(0)
{
    ui->setupUi(this);
    setStyleSheet("border-image:url(:/yiyiyi.jpg);");
    ui->search_1->setPlaceholderText(" Search... ");
    ui->table_teacher->setRowCount(20);
    ui->table_teacher->setColumnCount(6);
    ui->table_teacher->setAlternatingRowColors(true);
    ui->table_teacher->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_teacher->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->table_teacher->setItem(0,0,new QTableWidgetItem(tr("工号")));
    ui->table_teacher->setItem(0,1,new QTableWidgetItem(tr("姓名")));
    ui->table_teacher->setItem(0,2,new QTableWidgetItem(tr("授课1")));
    ui->table_teacher->setItem(0,3,new QTableWidgetItem(tr("授课2")));
    ui->table_teacher->setItem(0,4,new QTableWidgetItem(tr("授课3")));
    ui->table_teacher->setItem(0,5,new QTableWidgetItem(tr("授课4")));

    ui->search_2->setPlaceholderText(" Search... ");
    ui->table_student->setRowCount(100);
    ui->table_student->setColumnCount(4);
    ui->table_student->setAlternatingRowColors(true);
    ui->table_student->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_student->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->table_student->setItem(0,0,new QTableWidgetItem(tr("学号")));
    ui->table_student->setItem(0,1,new QTableWidgetItem(tr("姓名")));
    ui->table_student->setItem(0,2,new QTableWidgetItem(tr("班级")));
    ui->table_student->setItem(0,3,new QTableWidgetItem(tr("专业")));

    ui->search_3->setPlaceholderText(" Search... ");
    ui->table_course->setRowCount(30);
    ui->table_course->setColumnCount(5);
    ui->table_course->setAlternatingRowColors(true);
    ui->table_course->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_course->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->table_course->setItem(0,0,new QTableWidgetItem(tr("课程编号")));
    ui->table_course->setItem(0,1,new QTableWidgetItem(tr("课程名称")));
    ui->table_course->setItem(0,2,new QTableWidgetItem(tr("学分")));
    ui->table_course->setItem(0,3,new QTableWidgetItem(tr("学时")));
    ui->table_course->setItem(0,4,new QTableWidgetItem(tr("性质")));

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
        m_sys_course.push_back(course);
    }
    get_course.close();


    m_s3=m_sys_course._size();

    for(int row=1;row<m_sys_course._size();row++){

        string id=m_sys_course[row-1]._ID().toStdString();
        string name=m_sys_course[row-1]._name().toStdString();
        string credit=m_sys_course[row-1]._credit().toStdString();
        string time=m_sys_course[row-1]._time().toStdString();
        string type=m_sys_course[row-1]._charactor().toStdString();

        const char* c_s = id.c_str();
        const char* c_s1 = name.c_str();
        const char* c_s2 = credit.c_str();
        const char* c_s3 = time.c_str();
        const char* c_s4 = type.c_str();

        ui->table_course->setItem(row,0,new QTableWidgetItem(tr(c_s)));
        ui->table_course->setItem(row,1,new QTableWidgetItem(tr(c_s1)));
        ui->table_course->setItem(row,2,new QTableWidgetItem(tr(c_s2)));
        ui->table_course->setItem(row,3,new QTableWidgetItem(tr(c_s3)));
        ui->table_course->setItem(row,4,new QTableWidgetItem(tr(c_s4)));


    }
}

SYSTEM::~SYSTEM()
{
    delete ui;
}



void SYSTEM::initial_show()
{
    m_s1=m_sys_teacher._size();
    m_s2=m_sys_student._size();

    for(int row=1;row<m_sys_teacher._size();row++){

        if(m_sys_teacher[row-1]._course1()!="none"){
            string course=m_sys_teacher[row-1]._course1().toStdString();
            const char* c_s = course.c_str();
            ui->table_teacher->setItem(row,2,new QTableWidgetItem(tr(c_s)));
        }
        else ui->table_teacher->setItem(row,2,new QTableWidgetItem(tr(" ")));

        if(m_sys_teacher[row-1]._course2()!="none"){
            string course=m_sys_teacher[row-1]._course2().toStdString();
            const char* c_s = course.c_str();
            ui->table_teacher->setItem(row,3,new QTableWidgetItem(tr(c_s)));
        }
        else ui->table_teacher->setItem(row,3,new QTableWidgetItem(tr(" ")));

        if(m_sys_teacher[row-1]._course3()!="none"){
            string course=m_sys_teacher[row-1]._course3().toStdString();
            const char* c_s = course.c_str();
            ui->table_teacher->setItem(row,4,new QTableWidgetItem(tr(c_s)));
        }
        else ui->table_teacher->setItem(row,4,new QTableWidgetItem(" "));
        if(m_sys_teacher[row-1]._course4()!="none"){
            string course=m_sys_teacher[row-1]._course4().toStdString();
            const char* c_s = course.c_str();
            ui->table_teacher->setItem(row,5,new QTableWidgetItem(tr(c_s)));
        }
        else ui->table_teacher->setItem(row,5,new QTableWidgetItem(" "));



        string id=m_sys_teacher[row-1]._ID().toStdString();
        string name=m_sys_teacher[row-1]._name().toStdString();

        const char* c_s = id.c_str();
        const char* c_s1 = name.c_str();

        ui->table_teacher->setItem(row,0,new QTableWidgetItem(tr(c_s)));
        ui->table_teacher->setItem(row,1,new QTableWidgetItem(tr(c_s1)));

    }

    for(int row=1;row<m_sys_student._size();row++){

        string id=m_sys_student[row-1]._ID().toStdString();
        string name=m_sys_student[row-1]._name().toStdString();
        string cla=m_sys_student[row-1]._cla().toStdString();
        string major=m_sys_student[row-1]._major().toStdString();

        const char* c_s = id.c_str();
        const char* c_s1 = name.c_str();
        const char* c_s2 = cla.c_str();
        const char* c_s3 = major.c_str();

        ui->table_student->setItem(row,0,new QTableWidgetItem(tr(c_s)));
        ui->table_student->setItem(row,1,new QTableWidgetItem(tr(c_s1)));
        ui->table_student->setItem(row,2,new QTableWidgetItem(tr(c_s2)));
        ui->table_student->setItem(row,3,new QTableWidgetItem(tr(c_s3)));
    }

}



void SYSTEM::on_search_1_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->table_teacher->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->table_teacher->showRow(row);
        }
        return ;
    }

    int rowCount = ui->table_teacher->rowCount();
    int columnCount = ui->table_teacher->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->table_teacher->item(row,column)){
                rowData += ui->table_teacher->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->table_teacher->showRow(row);
            }
            else{
                ui->table_teacher->hideRow(row);
            }
        }
        else{
            ui->table_teacher->hideRow(row);
        }
    }
}

void SYSTEM::on_search_2_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->table_student->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->table_student->showRow(row);
        }
        return ;
    }

    int rowCount = ui->table_student->rowCount();
    int columnCount = ui->table_student->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->table_student->item(row,column)){
                rowData += ui->table_student->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->table_student->showRow(row);
            }
            else{
                ui->table_student->hideRow(row);
            }
        }
        else{
            ui->table_student->hideRow(row);
        }
    }
}

void SYSTEM::on_search_3_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->table_course->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->table_course->showRow(row);
        }
        return ;
    }

    int rowCount = ui->table_course->rowCount();
    int columnCount = ui->table_course->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->table_course->item(row,column)){
                rowData += ui->table_course->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->table_course->showRow(row);
            }
            else{
                ui->table_course->hideRow(row);
            }
        }
        else{
            ui->table_course->hideRow(row);
        }
    }

}


void SYSTEM::on_add_1_clicked()
{
    //添加行
    int currentRow = ui->table_teacher->currentRow();
    ui->table_teacher->insertRow(currentRow + 1);
    for(int i=0;i<6;i++){
    ui->table_teacher->setItem(currentRow+1,i,new QTableWidgetItem(""+QString::number(currentRow+1)));}
    m_s1+=1;
}

void SYSTEM::on_del_1_clicked()
{
    int currentRow = ui->table_teacher->currentRow();
    ui->table_teacher->removeRow(currentRow);
    m_s1--;
}



void SYSTEM::on_add_2_clicked()
{
    //添加行
    int currentRow = ui->table_student->currentRow();
    ui->table_student->insertRow(currentRow + 1);
    for(int i=0;i<6;i++){
    ui->table_student->setItem(currentRow+1,i,new QTableWidgetItem(""+QString::number(currentRow+1)));}
    m_s2+=1;
}

void SYSTEM::on_del_2_clicked()
{
    //添加行
    int currentRow = ui->table_student->currentRow();
    ui->table_student->removeRow(currentRow);
    m_s2--;
}



void SYSTEM::on_add_3_clicked()
{
    //添加行
    int currentRow = ui->table_course->currentRow();
    ui->table_course->insertRow(currentRow + 1);
    for(int i=0;i<6;i++){
    ui->table_course->setItem(currentRow+1,i,new QTableWidgetItem(""+QString::number(currentRow+1)));}
    m_s3+=1;
}

void SYSTEM::on_del_3_clicked()
{
    //添加行
    int currentRow = ui->table_course->currentRow();
    ui->table_course->removeRow(currentRow);
    m_s3--;
}

void SYSTEM::on_save_1_clicked()
{
    ofstream o_stu;
    o_stu.open("F:\\qtprogramme\\kechengsheji\\data\\new_stu.txt");
    for(int row=0;row<m_s2;row++){

        QString data1=ui->table_student->item(row,0)->text();
        QString data2=ui->table_student->item(row,1)->text();
        QString data3=ui->table_student->item(row,2)->text();
        QString data4=ui->table_student->item(row,3)->text();

        string _1=data1.toStdString();
        string _2=data2.toStdString();
        string _3=data3.toStdString();
        string _4=data4.toStdString();

        o_stu<<_1<<" "<<_2<<" "<<_3<<" "<<_4<<endl;
    }
    o_stu.close();




}

void SYSTEM::on_save_2_clicked()
{
    ofstream o_teacher;
    o_teacher.open("F:\\qtprogramme\\kechengsheji\\data\\new_teacher.txt");
    for(int row=0;row<m_s1;row++){


        QString data1=ui->table_teacher->item(row,0)->text();
        QString data2=ui->table_teacher->item(row,1)->text();
        string _1=data1.toStdString();
        string _2=data2.toStdString();
        o_teacher<<_1<<" "<<_2;
        if(!(ui->table_teacher->item(row,2)->text().isEmpty())){
            QString data3=ui->table_teacher->item(row,2)->text();
            string _3=data3.toStdString();
            o_teacher<<" "<<_3;
        }
        else o_teacher<<endl;
        if(!(ui->table_teacher->item(row,3)->text().isEmpty())){
            QString data4=ui->table_teacher->item(row,3)->text();
            string _4=data4.toStdString();
            o_teacher<<" "<<_4;
        }
        else o_teacher<<endl;

        if(!(ui->table_teacher->item(row,4)->text().isEmpty())){
            QString data5=ui->table_teacher->item(row,4)->text();
            string _5=data5.toStdString();
            o_teacher<<" "<<_5;
        }
        else o_teacher<<endl;

        if(!(ui->table_teacher->item(row,5)->text().isEmpty())){    //????
            QString data6=ui->table_teacher->item(row,5)->text();
            string _6=data6.toStdString();
            o_teacher<<" "<<_6<<endl;
        }
        else o_teacher<<endl;

    }
    o_teacher.close();
}

void SYSTEM::on_save_3_clicked()
{

    ofstream o_course;
    o_course.open("F:\\qtprogramme\\kechengsheji\\data\\new_course.txt");
    for(int row=0;row<m_s3;row++){
        QString data1=ui->table_course->item(row,0)->text();
        QString data2=ui->table_course->item(row,1)->text();
        QString data3=ui->table_course->item(row,2)->text();
        QString data4=ui->table_course->item(row,3)->text();
        QString data5=ui->table_course->item(row,4)->text();

        string _1=data1.toStdString();
        string _2=data2.toStdString();
        string _3=data3.toStdString();
        string _4=data4.toStdString();
       string _5=data5.toStdString();
        o_course<<_1<<" "<<_2<<" "<<_3<<" "<<_4<<" "<<_5<<endl;
    }
    o_course.close();
}
