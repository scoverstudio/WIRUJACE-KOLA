// MFCApplication4Dlg.cpp: plik implementacji

#include "pch.h"
#include "framework.h"
#include "MFCApplication4.h"
#include "MFCApplication4Dlg.h"
#include "afxdialogex.h"
#include "RotatingCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CMFCApplication4Dlg::CMFCApplication4Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFCAPPLICATION4_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    for (int i = 0; i < 4; ++i) {
        circles[i] = nullptr;
    }
}

void CMFCApplication4Dlg::OnStopCircles()
{
    for (int i = 0; i < 4; ++i) {
        if (circles[i]) {
            circles[i]->Stop();
        }
    }
}

void CMFCApplication4Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication4Dlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_START, &CMFCApplication4Dlg::OnStartCircles) 
    ON_BN_CLICKED(IDC_BUTTON_STOP, &CMFCApplication4Dlg::OnStopCircles)
END_MESSAGE_MAP()


BOOL CMFCApplication4Dlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);          
    SetIcon(m_hIcon, FALSE);      

    circles[0] = new RotatingCircle(RGB(255, 0, 0), this,0);   
    circles[1] = new RotatingCircle(RGB(0, 255, 0), this, 0.75); 
    circles[2] = new RotatingCircle(RGB(0, 0, 255), this, 1.6);   
    circles[3] = new RotatingCircle(RGB(255, 255, 0), this, 2.2);

    return TRUE; 
}

void CMFCApplication4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void CMFCApplication4Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CPaintDC dc(this);

   
        for (int i = 0; i < 4; ++i) {
            if (circles[i]) {
                circles[i]->Draw(&dc);
            }
        }

        CDialogEx::OnPaint();
    }
}


HCURSOR CMFCApplication4Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication4Dlg::OnStartCircles()
{
    for (int i = 0; i < 4; ++i) {
        if (circles[i]) {
            circles[i]->Start();
        }
    }
}

CMFCApplication4Dlg::~CMFCApplication4Dlg()
{
    for (int i = 0; i < 4; ++i) {
        if (circles[i]) {
            circles[i]->Stop();
            delete circles[i];
            circles[i] = nullptr;
        }
    }
}
