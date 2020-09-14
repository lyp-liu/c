#include "course_score.h"
#include "ui_course_score.h"
#include<fstream>
#include<QMessageBox>
#include<stdlib.h>
using namespace std;
course_score::course_score(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::course_score)
{
    ui->setupUi(this);

    setStyleSheet("border-image:url(:/yiyiyi.jpg);");
    m_sstudent=new student_function;
    m_operator=new operate_score();
    m_system=new SYSTEM();

    ifstream get_student;
    get_student.open("F:\\qtprogramme\\kechengsheji\\data\\student.txt");
    if(!get_student){
        QMessageBox::information(this,"ERROR","没有该文件！\n");
        return;
    }
    string id,name,class_,major;
    get_student>>id>>name>>class_>>major;
    while(get_student>>id>>name>>class_>>major){
        const char* c_s3 = class_.c_str();
        QString _class_=QString::fromLocal8Bit(c_s3);
        const char* c_s2 = id.c_str();
        QString _id=QString::fromLocal8Bit(c_s2);
        if(_id=="#END")break;
        const char* c_s = name.c_str();
        QString _name=QString::fromLocal8Bit(c_s);
        const char* c_s1 = major.c_str();
        QString _major=QString::fromLocal8Bit(c_s1);

        Student student(_id,_name,_class_,_major);
        m_students.push_back(student);
    }
    get_student.close();


    ifstream get_teacher;
    get_teacher.open("F:\\qtprogramme\\kechengsheji\\data\\staff.txt");
    if(!get_teacher){
        QMessageBox::information(this,"ERROR","没有该文件！\n");
        return;
    }
    string _id,_name,_course1,_course2,_course3,_course4;
    get_teacher>>_id>>_name>>_course1;
    while(get_teacher>>_id>>_name>>_course1>>_course2>>_course3>>_course4){
        const char* c_id_=_id.c_str();
        QString _id_=QString::fromLocal8Bit(c_id_);
        const char* c_name_=_name.c_str();
        QString _name_=QString::fromLocal8Bit(c_name_);
        const char* c_course1_=_course1.c_str();
        QString _course1_=QString::fromLocal8Bit(c_course1_);
        const char* c_course2_=_course2.c_str();
        QString _course2_=QString::fromLocal8Bit(c_course2_);
        const char* c_course3_=_course3.c_str();
        QString _course3_=QString::fromLocal8Bit(c_course3_);
        const char* c_course4_ = _course4.c_str();
        QString _course4_=QString::fromLocal8Bit(c_course4_);
        Teacher teacher(_id_,_name_,_course1_,_course2_,_course3_,_course4_);
        m_teachers.push_back(teacher);

    }
}

course_score::~course_score()
{
    delete ui;
    delete m_sstudent;
    delete m_operator;
    delete m_system;
}

void course_score::on_login_clicked()
{
   accountdata=ui->usename->text();

   bool Is_student=false;
   bool Is_teacher=false;
   for(int i=0;i<m_students._size();i++)
       if(accountdata==m_students[i]._ID())Is_student=true;

   for(int i=0;i<m_teachers._size();i++)
       if(accountdata==m_teachers[i]._ID())Is_teacher=true;

   if(Is_student){
       m_sstudent->get_id_accountdata(accountdata);
       m_sstudent->show();
   }
   else if(Is_teacher){
       for(int i=0;i<m_teachers._size();i++)
           if(accountdata==m_teachers[i]._ID()){

               m_operator->initial_course(m_teachers[i]._course1(),m_teachers[i]._course2(),m_teachers[i]._course3(),m_teachers[i]._course4());

                m_operator->initial_show();


               m_operator->show();
           }
   }
   else if(accountdata=="####"){

       m_system->write(m_teachers,m_students);

       m_system->initial_show();

       m_system->show();
   }
   else QMessageBox::information(this,"ERROR","该用户名不存在！\n");
}
