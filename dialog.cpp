#include "dialog.h"
#include "ui_dialog.h"
#include "windows.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QApplication::setQuitOnLastWindowClosed(false);
    QTimer *timer=new QTimer();
    ui->setupUi(this);
    //设置窗口透明镂空和总在最前
    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setWindowFlags(this->windowFlags());
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    //连接信号与槽
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(UpdateTime()));

    //启动timer
    timer->start(100);

    //设置窗口在桌面右上部
    QRect deskRect = QApplication::desktop()->availableGeometry();
    this->move(deskRect.right()-400, deskRect.bottom()-180);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetTime(int Days,int Hours,int Minutes,int Seconds)
{
    //获取日期的每一位数
    int Days1,Days2,Days3;
    Days3=Days%10;
    Days/=10;
    Days2=Days%10;
    Days/=10;
    Days1=Days%10;
    //获取小时的每一位数
    int Hours1,Hours2;
    Hours2=Hours%10;
    Hours/=10;
    Hours1=Hours%10;
    //获取分钟的每一位数
    int Minutes1,Minutes2;
    Minutes2=Minutes%10;
    Minutes/=10;
    Minutes1=Minutes%10;
    //获取秒的每一位数
    int Seconds1,Seconds2;
    Seconds2=Seconds%10;
    Seconds/=10;
    Seconds1=Seconds%10;
    //设置时间标签
    this->ui->label_Days1->setText(QString::number(Days1));
    this->ui->label_Days2->setText(QString::number(Days2));
    this->ui->label_Days3->setText(QString::number(Days3));

    this->ui->label_Hours1->setText(QString::number(Hours1));
    this->ui->label_Hours2->setText(QString::number(Hours2));

    this->ui->label_Minutes1->setText(QString::number(Minutes1));
    this->ui->label_Minutes2->setText(QString::number(Minutes2));

    this->ui->label_Seconds1->setText(QString::number(Seconds1));
    this->ui->label_Seconds2->setText(QString::number(Seconds2));

}

void Dialog::UpdateTime()
{
    //计算时间差
    QDateTime begin_time = QDateTime::currentDateTime();
    QDateTime end_time = QDateTime::fromString("2020.06.07","yyyy.MM.dd");
    QTime time;
    time.setHMS(0, 0, 0, 0);
    int LeftSeconds=begin_time.secsTo(end_time);
    int Days,Hours,Minutes,Seconds;

    //获取秒
    Seconds=LeftSeconds%60;

    LeftSeconds-=Seconds;
    //转化成分钟
    LeftSeconds/=60;
    //获取分钟
    Minutes=LeftSeconds%60;

    LeftSeconds-=Minutes;
    //转化成小时
    LeftSeconds/=60;
    //获取小时
    Hours=LeftSeconds%24;

    //获取天
    Days=(LeftSeconds-Hours)/24;
    this->SetTime(Days,Hours,Minutes,Seconds);

    /*
    if(isProcessExited("WINWORD.EXE")||isProcessExited("POWERPNT.EXE")
       ||isProcessExited("EXCEL.EXE")||isProcessExited("chrome.exe"))
    {
        //进程存在取消总在最前
        setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
        show();


    }
    else
    {
        setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
        show();
    }
    */
}


bool Dialog::isProcessExited(QString ProcessID)
{
    QProcess process;
    QString result;
    process.start("tasklist", QStringList()<<"-fi"<<"imagename eq "+ProcessID);
    //得到进程列表
    if (process.waitForStarted(-1))
    {
        while(process.waitForReadyRead(-1))
        {
            //得到进程列表
            result=process.readAllStandardOutput();
            result=result.toLocal8Bit();
        }
    }
    //分割文本
    QStringList list = result.split("\n");
    //>=4表示该进程存在
    if(list.length()>=4)
        return true;
    else
        return false;
}

void Dialog::on_radioButton_Hide_clicked()
{
    if(ui->radioButton_Hide->isChecked())
    {
        //隐藏
        ui->label_background->setVisible(false);
        ui->label_Days1->setVisible(false);
        ui->label_Days2->setVisible(false);
        ui->label_Days3->setVisible(false);
        ui->label_Hours1->setVisible(false);
        ui->label_Hours2->setVisible(false);
        ui->label_Minutes1->setVisible(false);
        ui->label_Minutes2->setVisible(false);
        ui->label_Seconds1->setVisible(false);
        ui->label_Seconds2->setVisible(false);
        ui->pushButton_About->setVisible(false);
    }
    else
    {
        //显示
        ui->label_background->setVisible(true);
        ui->label_Days1->setVisible(true);
        ui->label_Days2->setVisible(true);
        ui->label_Days3->setVisible(true);
        ui->label_Hours1->setVisible(true);
        ui->label_Hours2->setVisible(true);
        ui->label_Minutes1->setVisible(true);
        ui->label_Minutes2->setVisible(true);
        ui->label_Seconds1->setVisible(true);
        ui->label_Seconds2->setVisible(true);
        ui->pushButton_About->setVisible(true);
    }
}

void Dialog::on_pushButton_About_clicked()
{
    QMessageBox AboutBox(QMessageBox::NoIcon,"关于高考倒计时2019","高考倒计时2019\n"
                                                           "版本号:V1.00.8.4 Release\n"
                                                           "By:小白神马好吃吗\n"
                                                           "QQ:1834309151\n"
                                                           "版权声明:本小工具采用Qt 代码完全开源\n"
                                                           "(本来就没什么技术含量)\n"
                                                           "计时背景部分模仿lookcos发布在github.com/LookCos/的html计时器\n"
                                                           "本小工具仅用于班级高考倒计时,不用于任何商业用途\n"
                                                           "若原作者觉不妥,请联系指教\n");
    AboutBox.setIconPixmap(QPixmap(":/White"));
    AboutBox.exec();

}
