#include "CQWindow.h"

int main(int argc, char *argv[])
{
    RX::CQWindow win(0);
    win.createWindow();
    win.setTitle("哈哈");
    win.show(SW_SHOWMAXIMIZED);
    return 0;
}
