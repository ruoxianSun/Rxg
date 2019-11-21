#include "CQWindow.h"
namespace RX
{

CQWindow::CQWindow(HINSTANCE inst):CWindowW32(inst)
{
    w=300,h=300;
}

void CQWindow::setTitle(const QString &title)
{
    ::SetWindowText(handel(),title.toStdWString().c_str());
}

void CQWindow::createWindow()
{
    create(WS_EX_TOPMOST|WS_OVERLAPPEDWINDOW);
}

int CQWindow::messageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (msg)
    {
    case WM_PAINT:
        hdc = ::BeginPaint(hwnd, &ps);
        ::Rectangle(hdc, 10, 10, w, h);
        ::EndPaint(hwnd, &ps);
        return 1;
    default:
        break;
    }
    return 0;
}

}

