#ifndef COURSE_H
#define COURSE_H

#include<QString>

class Course{
private:
    QString m_name,m_ID,m_credit,m_time,m_Isrequired;
public:
    Course(const QString& ID="00", const QString& name="none", const QString& credit="00", const QString& time="00", const QString& Isrequired="none")
        :m_ID(ID),
          m_name(name),
          m_credit(credit),
          m_time(time),
          m_Isrequired(Isrequired)
    { }

    Course(const Course&)=delete;
    ~Course(){}
    const QString& _ID()const {return m_ID;}
    const QString& _name()const {return m_name;}
    const QString& _credit()const {return m_credit;}
    const QString& _time()const  {return m_time;}
    const QString& _charactor()const {return m_Isrequired;}
};

#endif // COURSE_H
