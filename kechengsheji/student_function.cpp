#include "student_function.h"
#include "ui_student_function.h"

student_function::student_function(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::student_function)
{
    ui->setupUi(this);
    setStyleSheet("border-image:url(:/yiyiyi.jpg);");
    m_scourse=new course_function();
    m_show=new outputscore();
}

student_function::~student_function()
{
    delete ui;
    delete m_scourse;
    delete m_show;
}

void student_function::on_function_del_clicked()
{
    m_scourse->show();
}

void student_function::on_search_score_clicked()
{
    m_show->set_data_id(m_id_user);
    m_show->initial();
    m_show->show();
}

void student_function::on_search_score_2_clicked()
{
    this->hide();
}
