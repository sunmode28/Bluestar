#include "widget.h"
#include "QDebug"

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
    sa->setBackgroundRole(QPalette::Light);
    main_layout->addWidget(sa);//把滑动区域添加到主页面布局
    QFrame* line=new QFrame();
    line->setFrameShape(QFrame::HLine);//
    main_layout->addWidget(line);
    main_layout->addWidget(insert_button);
    main_layout->setStretchFactor(sa,9);//
    main_layout->setStretchFactor(insert_button,1);
    setInsert_Button();
    getContextWidget();//把所有数据提取出来
    context_widget->setFixedSize(this->width()-40,30*context_list.length());//设置QScrollarea内的窗体大小防止出现控件压缩
    setContextData();
}
Widget::~Widget()
{
}
void Widget::getContextWidget(){
    sa->setWidget(context_widget);//把滑动区域的内容窗体添加到滑动区域中
    context_widget->setLayout(context_layout);//把滑动区域的内容布局添加到内容窗体中
    QString path=getShellRP();//调用方法获取命令执行后的返回结果
    QStringList ql=getPathList(path);//调用方法获取处理后的数据
    QString str;
    foreach (str, ql) {
        QStringList sl=str.split("=");
        Context *con=new Context();
        if(sl[0]!=""&&sl[1]!=""){//判断是否有名字为空的
            con->setName(sl[0]);
            con->setValue(sl[1]);
            context_list.append(con);
        }
    }
}
QStringList Widget::getPathList(QString path){
    return (path.split("\n"));
}
void Widget::init(){
    this->setWindowIcon(QIcon(":/pic/image/icon.png"));
    this->setWindowTitle("蓝星-环境变量");
//    this->setStyleSheet("background-color:green");
    main_layout=new QVBoxLayout(this);//初始化主界面的布局
    sa=new QScrollArea();//初始化滑动区域
    context_widget=new QWidget();//初始化滑动区内容窗体
    context_layout=new QVBoxLayout();//初始化滑动区域内容窗体的布局
    insert_button=new QWidget();//初始化添加页面

    this->setFixedSize(1200,800);//固定窗体大小
}
QString Widget::getShellRP(){
    ps=new QProcess;
    //执行命令
    ps->start("bash",QStringList()<<"-c"<<"printenv");
    ps->waitForStarted();
    ps->waitForFinished();
    //获取命令的执行结果
    QString path=QString::fromLocal8Bit(ps->readAllStandardOutput());//获取path
//    putenv("PATH");

    return path;
}

void Widget::setContextData(){
    foreach (auto context_temp, context_list) {
        QHBoxLayout* qbl_temp=new QHBoxLayout();//创建每条数据的布局
//        QCheckBox *qcb=new QCheckBox();//设置多选框用来删除
        QLineEdit *name_temp=new QLineEdit();//创建name条
        QLineEdit *value_temp=new QLineEdit();//创建value条
        context_layout->addLayout(qbl_temp);
//        qcb->setCheckState(Qt::CheckState::Unchecked);//设置是否选中
        name_temp->setText(context_temp->getName());
        name_temp->setDisabled(true);//设置是否可修改
        value_temp->setText(context_temp->getValue());
        value_temp->setFocusPolicy(Qt::NoFocus);


//        qbl_temp->addWidget(qcb);
        qbl_temp->addWidget(name_temp);
        qbl_temp->addWidget(value_temp);
        //设置比例
//        qbl_temp->setStretchFactor(qcb,1);
        qbl_temp->setStretchFactor(name_temp,1);
        qbl_temp->setStretchFactor(value_temp,1);


    }

}

void Widget::setInsert_Button(){
    insert_button_layout=new QHBoxLayout();
    insert_button->setLayout(insert_button_layout);
    btn1=new QPushButton("刷新");
    btn2=new QPushButton("生成");
    addName=new MyQlineEdit();
    addValue=new MyQlineEdit();
    btn1->setStyleSheet("background-color:Orange");
    btn2->setStyleSheet("background-color:green");
    addName->setPlaceholderText("Name");
    addValue->setPlaceholderText("Value");

    btn2->setToolTip("添加后若不显示请在命令行执行 source /etc/profile");


    insert_button_layout->addWidget(btn1);
    insert_button_layout->addWidget(btn2);
    insert_button_layout->addWidget(addName);
    insert_button_layout->addWidget(addValue);
    insert_button_layout->setStretchFactor(btn1,1);
    insert_button_layout->setStretchFactor(btn2,1);

    insert_button_layout->setStretchFactor(addName,4);
    insert_button_layout->setStretchFactor(addValue,4);

    connect(btn1,&QPushButton::clicked,this,&Widget::Refresh);
    connect(btn2,&QPushButton::clicked,this,&Widget::setOv);

}
void Widget::Refresh(){
    context_list.clear();
    clearLayout(context_layout);
    getContextWidget();
//    context_widget->setFixedSize(this->width()-40,30*context_list.length());//设置QScrollarea内的窗体大小防止出现控件压缩
    setContextData();
}
void Widget::setOv(){

    QMessageBox mb;
    addName->text();
    addValue->text();
    QFile file("/etc/profile");
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        qDebug()<<"没有权限请用sudo 命令或者root用户执行";
        mb.warning(this,"警告","执行失败",QMessageBox::Close);
        mb.show();
    }else{
    QTextStream out(&file);
    out<<"export "+addName->text()+"="+addValue->text()+"\n";
    system("echo '/etc/profile' >>bash -c source ");

    if(out.status()==QTextStream::Ok&& addName->text()!=""&&addValue->text()!=""){
        mb.about(this,"执行成功","执行成功");
        mb.show();
    }else{
        mb.warning(this,"警告","执行失败",QMessageBox::Close);
        mb.show();
    }
    }

    file.close();
}
void Widget::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget(); // 删除QWidget
        delete item;           // 删除QLayoutItem
    }
}
