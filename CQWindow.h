#ifndef CQWINDOW_H
#define CQWINDOW_H

#include "CNativeWindow.h"
#include <qstring.h>
namespace RX {
class CQWindow:public CWindowW32
{
public:
    CQWindow(HINSTANCE inst);
    void setTitle(const QString&title);
    void createWindow();
protected:
    int messageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
protected:
    int w,h;
};
}

#endif // CQWINDOW_H
