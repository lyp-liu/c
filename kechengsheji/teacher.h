#ifndef TEACHER_H
#define TEACHER_H
#include<QString>
#include"course.h"
#include"teacher.h"

class Teacher{
    QString m_ID, m_name, m_course1,m_course2,m_course3,m_course4;
public:
    Teacher(const QString& ID="00", const QString& name="none", const QString& course1="none",const QString& course2="none",const QString& course3="none",const QString& course4="none")
        :m_ID(ID),
          m_name(name),
          m_course1(course1),
          m_course2(course2),
           m_course4(course4),
          m_course3(course3)

    { }

    Teacher(const Teacher&)=delete;
    const QString& _ID()const {return m_ID;}
    const QString& _name()const {return m_name;}
    const QString& _course1()const {return m_course1;}
    const QString& _course2()const {return m_course2;}
    const QString& _course3()const {return m_course3;}
    const QString& _course4()const {return m_course4;}
};







#endif // TEACHER_H
