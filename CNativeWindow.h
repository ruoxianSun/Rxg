#ifndef CNATIVEWINDOW_H
#define CNATIVEWINDOW_H
#include <Windows.h>
#include <map>
namespace RX {
class CWindowW32
{
public:
    CWindowW32(HINSTANCE inst);
    ~CWindowW32();
    HWND handel(){return _hwnd;}
    void show(int);
protected:
    void create(int style=WS_OVERLAPPEDWINDOW);
    virtual int messageProc(HWND h,UINT msg,WPARAM wp,LPARAM lp);
    static LRESULT CALLBACK wndProc(HWND,UINT,WPARAM,LPARAM);
protected:
    static std::map<HWND,CWindowW32*> _registeredClass;
    HWND _hwnd;
    HINSTANCE _instance;
    bool _isExit;
};
}
#endif // CNATIVEWINDOW_H
