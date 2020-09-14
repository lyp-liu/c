#ifndef SCORE_H
#define SCORE_H
#include<QString>


class Score{
private:
    QString m_name, m_course, m_ID, m_score;
public:
    Score(const QString& ID = "00" , const QString& name = "none", const QString& course = "none", const QString& score = "00")
        : m_ID(ID),
          m_name(name),
          m_course(course),
          m_score(score)
    { }
    Score(const Score&)=delete;
    ~Score(){}
    const QString _ID()const {return m_ID;}
    const QString& _name()const {return m_name;}
    const QString& _course()const {return m_course;}
    const QString& _score()const {return m_score;}
    const Score& operator=(const Score&rhs){
        if(this!=&rhs){
            m_ID=rhs._ID();
            m_name=rhs._name();
            m_course=rhs._course();
            m_score=rhs._score();
        }
        return *this;
    }

};

#endif // SCORE_H
