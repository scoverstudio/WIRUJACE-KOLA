// MFCApplication4Dlg.h : plik nagłówkowy

#pragma once
#include "RotatingCircle.h"

// Klasa dialogowa CMFCApplication4Dlg
class CMFCApplication4Dlg : public CDialogEx
{
public:
    CMFCApplication4Dlg(CWnd* pParent = nullptr);    // Konstruktor

    // Identyfikator okna dialogowego
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFCAPPLICATION4_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // Obsługa DDX/DDV
    HICON m_hIcon;

    // Tablica czterech wskaźników na obiekty RotatingCircle
    RotatingCircle* circles[4];

    // Funkcje
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnStartCircles(); // Funkcja obsługi przycisku startującego koła
    afx_msg void OnStopCircles();


    DECLARE_MESSAGE_MAP()

public:
    virtual ~CMFCApplication4Dlg(); // Destruktor
};
