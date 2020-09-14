#include "operate_score.h"
#include "ui_operate_score.h"
#include<fstream>
#include<QString>
#include<QMessageBox>
#include<stdlib.h>
#include<cmath>

using namespace std;

operate_score::operate_score(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::operate_score),
    m_ave1(0),
    m_ave2(0),
    m_ave3(0),
    m_ave4(0),
    m_BZC1(0),
    m_BZC2(0),
    m_BZC3(0),
    m_BZC4(0),
    m_JGL1(0),
    m_JGL2(0),
    m_JGL3(0),
    m_JGL4(0),
    m_s1(0),
    m_s2(0),
    m_s3(0),
    m_s4(0)
{
    ui->setupUi(this);
    setStyleSheet("border-image:url(:/yiyiyi.jpg);");
    headers<<QStringLiteral("ID")<<QStringLiteral("Name")<<QStringLiteral("Course")<<QStringLiteral("Grade");
    ui->table_1->setColumnCount(4);
    ui->table_2->setColumnCount(4);
    ui->table_3->setColumnCount(4);
    ui->table_4->setColumnCount(4);
    ui->table_1->setHorizontalHeaderLabels(headers);
    ui->table_2->setHorizontalHeaderLabels(headers);
    ui->table_3->setHorizontalHeaderLabels(headers);
    ui->table_4->setHorizontalHeaderLabels(headers);
    ui->search_1->setPlaceholderText(" Search... ");
    ui->table_1->setRowCount(100);

    ui->table_1->setAlternatingRowColors(true);
    ui->table_1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->search_2->setPlaceholderText(" Search... ");
    ui->table_2->setRowCount(100);

    ui->table_2->setAlternatingRowColors(true);
    ui->table_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    ui->search_3->setPlaceholderText(" Search... ");
    ui->table_3->setRowCount(100);

    ui->table_3->setAlternatingRowColors(true);
    ui->table_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    ui->search_4->setPlaceholderText(" Search... ");
    ui->table_4->setRowCount(100);

    ui->table_4->setAlternatingRowColors(true);
    ui->table_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    ifstream get_score ;
    get_score.open("F:\\qtprogramme\\kechengsheji\\data\\score.txt");
    if(!get_score){
        QMessageBox::information(this,"ERROR","没有score文件！\n");
        return;
    }
    string _id_,_name_,_course_,_score_;
    get_score>>_id_>>_name_>>_course_>>_score_;
    while(get_score>>_id_>>_name_>>_course_>>_score_){

        const char* c_name = _name_.c_str();
        QString _name=QString::fromLocal8Bit(c_name);
        const char* c_id = _id_.c_str();
        QString _id=QString::fromLocal8Bit(c_id);
        if(_id_=="#END")break;
        const char* c_course = _course_.c_str();
        QString _course=QString::fromLocal8Bit(c_course);
        const char* c_score = _score_.c_str();
        QString _score=QString::fromLocal8Bit(c_score);

        Score score(_id,_name,_course,_score);
        m_scores.push_back(score);

    }
    get_score.close();

    ifstream get_teacher;
    get_teacher.open("F:\\qtprogramme\\kechengsheji\\data\\staff.txt");
    if(!get_teacher){
        QMessageBox::information(this,"ERROR","没有该文件！\n");
        return;
    }
    string _id,_name,_course1,_course2,_course3,_course4;
    get_teacher>>_id>>_name>>_course1;
    while(get_teacher>>_id>>_name>>_course1>>_course2>>_course3>>_course4){
        const char* c_1_=_course1.c_str();
        const QString kemu1=QString::fromLocal8Bit(c_1_);
        const char* c_2_=_course2.c_str();
        const QString kemu2=QString::fromLocal8Bit(c_2_);
        const char* c_3_=_course3.c_str();
       const QString kemu3=QString::fromLocal8Bit(c_3_);
        const char* c_4_=_course4.c_str();
       const QString kemu4=QString::fromLocal8Bit(c_4_);
//m_operate->addTab(m_operate, m_courses[0]);

   //const QString&object1=const_cast<QString&>(kemu1);
   //const QString&object2=const_cast<QString&>(kemu2);
   //const QString&object3=const_cast<QString&>(kemu3);
   //const QString&object4=const_cast<QString&>(kemu4);
       //QString object1="&"+m_courses[0];
    //m_operate->setTabText(0,object1);
     //m_operate->setTabText(1,kemu2);
   // m_operate->setTabText(2,kemu3);
     //m_operate->setTabText(3,kemu4);
}
    for(int i=0;i<m_scores._size();i++){
        int m=m_scores[i]._score().toInt();
        for(int j=0;j<m_scores._size();j++){
            int n=m_scores[j]._score().toInt();
            if(m>n){
                Score change;
                change=m_scores[i];
                m_scores[i]=m_scores[j];
                m_scores[j]=change;
            }
        }
    }
    ui->table_1->setSortingEnabled(true);
    ui->table_2->setSortingEnabled(true);
    ui->table_3->setSortingEnabled(true);
    ui->table_4->setSortingEnabled(true);
connect(ui->table_1->horizontalHeader(),SIGNAL(sectionClicked(int )),this, SLOT(sortByColumn1(int)));
connect(ui->table_2->horizontalHeader(),SIGNAL(sectionClicked(int )),this, SLOT(sortByColumn2(int)));
connect(ui->table_3->horizontalHeader(),SIGNAL(sectionClicked(int )),this, SLOT(sortByColumn3(int)));
connect(ui->table_4->horizontalHeader(),SIGNAL(sectionClicked(int )),this, SLOT(sortByColumn4(int)));

}

operate_score::~operate_score()
{
    delete ui;
}


void operate_score::sortByColumn1(int col){

ui->table_1->sortItems(col, Qt::DescendingOrder);
}
void operate_score::sortByColumn2(int col){

ui->table_2->sortItems(col, Qt::DescendingOrder);
}
void operate_score::sortByColumn3(int col){

ui->table_3->sortItems(col, Qt::DescendingOrder);
}
void operate_score::sortByColumn4(int col){

ui->table_4->sortItems(col, Qt::DescendingOrder);
}

void operate_score::initial_show()
{
    double a[100],b[100],c[100],d[100];

    //m_operate->setTabText(0,object1);
    //m_operate->setTabText(1,object2);
   // m_operate->setTabText(2,object3);
    for(int i=0;i<m_scores._size();i++){
        if(m_scores[i]._course()==m_courses[0]){

            string id=m_scores[i]._ID().toStdString();
            string name=m_scores[i]._name().toStdString();
            string course=m_scores[i]._course().toStdString();
            string score=m_scores[i]._score().toStdString();

            const char* c_s = id.c_str();
            const char* c_s1 = name.c_str();
            const char* c_s2 = course.c_str();
            const char* c_s3 = score.c_str();

            ui->table_1->setItem(++m_s1-1,0,new QTableWidgetItem(tr(c_s)));

            ui->table_1->setItem(m_s1-1,1,new QTableWidgetItem(tr(c_s1)));
            ui->table_1->setItem(m_s1-1,2,new QTableWidgetItem(tr(c_s2)));
            ui->table_1->setItem(m_s1-1,3,new QTableWidgetItem(tr(c_s3)));

            if((m_scores[i]._score()).toInt()>=60){
                m_JGL1++;}
            m_ave1+=m_scores[i]._score().toInt();
            a[m_s1-1]=m_scores[i]._score().toInt();
        }
        else if(m_scores[i]._course()==m_courses[1]){

            string id=m_scores[i]._ID().toStdString();
            string name=m_scores[i]._name().toStdString();
            string course=m_scores[i]._course().toStdString();
            string score=m_scores[i]._score().toStdString();

            const char* c_s = id.c_str();
            const char* c_s1 = name.c_str();
            const char* c_s2 = course.c_str();
            const char* c_s3 = score.c_str();

            ui->table_2->setItem(++m_s2-1,0,new QTableWidgetItem(tr(c_s)));
            ui->table_2->setItem(m_s2-1,1,new QTableWidgetItem(tr(c_s1)));
            ui->table_2->setItem(m_s2-1,2,new QTableWidgetItem(tr(c_s2)));
            ui->table_2->setItem(m_s2-1,3,new QTableWidgetItem(tr(c_s3)));

            if((m_scores[i]._score()).toInt()>=60){
                m_JGL2++;
            }
            m_ave2+=m_scores[i]._score().toInt();
            c[m_s2-1]=m_scores[i]._score().toInt();

        }
        else if(m_scores[i]._course()==m_courses[2]){

            string id=m_scores[i]._ID().toStdString();
            string name=m_scores[i]._name().toStdString();
            string course=m_scores[i]._course().toStdString();
            string score=m_scores[i]._score().toStdString();

            const char* c_s = id.c_str();
            const char* c_s1 = name.c_str();
            const char* c_s2 = course.c_str();
            const char* c_s3 = score.c_str();

            ui->table_3->setItem(++m_s3-1,0,new QTableWidgetItem(tr(c_s)));
            ui->table_3->setItem(m_s3-1,1,new QTableWidgetItem(tr(c_s1)));
            ui->table_3->setItem(m_s3-1,2,new QTableWidgetItem(tr(c_s2)));
            ui->table_3->setItem(m_s3-1,3,new QTableWidgetItem(tr(c_s3)));

            if((m_scores[i]._score()).toInt()>=60){
                m_JGL3++;}
            m_ave3+=m_scores[i]._score().toInt();
            c[m_s3-1]=m_scores[i]._score().toInt();
        }


        else if(m_scores[i]._course()==m_courses[3]){

            string id=m_scores[i]._ID().toStdString();
            string name=m_scores[i]._name().toStdString();
            string course=m_scores[i]._course().toStdString();
            string score=m_scores[i]._score().toStdString();

            const char* c_s = id.c_str();
            const char* c_s1 = name.c_str();
            const char* c_s2 = course.c_str();
            const char* c_s3 = score.c_str();

            ui->table_4->setItem(++m_s4-1,0,new QTableWidgetItem(tr(c_s)));
            ui->table_4->setItem(m_s4-1,1,new QTableWidgetItem(tr(c_s1)));
            ui->table_4->setItem(m_s4-1,2,new QTableWidgetItem(tr(c_s2)));
            ui->table_4->setItem(m_s4-1,3,new QTableWidgetItem(tr(c_s3)));
            m_operate->setTabText(4,"111");
            if((m_scores[i]._score()).toInt()>=60){
                m_JGL4++;}
            m_ave4+=m_scores[i]._score().toInt();
            d[m_s4-1]=m_scores[i]._score().toInt();

        }
    }
    m_ave1/=m_s1;
    m_JGL1/=m_s1;
    for(int i=0;i<m_s1;i++)
        m_BZC1+=(a[i]-m_ave1)*(a[i]-m_ave1);
    m_BZC1=sqrt(m_BZC1/m_s1);

    m_ave2/=m_s2;
    m_JGL2/=m_s2;
    for(int i=0;i<m_s2;i++)
        m_BZC2+=(b[i]-m_ave2)*(b[i]-m_ave2);
    m_BZC2=sqrt(m_BZC2/m_s2);

    m_ave3/=m_s3;
    m_JGL3/=m_s3;
    for(int i=0;i<m_s3;i++)
        m_BZC1+=(c[i]-m_ave3)*(c[i]-m_ave3);
    m_BZC3=sqrt(m_BZC3/m_s3);


    m_ave4/=m_s4;
    m_JGL4/=m_s4;
    for(int i=0;i<m_s4;i++)
        m_BZC1+=(d[i]-m_ave4)*(d[i]-m_ave4);
    m_BZC4=sqrt(m_BZC4/m_s4);

}



void operate_score::initial_course(const QString &a, const QString &b, const QString &c,const QString &d)
{
    m_courses[0]=a;
    m_courses[1]=b;
    m_courses[2]=c;
    m_courses[3]=d;
}
void operate_score::on_search_1_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->table_1->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->table_1->showRow(row);
        }
        return ;
    }

    int rowCount = ui->table_1->rowCount();
    int columnCount = ui->table_1->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->table_1->item(row,column)){
                rowData += ui->table_1->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->table_1->showRow(row);
            }
            else{
                ui->table_1->hideRow(row);
            }
        }
        else{
            ui->table_1->hideRow(row);
        }
    }
}

void operate_score::on_search_2_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->table_2->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->table_2->showRow(row);
        }
        return ;
    }

    int rowCount = ui->table_2->rowCount();
    int columnCount = ui->table_2->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->table_2->item(row,column)){
                rowData += ui->table_2->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->table_2->showRow(row);
            }
            else{
                ui->table_2->hideRow(row);
            }
        }
        else{
            ui->table_2->hideRow(row);
        }
    }
}

void operate_score::on_search_3_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->table_3->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->table_3->showRow(row);
        }
        return ;
    }

    int rowCount = ui->table_3->rowCount();
    int columnCount = ui->table_3->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->table_3->item(row,column)){
                rowData += ui->table_3->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->table_3->showRow(row);
            }
            else{
                ui->table_3->hideRow(row);
            }
        }
        else{
            ui->table_3->hideRow(row);
        }
    }
}

void operate_score::on_Btn_add_1_clicked()
{
    //添加行
    int currentRow = ui->table_1->currentRow();
    ui->table_1->insertRow(currentRow + 1);
    m_s1++;
}

void operate_score::on_Btn_erase_1_clicked()
{
    int currentRow = ui->table_1->currentRow();
    ui->table_1->removeRow(currentRow);
    m_s1--;
}

void operate_score::on_Btn_ave_1_clicked()
{
    QString trs;
    trs.setNum(m_ave1);
    QString r="该课程的平均成绩为：";
    r.append(trs);
    QMessageBox::information(this,"平均成绩",r);
}

void operate_score::on_Btn_pass_1_clicked()
{
    QString trs;
    trs.setNum(m_JGL1);
    QString r="该课程的及格率为:";
    r.append(trs);
    QMessageBox::information(this,"及格率:",r);
}

void operate_score::on_Btn_BZC_1_clicked()
{
    QString trs;
    trs.setNum(m_BZC1);
    QString r="该课程的标准差为:";
    r.append(trs);
    QMessageBox::information(this,"标准差:",r);
}

void operate_score::on_Btn_add_2_clicked()
{
    //添加行
    int currentRow = ui->table_2->currentRow();
    ui->table_2->insertRow(currentRow + 1);
    m_s2++;
}

void operate_score::on_Btn_erase_2_clicked()
{
    int currentRow = ui->table_2->currentRow();
    ui->table_2->removeRow(currentRow);
    m_s2--;
}

void operate_score::on_Btn_ave_2_clicked()
{
    QString trs;
    trs.setNum(m_ave2);
    QString r="该课程的平均成绩为：";
    r.append(trs);
    QMessageBox::information(this,"平均成绩",r);
}


void operate_score::on_Btn_pass_2_clicked()
{
    QString trs;
    trs.setNum(m_JGL2);
    QString r="该课程的及格率为:";
    r.append(trs);
    QMessageBox::information(this,"及格率:",r);
}

void operate_score::on_Btn_BZC_2_clicked()
{
    QString trs;
    trs.setNum(m_BZC2);
    QString r="该课程的标准差为:";
    r.append(trs);
    QMessageBox::information(this,"标准差:",r);
}

void operate_score::on_Btn_add_3_clicked()
{
    //添加行
    int currentRow = ui->table_3->currentRow();
    ui->table_3->insertRow(currentRow + 1);
    m_s3++;
}

void operate_score::on_Btn_erase_3_clicked()
{
    int currentRow = ui->table_3->currentRow();
    ui->table_3->removeRow(currentRow);
    m_s3--;
}

void operate_score::on_Btn_ave_3_clicked()
{
    QString trs;
    trs.setNum(m_ave3);
    QString r="该课程的平均成绩为：";
    r.append(trs);
    QMessageBox::information(this,"平均成绩",r);
}

void operate_score::on_Btn_pass_3_clicked()
{
    QString trs;
    trs.setNum(m_JGL3);
    QString r="该课程的及格率为:";
    r.append(trs);
    QMessageBox::information(this,"及格率:",r);
}

void operate_score::on_Btn_BZC_3_clicked()
{
    QString trs;
    trs.setNum(m_BZC3);
    QString r="该课程的标准差为:";
    r.append(trs);
    QMessageBox::information(this,"标准差:",r);
}

void operate_score::on_pushButton_clicked()
{
    for(int i=1;i<=m_s1;i++){
    QString ID=ui->table_1->item(i,0)->text();
    QString name=ui->table_1->item(i,1)->text();
    QString course=ui->table_1->item(i,2)->text();
    QString score=ui->table_1->item(i,3)->text();
    Score score_(ID,name,course,score);
    m_scores[i-1]=score_;
    }
    for(int i=1;i<=m_s2;i++){
    QString ID=ui->table_2->item(i,0)->text();
    QString name=ui->table_2->item(i,1)->text();
    QString course=ui->table_2->item(i,2)->text();
    QString score=ui->table_2->item(i,3)->text();
    Score score_(ID,name,course,score);
    m_scores[m_s1+i-1]=score_;
    }
    for(int i=1;i<=m_s3;i++){
    QString ID=ui->table_3->item(i,0)->text();
    QString name=ui->table_3->item(i,1)->text();
    QString course=ui->table_3->item(i,2)->text();
    QString score=ui->table_3->item(i,3)->text();
    Score score_(ID,name,course,score);
    m_scores[m_s1+m_s2+i-1]=score_;
    }

    m_scores.resize(m_s1+m_s2+m_s3);
    this->hide();
}

void operate_score::on_search_4_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        int rowCount=ui->table_4->rowCount();
        for(int row = 0; row < rowCount; row++)
        {
            ui->table_4->showRow(row);
        }
        return ;
    }

    int rowCount = ui->table_4->rowCount();
    int columnCount = ui->table_4->columnCount();
    for(int row = 0; row < rowCount; row++){
        QString rowData;

        for(int column = 0; column < columnCount; column++){
            if(ui->table_4->item(row,column)){
                rowData += ui->table_4->item(row,column)->text();
            }
        }
        if(!rowData.isEmpty()){
            if(rowData.contains(arg1)){
                ui->table_4->showRow(row);
            }
            else{
                ui->table_4->hideRow(row);
            }
        }
        else{
            ui->table_4->hideRow(row);
        }
    }
}

void operate_score::on_Btn_add_4_clicked()
{
    //添加行
    int currentRow = ui->table_4->currentRow();
    ui->table_4->insertRow(currentRow + 1);
    m_s4++;
}

void operate_score::on_Btn_erase_4_clicked()
{
    int currentRow = ui->table_4->currentRow();
    ui->table_4->removeRow(currentRow);
    m_s4--;
}

void operate_score::on_Btn_ave_4_clicked()
{
    QString trs;
    trs.setNum(m_ave4);
    QString r="该课程的平均成绩为：";
    r.append(trs);
    QMessageBox::information(this,"平均成绩",r);
}

void operate_score::on_Btn_pass_4_clicked()
{
    QString trs;
    trs.setNum(m_JGL4);
    QString r="该课程的及格率为:";
    r.append(trs);
    QMessageBox::information(this,"及格率:",r);
}

void operate_score::on_Btn_BZC_4_clicked()
{
    QString trs;
    trs.setNum(m_BZC4);
    QString r="该课程的标准差为:";
    r.append(trs);
    QMessageBox::information(this,"标准差:",r);
}



