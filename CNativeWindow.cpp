#include "CNativeWindow.h"
#include <WinUser.h>
namespace RX {
std::map<HWND,CWindowW32*> CWindowW32::_registeredClass;

CWindowW32::CWindowW32(HINSTANCE inst)
{
    _isExit=false;
    _hwnd=0;
    _instance=inst;
}

CWindowW32::~CWindowW32()
{
    if(handel()!=0&&::IsWindow(handel()))
    {
        ::DestroyWindow(handel());
    }
}

int CWindowW32::messageProc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    return 0;
}

void CWindowW32::create(int style)
{
    wchar_t className[64];
    wchar_t title[128];
    ::wsprintf(className,L"%p",this);
    {
        WNDCLASSEX wClass;
        wClass.cbSize=sizeof(WNDCLASSEX);
        wClass.style=CS_HREDRAW|CS_VREDRAW;
        wClass.lpfnWndProc=CWindowW32::wndProc;
        wClass.cbClsExtra=0;
        wClass.cbWndExtra=0;
        wClass.hInstance=this->_instance;
        wClass.hIcon=NULL;
        wClass.hCursor=::LoadCursor(NULL,IDC_ARROW);
        wClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
        wClass.lpszMenuName=NULL;
        wClass.lpszClassName=className;
        wClass.hIconSm=NULL;
        if(0==::RegisterClassEx(&wClass))
        {
            return;
        }
    }
    if(handel()==0)
    {
        ::wsprintf(title,L"窗口类名(C++类虚表指针):%p",this);
        HWND hwnd=::CreateWindow(className,
                                 title,
                                 style,
                                 0,0,800,600,
                                 NULL,
                                 NULL,
                                 _instance,
                                 (LPVOID)this
                                 );
        if(hwnd==0)
        {
            wchar_t msg[128];
            ::wsprintf(msg,L"CreateWindow()失败:%ld",::GetLastError());
            ::MessageBox(0,msg,L"错误",MB_OK);
        }
    }

}



void CWindowW32::show(int iCmdShow)
{
    if(handel())
    {
        MSG msg;
        ShowWindow(handel(), iCmdShow);
        UpdateWindow(handel());

        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if(_isExit)break;
        }
    }
}

LRESULT CWindowW32::wndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    CWindowW32*win=0;
    if(!win)
    {
        if(_registeredClass.find(hwnd)!=_registeredClass.end())
        {
            win=_registeredClass[hwnd];
        }
    }

    switch(msg)
    {
    case WM_CREATE:
    {
        win=(CWindowW32*)(((LPCREATESTRUCT)lp)->lpCreateParams);
        win->_hwnd=hwnd;
        _registeredClass[hwnd]=win;
        return win->messageProc(hwnd,msg,wp,lp);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default:
    {
        if(win)
        {
            if(win->messageProc(hwnd,msg,wp,lp)==0)
            {
                return ::DefWindowProc(hwnd,msg,wp,lp);
            }
        }
        else {
            return ::DefWindowProc(hwnd,msg,wp,lp);
        }
    }break;
    }
    return 0;
}
}


