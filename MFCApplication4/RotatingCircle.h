#pragma once
#include <afxwin.h>

class RotatingCircle {
public:
    RotatingCircle(COLORREF color, CWnd* pWnd, double startAngle);
    void Start();
    void Stop();
    void Draw(CDC* pDC);

private:
    void Rotate();
    static UINT ThreadFunc(LPVOID pParam);

    COLORREF m_Color;
    CWnd* m_pWnd;
    CWinThread* m_pThread;
    bool m_Running;
    double m_Angle;
    double m_StartAngle;
};
