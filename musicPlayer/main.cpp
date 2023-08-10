#include "widget.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style.qss");
    if (file.exists()) {
        //以只读方式打开
        file.open(QFile::ReadOnly);
        //以字符串的方式保存读出的结果
        QString styleSheet = QLatin1String(file.readAll());
        //设置全局样式
        qApp->setStyleSheet(styleSheet);
        //关闭文件
        file.close();
    }

    Widget w;
    QPalette pal(w.palette());
//    pal.setColor(QPalette::Background, QColor(30, 30, 25));
    pal.setColor(QPalette::Background, QColor(68, 69, 73));
    w.setAutoFillBackground(true);
    w.setPalette(pal);
    w.show();
    return a.exec();
}
