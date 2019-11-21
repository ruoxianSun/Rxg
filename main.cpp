#include "widget.h"
#include <QApplication>
#include "CQWindow.h"

int main(int argc, char *argv[])
{
    RX::CQWindow win(0);
    win.createWindow();
    win.setTitle("哈哈");
    win.show(SW_SHOW);
    return 0;
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
