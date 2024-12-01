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
        Sleep(50); // Szybko�� obrotu
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

    // Wylicz przesuni�cie na podstawie k�ta obrotu i k�ta pocz�tkowego
    int offsetX = static_cast<int>(radius * cos(m_Angle + m_StartAngle));
    int offsetY = static_cast<int>(radius * sin(m_Angle + m_StartAngle));

    // Ustawienie koloru p�dzla
    CBrush brush(m_Color);
    CBrush* pOldBrush = pDC->SelectObject(&brush);

    // Rysowanie pe�nego ko�a o �rednicy 50
    int circleRadius = 50;
    pDC->Ellipse(centerX + offsetX - circleRadius, centerY + offsetY - circleRadius,
        centerX + offsetX + circleRadius, centerY + offsetY + circleRadius);

    // Przywracanie poprzedniego p�dzla
    pDC->SelectObject(pOldBrush);
}

