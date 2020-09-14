#ifndef STUDENT_H
#define STUDENT_H
#include<QString>

class Student{
    QString m_ID,m_name,m_class,m_major;
public:
    Student(const QString&ID="00",const QString&name="none",const QString&cla="00",const QString&major="none")
        :m_ID(ID),m_name(name),m_class(cla),m_major(major)
    {  }
    Student(const Student&)=delete;
    const QString& _ID()const {return m_ID;}
    const QString& _name()const {return m_name;}
    const QString& _cla()const {return m_class;}
    const QString& _major()const {return m_major;}
};


#endif // STUDENT_H
