#ifndef MYQLINEEDIT_H
#define MYQLINEEDIT_H

#include <QLineEdit>
#include <QObject>

class MyQlineEdit : public QLineEdit
{
    Q_OBJECT

public:
    void getText();

signals:

};

#endif // MYQLINEEDIT_H
