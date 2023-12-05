#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QScrollArea>
#include <Context.h>
#include <myqlineedit.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QList>
#include <QString>
#include <QPushButton>
#include <QCheckBox>
#define MAIN_W 600
#define MAIN_H 600

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    void init();
    void getContextWidget();
    void setContextData();
    void setInsert_Button();
    QString getShellRP();
    QStringList getPathList(QString path);
    void clearLayout(QLayout *layout);
    ~Widget();
public slots:
    void setOv();
    void Refresh();
private:
    QProcess* ps;
    QVBoxLayout* main_layout;//主窗体的布局，垂直
    QScrollArea *sa;//滑动区域
    QWidget *context_widget;//内容窗体
    QVBoxLayout* context_layout;//内容布局，垂直
    QList<Context*> context_list;//内容列表
    QHBoxLayout *insert_button_layout;//添加页面的布局文件
    QWidget *insert_button;//添加页面
    QLine *ql;
    QPushButton* btn1;
    QPushButton* btn2;
    MyQlineEdit* addName;
    MyQlineEdit* addValue;
    QString rePath;

};

#endif // WIDGET_H
