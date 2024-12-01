#include "pch.h"
#include "RotatingCircle.h"
#include <math.h>

RotatingCircle::RotatingCircle(COLORREF color, CWnd* pWnd, double startAngle)
    : m_Color(color), m_pWnd(pWnd), m_pThread(nullptr), m_Running(false),
    m_StartAngle(startAngle), m_Angle(startAngle) {}

void RotatingCircle::Start() {
    if (!m_Running) {
        m_Running = true;
        m_pThread = AfxBeginThread(ThreadFunc, this);
    }
}

void RotatingCircle::Stop() {
    m_Running = false;
    if (m_pThread) {
        WaitForSingleObject(m_pThread->m_hThread, INFINITE);
        m_pThread = nullptr;
    }
}

UINT RotatingCircle::ThreadFunc(LPVOID pParam) {
    RotatingCircle* pCircle = (RotatingCircle*)pParam;
    while (pCircle->m_Running) {
        pCircle->Rotate();
        pCircle->m_pWnd->Invalidate();
        Sleep(50); // Szybkoœæ obrotu
    }
    return 0;
}

void RotatingCircle::Rotate() {
    m_Angle += 0.1;
    if (m_Angle > 2 * 3.1415) m_Angle = 0;
}

void RotatingCircle::Draw(CDC* pDC)
{
    CRect rect;
    m_pWnd->GetClientRect(&rect);
    int centerX = rect.Width() / 2;
    int centerY = rect.Height() / 2;

    int radius = 120;

    // Wylicz przesuniêcie na podstawie k¹ta obrotu i k¹ta pocz¹tkowego
    int offsetX = static_cast<int>(radius * cos(m_Angle + m_StartAngle));
    int offsetY = static_cast<int>(radius * sin(m_Angle + m_StartAngle));

    // Ustawienie koloru pêdzla
    CBrush brush(m_Color);
    CBrush* pOldBrush = pDC->SelectObject(&brush);

    // Rysowanie pe³nego ko³a o œrednicy 50
    int circleRadius = 50;
    pDC->Ellipse(centerX + offsetX - circleRadius, centerY + offsetY - circleRadius,
        centerX + offsetX + circleRadius, centerY + offsetY + circleRadius);

    // Przywracanie poprzedniego pêdzla
    pDC->SelectObject(pOldBrush);
}

