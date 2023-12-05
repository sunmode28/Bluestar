#ifndef CONTEXT_H
#define CONTEXT_H

#include <QString>



class Context
{
public:
    Context();
    void setIsv(bool b);
    void setName(QString name);
    void setValue(QString value);
    bool getIsv();
    QString getName();
    QString getValue();
private:
    bool isv;
    QString name;
    QString value;
};

#endif // CONTEXT_H
